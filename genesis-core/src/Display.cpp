#include "Screen/Display.h"
#include "Core/Log.h"

namespace GC{

#define CHECK(x, msg) if (!(x)) { GC_CORE_ERROR("{}", msg); /*leanup();*/ Display::ERROR = true; } //<------------------

  Display::Display() : mFlipper(mState) {

    GC_CORE_INFO("Opening DRM ...");
    mState.drm_fd = open("/dev/dri/card1", O_RDWR | O_CLOEXEC);
    if (mState.drm_fd < 0) {
      GC_CORE_ERROR("Unable to open render node: {}", errno);
      ERROR = true;
    }

    drmModeRes *resources = drmModeGetResources(mState.drm_fd);
    CHECK(resources, "drmModeGetResources failed");

    drmModeConnector *conn = nullptr;
    for(int i = 0; i < resources->count_connectors; ++i){
      conn = drmModeGetConnector(mState.drm_fd, resources->connectors[i]);
      if(conn->connection == DRM_MODE_CONNECTED){
	mState.conn_id = conn->connector_id;
	break;
      }
      drmModeFreeConnector(conn);
      conn = nullptr;
    }
    CHECK(conn, "No connected connector found");

    CHECK(conn->count_modes > 0, "No valid modes");
    mState.mode = conn->modes[0];

    drmModeEncoder *enc = NULL;
    for (int i = 0; i < conn->count_encoders; ++i) {
      enc = drmModeGetEncoder(mState.drm_fd, conn->encoders[i]);
      if (enc && enc->crtc_id) {
	mState.crtc_id = enc->crtc_id;
	break;
      }
      if (enc) {
	drmModeFreeEncoder(enc);      
      }
    }
    if(mState.crtc_id == 0){
      GC_CORE_ERROR("No CRTC found for connector {}", conn->connector_id);
      ERROR = true;
    }

    CHECK(enc, "No encoder with CRTC found");

    mState.saved_crtc = drmModeGetCrtc(mState.drm_fd, mState.crtc_id);

    GC_CORE_INFO("Creating GBM device ..");
    mState.gbm_dev = gbm_create_device(mState.drm_fd);
    if (!mState.gbm_dev) {
      GC_CORE_ERROR("Unable to create GBM device");
      close(mState.drm_fd);
      ERROR = true;
    }

    GC_CORE_INFO("Creating GBM surface");
    mState.gbm_surf = gbm_surface_create(
					 mState.gbm_dev, mState.mode.hdisplay, mState.mode.vdisplay,
					 GBM_FORMAT_XRGB8888, GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING);
    if (!mState.gbm_surf) {
      GC_CORE_ERROR("Unable to create GBM surface");
      gbm_device_destroy(mState.gbm_dev);
      close(mState.drm_fd);
      ERROR = true;
    }
  
  }

  Display::~Display() {
    mFlipper.cleanup();
    CleanUp();
  }

  void Display::CleanUp() {
  
  }

}
