#include "VertexArray.h"
#include "Log.h"
#include "Platform/EGL/EGLVertexArray.h"
#include "Genesis/Core/GC_Assert.h"
#include "Renderer.h"

namespace G3D {

Ref<VertexArray> VertexArray::Create() {

  GC_CORE_INFO("Vertex Array Creating");  
    switch (Renderer::GetAPI())
      {
      case RendererAPI::API::None:    GC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::EGL:  return CreateRef<EGLVertexArray>();
      }

    GC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

}
