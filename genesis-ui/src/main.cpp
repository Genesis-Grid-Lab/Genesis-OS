#define GL_GLES2
#include "Genesis/Core/Log.h"
#include "Genesis3D/GraphicsContext.h"
#include "Genesis3D/RenderCommand.h"
#include "Genesis3D/Renderer.h"
#include "Genesis3D/Buffer.h"
#include "Genesis3D/VertexArray.h"

#define CHECK(x, msg) if (!(x)) { std::cerr << msg << std::endl; cleanup(); return -1; }

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
  GC::Display screen;
  Scope<G3D::GraphicsContext> m_Context;

  Ref<G3D::VertexArray> vertexArray = G3D::VertexArray::Create();

  m_Context = G3D::GraphicsContext::Create(&screen);

  m_Context->Init();
  
  G3D::Renderer::Init();
    // Compile shaders
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertSource, NULL);
    glCompileShader(vert);
    GLint compiled = 0;
    glGetShaderiv(vert, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        cerr << "Vertex shader failed to compile" << endl;
    }

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragSource, NULL);
    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        cerr << "Fragment shader failed to compile" << endl;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        cerr << "Program linking failed" << endl;
    }

    glUseProgram(program);

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

    // VBOs
    // GLuint vbo, ibo;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glGenBuffers(1, &ibo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLint pos = glGetAttribLocation(program, "aPosition");

    // glEnableVertexAttribArray(pos);
    // glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    GLint mvp = glGetUniformLocation(program, "uModelViewProjection");

    glEnable(GL_DEPTH_TEST);
    glClearDepthf(1.0f);
    glDepthFunc(GL_LEQUAL);
    // eglSwapInterval(egl_display, 1);

    // Loop
    float rotation = 0.0f;

    // dState = {drm_fd, crtc_id, conn_id, mode, gbm, gbm_surf, egl_display, egl_surf};

    // eglSwapInterval(egl_display, 1);

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
      
      glUniformMatrix4fv(mvp, 1, GL_FALSE, &mvpMat[0][0]);

      // glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLushort),
      // GL_UNSIGNED_SHORT, 0); eglSwapBuffers(egl_display, egl_surf);
      G3D::RenderCommand::DrawIndexed(vertexArray);
      m_Context->SwapBuffers();
      if (!screen.FlipPage())
	break;
    }
    G3D::Renderer::Shutdown();

    return 0;
}
