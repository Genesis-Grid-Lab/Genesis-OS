#include "Platform/EGL/EGLContext.h"
#include "Genesis/Core/Log.h"
#include "EGL/eglplatform.h"

namespace G3D {

  EGLGraphicsContext::EGLGraphicsContext(GC::Display *display) : mDisplay(display) {}

  EGLGraphicsContext::~EGLGraphicsContext(){
    if (egl_display != EGL_NO_DISPLAY) {
      eglMakeCurrent(egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
      if (egl_ctx != EGL_NO_CONTEXT) eglDestroyContext(egl_display, egl_ctx);
      if (egl_surf != EGL_NO_SURFACE) eglDestroySurface(egl_display, egl_surf);
      eglTerminate(egl_display);
    }
  }

  void EGLGraphicsContext::Init(){
    GC_CORE_INFO("Initialize EGL ...");
    // Initialize EGL
    egl_display = eglGetPlatformDisplay(EGL_PLATFORM_GBM_KHR, mDisplay->mState.gbm_dev, NULL);
    if (egl_display == EGL_NO_DISPLAY) {
      GC_CORE_ERROR( "Unable to get EGL platform display");
      gbm_surface_destroy(mDisplay->mState.gbm_surf);
      gbm_device_destroy(mDisplay->mState.gbm_dev);
      close(mDisplay->mState.drm_fd);
    }
    
    if (!eglInitialize(egl_display, NULL, NULL)) {
      GC_CORE_ERROR("Unable to initialize EGL");
      eglTerminate(egl_display);
      gbm_surface_destroy(mDisplay->mState.gbm_surf);
      gbm_device_destroy(mDisplay->mState.gbm_dev);
      close(mDisplay->mState.drm_fd);
    }

    std::cout << "EGL Version = " << eglQueryString(egl_display, EGL_VERSION) << "\n";
    std::cout << "EGL Vendor = " << eglQueryString(egl_display, EGL_VENDOR) << "\n";

    eglBindAPI(EGL_OPENGL_ES_API);

    gladLoadEGL(egl_display, eglGetProcAddress);  // load EGL
    gladLoadGLES2(eglGetProcAddress);    

    // Choose config
    EGLint attr[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8,
	EGL_ALPHA_SIZE, 8,
	EGL_DEPTH_SIZE, 16,
        EGL_NONE
    };
    EGLConfig config = NULL;
    EGLint num_configs = 0;

    if (!eglChooseConfig(egl_display, attr, &config, 1, &num_configs) ||
        num_configs == 0) {
      GC_CORE_ERROR("Unable to choose EGL config");
        eglTerminate(egl_display);
        gbm_surface_destroy(mDisplay->mState.gbm_surf);
        gbm_device_destroy(mDisplay->mState.gbm_dev);
        close(mDisplay->mState.drm_fd);
    }

    GC_CORE_INFO("Creating EGL context ..");
    // Create context
    EGLint contextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext egl_ctx = eglCreateContext(egl_display, config, EGL_NO_CONTEXT, contextAttributes);
    if (egl_ctx == EGL_NO_CONTEXT) {
      GC_CORE_ERROR("Unable to create EGL context");
        eglTerminate(egl_display);
        gbm_surface_destroy(mDisplay->mState.gbm_surf);
        gbm_device_destroy(mDisplay->mState.gbm_dev);
        close(mDisplay->mState.drm_fd);
    }

    GC_CORE_INFO("Creating EGL surface ...");
    // Create surface
    egl_surf = eglCreateWindowSurface(egl_display, config, mDisplay->mState.gbm_surf, NULL);
    if (egl_surf == EGL_NO_SURFACE) {
      GC_CORE_ERROR("Unable to create EGL surface : {}", eglGetError());
      eglTerminate(egl_display);
      gbm_surface_destroy(mDisplay->mState.gbm_surf);
      gbm_device_destroy(mDisplay->mState.gbm_dev);
      close(mDisplay->mState.drm_fd);
    }

    if (!eglMakeCurrent(egl_display, egl_surf, egl_surf, egl_ctx)) {
      GC_CORE_ERROR("Unable to make context current");
        eglDestroySurface(egl_display, egl_surf);
        eglTerminate(egl_display);
        gbm_surface_destroy(mDisplay->mState.gbm_surf);
        gbm_device_destroy(mDisplay->mState.gbm_dev);
        close(mDisplay->mState.drm_fd);
    }

    eglSwapInterval(egl_display, 1);
  }

  void EGLGraphicsContext::SwapBuffers() {
    eglSwapBuffers(egl_display, egl_surf);
  }  
}
