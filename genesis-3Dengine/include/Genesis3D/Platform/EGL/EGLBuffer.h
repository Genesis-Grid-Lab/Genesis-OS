#pragma once

#include "Buffer.h"

namespace G3D {

  class EGLVertexBuffer : public VertexBuffer{
  public:
    EGLVertexBuffer(uint32_t size);
    EGLVertexBuffer(float *vertices, uint32_t size);
    EGLVertexBuffer(Vertex* vertices, uint32_t size);
    virtual ~EGLVertexBuffer();
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetData(const void* data, uint32_t size) override;

    virtual const BufferLayout& GetLayout() const override{ return m_Layout; }
    virtual void SetLayout(const BufferLayout &layout) override {
      m_Layout = layout;
    }
  private:
    uint32_t m_RendererID;
    BufferLayout m_Layout;
  };

  class EGLIndexBuffer : public IndexBuffer{
  public:
    EGLIndexBuffer(uint32_t *indices, uint32_t count);
    virtual ~EGLIndexBuffer() override;
    virtual void Bind() const override;
    virtual void Unbind() const override;
    
    virtual uint32_t GetCount() const override { return m_Count;}
    
  private:
    uint32_t m_RendererID;
    uint32_t m_Count;    
  };
}
