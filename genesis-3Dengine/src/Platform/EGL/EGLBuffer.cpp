#include "Platform/EGL/EGLBuffer.h"

namespace G3D {
  /////////////////////////////////////////////////////////////////////////////
  // VertexBuffer /////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////

  EGLVertexBuffer::EGLVertexBuffer(uint32_t size)
  {

    // glCreateBuffers(1, &m_RendererID);
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
  }

  EGLVertexBuffer::EGLVertexBuffer(float* vertices, uint32_t size)
  {

    // glCreateBuffers(1, &m_RendererID);
    glGenBuffers(1, &m_RendererID);    
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  }

  EGLVertexBuffer::EGLVertexBuffer(Vertex* vertices, uint32_t size)
  {

    // glCreateBuffers(1, &m_RendererID);
    glGenBuffers(1, &m_RendererID);    
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  }

  EGLVertexBuffer::~EGLVertexBuffer()
  {		
     

    glDeleteBuffers(1, &m_RendererID);
  }

  void EGLVertexBuffer::Bind() const
  {
     

    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  }

  void EGLVertexBuffer::Unbind() const
  {
     

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void EGLVertexBuffer::SetData(const void* data, uint32_t size)
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
  }

  /////////////////////////////////////////////////////////////////////////////
  // IndexBuffer //////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////

  EGLIndexBuffer::EGLIndexBuffer(uint32_t* indices, uint32_t count)
    : m_Count(count)
  {
     

    // glCreateBuffers(1, &m_RendererID);
    glGenBuffers(1, &m_RendererID);		
    // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
    // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
  }

  EGLIndexBuffer::~EGLIndexBuffer()
  {		
     

    glDeleteBuffers(1, &m_RendererID);
  }

  void EGLIndexBuffer::Bind() const
  {
     

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
  }

  void EGLIndexBuffer::Unbind() const
  {
     

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}
