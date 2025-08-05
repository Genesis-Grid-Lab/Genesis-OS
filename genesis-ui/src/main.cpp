#define GL_GLES2
#include "Genesis/Core/Log.h"
#include "Genesis3D/GraphicsContext.h"
#include "Genesis3D/RenderCommand.h"
#include "Genesis3D/Renderer.h"
#include "Genesis3D/Buffer.h"
#include "Genesis3D/VertexArray.h"
#include "Genesis3D/Shader.h"
#include "Genesis3D/Mesh.h"
#include "Genesis3D/Texture.h"

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory)
{
  string filename = string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  stbi_set_flip_vertically_on_load(1);
  unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data)
    {
      GLenum format;
      if (nrComponents == 1)
	format = GL_RED;
      else if (nrComponents == 3)
	format = GL_RGB;
      else if (nrComponents == 4)
	format = GL_RGBA;

      glBindTexture(GL_TEXTURE_2D, textureID);
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      stbi_image_free(data);
    }
  else
    {
      std::cout << "Texture failed to load at path: " << path << std::endl;
      stbi_image_free(data);
    }

  return textureID;
}

Ref<G3D::Mesh> GenerateCubeMesh() {
  std::vector<G3D::Vertex> vertices;
  std::vector<uint32_t> indices;

  glm::vec3 positions[] = {
    {-0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}, // front
    {-0.5f, -0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f}, // back
    {-0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f, -0.5f}, // top
    {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f}, // bottom
    { 0.5f, -0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f}, // right
    {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f, -0.5f}  // left
  };

  glm::vec3 normals[] = {
    { 0,  0,  1}, { 0,  0, -1}, { 0,  1,  0}, { 0, -1,  0}, { 1,  0,  0}, {-1,  0,  0}
  };

  glm::vec2 uvs[] = {
    {0, 0}, {1, 0}, {1, 1}, {0, 1}
  };

  uint32_t faceIndices[] = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    8, 9,10,10,11, 8,
    12,13,14,14,15,12,
    16,17,18,18,19,16,
    20,21,22,22,23,20
  };

  for (int face = 0; face < 6; ++face) {
    for (int i = 0; i < 4; ++i) {
      G3D::Vertex v;
      v.Position = positions[face * 4 + i];
      v.Normal = normals[face];
      v.TexCoords = uvs[i];
      v.Tangent = glm::vec3(1, 0, 0);     // Placeholder
      v.Bitangent = glm::vec3(0, 1, 0);   // Placeholder
      vertices.push_back(v);
    }
  }

  for (int i = 0; i < 36; ++i)
    indices.push_back(faceIndices[i]);

  G3D::TextureMesh tesMesh;
  tesMesh.id =
      TextureFromFile("board.png", "/usr/share/genesis-ui/Data/Textures");
  tesMesh.type = "texture_diffuse";
  std::vector<G3D::TextureMesh> noTextures; // Can be replaced later
  noTextures.emplace_back(tesMesh);  
  

  return CreateRef<G3D::Mesh>(vertices, indices, noTextures);
}

using namespace std;

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

  Ref<G3D::Shader> shader2 = G3D::Shader::Create("/usr/share/genesis-ui/Data/Shaders/shader.glsl");
  shader2->Bind();
  
  Ref<G3D::Mesh> cube = GenerateCubeMesh();

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

    cube->Draw(shader2);
    m_Context->SwapBuffers();
    if (!GC::Display::FlipPage())
      break;
  }
  G3D::Renderer::Shutdown();

    return 0;
}
