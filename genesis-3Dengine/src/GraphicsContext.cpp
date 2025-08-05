#include "GraphicsContext.h"
#include "Platform/EGL/EGLContext.h"
#include "Renderer.h"
#include "Genesis/Core/Log.h"

namespace G3D {
Scope<GraphicsContext> GraphicsContext::Create(DisplayState &display) {
  GC_INFO("context create");
    switch(Renderer::GetAPI()){
    case RendererAPI::API::None:
      GC_CORE_WARN("No Renderer selected");
      return nullptr;

    case RendererAPI::API::EGL:
      return CreateScope<EGLGraphicsContext>(display);
    }

    GC_CORE_ERROR("Unknown RendererAPI");
    return nullptr;
    
  }
}
