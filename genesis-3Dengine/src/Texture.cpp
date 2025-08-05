#include "Texture.h"
#include "Core/GC_Assert.h"
#include "Renderer.h"
#include "Platform/EGL/EGLTexture.h"
namespace G3D {
  Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
  {
    switch (Renderer::GetAPI())
      {
      case RendererAPI::API::None:    GC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::EGL:  return CreateRef<EGLTexture2D>(width, height);
      }

    GC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Ref<Texture2D> Texture2D::Create(const std::string& path)
  {
    switch (Renderer::GetAPI())
      {
      case RendererAPI::API::None:    GC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::EGL:  return CreateRef<EGLTexture2D>(path);
      }

    GC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
  Ref<Texture2D> Texture2D::Create(unsigned int id)
  {
    switch (Renderer::GetAPI())
      {
      case RendererAPI::API::None:    GC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::EGL:  return CreateRef<EGLTexture2D>(id);
      }

    GC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, GLenum internalFormat, GLenum dataFormat)
  {
    switch (Renderer::GetAPI())
      {
      case RendererAPI::API::None:    GC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::EGL:  return CreateRef<EGLTexture2D>(width, height, internalFormat, dataFormat);
      }

    GC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  // Ref<Texture2D> Texture2D::Create(Ref<Framebuffer>& buffer)
  // {
  //   switch (Renderer::GetAPI())
  //     {
  //     case RendererAPI::API::None:    GC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
  //     case RendererAPI::API::EGL:  return CreateRef<EGLTexture2D>(buffer);
  //     }

  //   GC_CORE_ASSERT(false, "Unknown RendererAPI!");
  //   return nullptr;
  // }
}
