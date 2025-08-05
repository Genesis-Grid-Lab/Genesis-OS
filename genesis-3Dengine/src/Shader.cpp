#include "Shader.h"
#include "Core/GC_Assert.h"
#include "Renderer.h"
#include "Platform/EGL/EGLShader.h"


namespace G3D {

  Ref<Shader> Shader::Create(const std::string& filepath)
  {
    switch (Renderer::GetAPI())
      {
      case RendererAPI::API::None:    GC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::EGL:  return CreateRef<EGLShader>(filepath);
      }

    GC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
  {
    switch (Renderer::GetAPI())
      {
      case RendererAPI::API::None:    GC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::EGL:  return CreateRef<EGLShader>(name, vertexSrc, fragmentSrc);
      }

    GC_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}
