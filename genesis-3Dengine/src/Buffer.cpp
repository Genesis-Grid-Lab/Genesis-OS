#include "Buffer.h"
#include "Platform/EGL/EGLBuffer.h"
#include "Genesis/Core/GC_Assert.h"
#include "Renderer.h"

namespace G3D {

  Ref<VertexBuffer> VertexBuffer::Create(uint32_t size){
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      GC_CORE_ASSERT(false, "no RendererAPI selected");
      return nullptr;
    case RendererAPI::API::EGL:
      return CreateRef<EGLVertexBuffer>(size);
    }

    GC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Ref<VertexBuffer> VertexBuffer::Create(Vertex* vertices, uint32_t size){
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      GC_CORE_ASSERT(false, "no RendererAPI selected");
      return nullptr;
    case RendererAPI::API::EGL:
      return CreateRef<EGLVertexBuffer>(vertices, size);
    }

    GC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size){
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
      GC_CORE_ASSERT(false, "no RendererAPI selected");
      return nullptr;
    case RendererAPI::API::EGL:
      return CreateRef<EGLVertexBuffer>(vertices, size);
    }

    GC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}


  Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
  {
    switch (Renderer::GetAPI())
      {
      case RendererAPI::API::None:    GC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::EGL:  return CreateRef<EGLIndexBuffer>(indices, size);
      }

    GC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}
