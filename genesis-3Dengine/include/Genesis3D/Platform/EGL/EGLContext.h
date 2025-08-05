#pragma once

#include "GraphicsContext.h"

namespace G3D {

  class EGLGraphicsContext : public GraphicsContext{
  public:
    EGLGraphicsContext(DisplayState &display);
    ~EGLGraphicsContext();

    virtual void Init() override;
    virtual void SwapBuffers() override;

  private:
    DisplayState &mDisplay;
    EGLDisplay egl_display = EGL_NO_DISPLAY;
    EGLSurface egl_surf = EGL_NO_SURFACE;
    EGLContext egl_ctx = EGL_NO_CONTEXT;    
  };
}
