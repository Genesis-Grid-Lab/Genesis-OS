#include "RendererAPI.h"
#include "Platform/EGL/EGLRendererAPI.h"
#include "Genesis/Core/Log.h"

namespace G3D {
RendererAPI::API RendererAPI::s_API = RendererAPI::API::EGL;
  Scope<RendererAPI> RendererAPI::Create(){
    switch (s_API) {
    case RendererAPI::API::None:
      GC_CORE_WARN("No rendererAPI selected");
      return nullptr;
    case RendererAPI::API::EGL:
      return CreateScope<EGLRendererAPI>();
    }

    GC_CORE_ERROR("Unknown RendererAPI!");
    return nullptr;

  } 
}
