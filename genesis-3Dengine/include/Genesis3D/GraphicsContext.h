#pragma once

#include "Genesis/Core/Config.h"
#include "Genesis/Screen/Display.h"

namespace G3D {

  class GraphicsContext{
  public:
    virtual ~GraphicsContext() = default;
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;

    static Scope<GraphicsContext> Create(DisplayState &display);    
  };
}
