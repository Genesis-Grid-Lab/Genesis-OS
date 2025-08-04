#pragma once
#include "Config.h"

// Thin POD to carry display/scanout state built by your existing init code.
struct DisplayState {
  int drm_fd = -1;
  uint32_t crtc_id = 0;
  uint32_t conn_id = 0;
  drmModeModeInfo mode{}; // non-const because drmModeSetCrtc wants a mutable ptr
  
  gbm_device*  gbm_dev  = nullptr;
  gbm_surface* gbm_surf = nullptr;
  
  EGLDisplay egl_display = EGL_NO_DISPLAY;
  EGLSurface egl_surf    = EGL_NO_SURFACE;
};

// ------------------------------------------------------------
// PageFlipper: owns gbm front buffers, FB cache, flip/wait
// ------------------------------------------------------------
class PageFlipper {
public:
  explicit PageFlipper(const DisplayState& s);

    // Present current EGL front buffer. On the first call, does a modeset.
    // On subsequent calls, queues a page flip and waits for completion,
    // then releases the previous BO.
  bool present();

  void cleanup();

private:
  uint32_t get_or_create_fb(gbm_bo* bo);

  static void on_page_flip_static(int fd, unsigned int, unsigned int, unsigned int, void* data);
    void on_page_flip(int) { waiting_ = false; }

    void wait_for_event() {
        fd_set fds; FD_ZERO(&fds); FD_SET(s_.drm_fd, &fds);
        if (select(s_.drm_fd + 1, &fds, nullptr, nullptr, nullptr) > 0) {
            drmHandleEvent(s_.drm_fd, &ev_);
        }
    }

    const DisplayState& s_;
    drmEventContext ev_{};
    std::unordered_map<gbm_bo*, uint32_t> fb_cache_;
    gbm_bo*  prev_bo_ = nullptr;
    uint32_t prev_fb_ = 0;
    bool first_ = true;
    volatile bool waiting_ = false;
};
