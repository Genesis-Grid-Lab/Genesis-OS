#define GL_GLES2
#include "Genesis/Core/Log.h"
#include "Genesis3D/GraphicsContext.h"
#include "Genesis3D/RenderCommand.h"
#include "Genesis3D/Renderer.h"
#include "Genesis3D/Buffer.h"
#include "Genesis3D/VertexArray.h"
#include "Genesis3D/Shader.h"

using namespace std;

// Vertex Shader Source
const char* vertSource = R"(
attribute vec3 aPosition;

uniform mat4 uModelViewProjection;

void main()
{
    gl_Position = uModelViewProjection * vec4(aPosition, 1.0);
}
)";

// Fragment Shader Source
const char* fragSource = R"(
precision mediump float;

void main()
{
    gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
)";

int main() {
  GC::Log::Init();
  GC_CORE_INFO("Staring UI ..");
  GC::Display::Init();
  GC_CORE_INFO("Context start..");
  Scope<G3D::GraphicsContext> m_Context;

  GC_CORE_INFO("Context create");
  m_Context = G3D::GraphicsContext::Create(GC::Display::mState);

  GC_CORE_INFO("Context init");
  m_Context->Init();

  GC_CORE_INFO("Renderer init");
  G3D::Renderer::Init();
  
  GC_CORE_INFO("Vertex create");
  Ref<G3D::VertexArray> vertexArray = G3D::VertexArray::Create();

  Ref<G3D::Shader> shader =
      G3D::Shader::Create("shader", vertSource, fragSource);
  Ref<G3D::Shader> shader2 = G3D::Shader::Create("/usr/share/genesis-ui/Data/Shaders/shader.glsl");
  shader2->Bind();
  // Define a cube
  G3D::Vertex vertices[] = {
    // Front face
    {{-0.5f, -0.5f,  0.5f}},
    {{ 0.5f, -0.5f,  0.5f}},
    {{ 0.5f,  0.5f,  0.5f}},
    {{-0.5f,  0.5f,  0.5f}},
    // Back face
    {{-0.5f, -0.5f, -0.5f}},
    {{ 0.5f, -0.5f, -0.5f}},
    {{ 0.5f,  0.5f, -0.5f}},
    {{-0.5f,  0.5f, -0.5f}},
  };
  uint32_t indices[] = {
    0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 0, 1, 5, 5, 4, 0,
    1, 2, 6, 6, 5, 1, 2, 3, 7, 7, 6, 2, 3, 0, 4, 4, 7, 3,
  };

  Ref<G3D::VertexBuffer> vertexBuffer =
    G3D::VertexBuffer::Create(vertices, sizeof(vertices));
  vertexBuffer->SetLayout({ {G3D::ShaderDataType::Float3, "aPosition"} });

  const auto &ib = G3D::IndexBuffer::Create(indices, 36);

  vertexArray->AddVertexBuffer(vertexBuffer);
  vertexArray->SetIndexBuffer(ib);

  glEnable(GL_DEPTH_TEST);
  glClearDepthf(1.0f);
  glDepthFunc(GL_LEQUAL);

  // Loop
  float rotation = 0.0f;

  const float dt = 0.016f;

  for (;;) {
    G3D::RenderCommand::Clear();
    G3D::RenderCommand::SetClearColor({1, 0, 0, 1});      
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepthf(1.0f);
      
    rotation += dt;
      
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f/720.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
      
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 1, 0));
      
    glm::mat4 mvpMat = projection * view * model;

    shader2->SetMat4("uModelViewProjection", mvpMat);

    G3D::RenderCommand::DrawIndexed(vertexArray);
    m_Context->SwapBuffers();
    if (!GC::Display::FlipPage())
      break;
  }
  G3D::Renderer::Shutdown();

    return 0;
}
