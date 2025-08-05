#include "Platform/EGL/EGLTexture.h"
#include "Core/GC_Assert.h"
#include <stb_image.h>

namespace G3D {
  EGLTexture2D::EGLTexture2D(unsigned int id){
    m_RendererID = id;
  }

  // EGLTexture2D::EGLTexture2D(uint32_t width, uint32_t height)
  //   : m_Width(width), m_Height(height)
  // {
    

  //   m_InternalFormat = GL_RGBA8;
  //   m_DataFormat = GL_RGBA;

  //   glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
  //   glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

  //   glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //   glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //   glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //   glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // }

  EGLTexture2D::EGLTexture2D(uint32_t width, uint32_t height)
    : m_Width(width), m_Height(height)
  {
    m_InternalFormat = GL_RGBA;
    m_DataFormat = GL_RGBA;
    
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }  

  // EGLTexture2D::EGLTexture2D(uint32_t width, uint32_t height, GLenum internalFormat, GLenum dataFormat)
  //   : m_Width(width), m_Height(height),  m_InternalFormat(internalFormat), m_DataFormat(dataFormat)
  // {
    

  //   glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
  //   glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

  //   glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //   glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //   glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //   glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // }

  EGLTexture2D::EGLTexture2D(uint32_t width, uint32_t height, GLenum internalFormat, GLenum dataFormat)
    : m_Width(width), m_Height(height), m_InternalFormat(internalFormat), m_DataFormat(dataFormat)
  {
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }  

  // EGLTexture2D::EGLTexture2D(Ref<Framebuffer>& buffer){
    
  //   GC_CORE_INFO("Creating Texture2D from Framebuffer");
  //   m_RendererID = buffer->GetColorAttachmentRendererID();
  //   m_Width = buffer->GetSpecification().Width;
  //   m_Height = buffer->GetSpecification().Height;
  //   m_IsLoaded = true;
  // }

  // EGLTexture2D::EGLTexture2D(const std::string& path)
  //   : m_Path(path)
  // {
    

  //   int width, height, channels;
  //   stbi_set_flip_vertically_on_load(0);
  //   stbi_uc* data = nullptr;
  //   {			
  //     data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  //   }
			
  //   if (data)
  //     {
  // 	m_IsLoaded = true;

  // 	m_Width = width;
  // 	m_Height = height;

  // 	GLenum internalFormat = 0, dataFormat = 0;
  // 	if (channels == 4)
  // 	  {
  // 	    internalFormat = GL_RGBA8;
  // 	    dataFormat = GL_RGBA;
  // 	  }
  // 	else if (channels == 3)
  // 	  {
  // 	    internalFormat = GL_RGB8;
  // 	    dataFormat = GL_RGB;
  // 	  }

  // 	m_InternalFormat = internalFormat;
  // 	m_DataFormat = dataFormat;

  // 	GC_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

  // 	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
  // 	glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

  // 	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // 	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // 	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // 	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // 	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

  // 	stbi_image_free(data);
  //     }
  //   else{
  //     GC_CORE_WARN("Could not load {0}", path);
  //   }
  // }


  EGLTexture2D::EGLTexture2D(const std::string& path)
    : m_Path(path)
  {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(0);
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data)
      {
        m_IsLoaded = true;

        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
	  {
            internalFormat = GL_RGBA;
            dataFormat = GL_RGBA;
	  }
        else if (channels == 3)
	  {
            internalFormat = GL_RGB;
            dataFormat = GL_RGB;
	  }

        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;

        GC_CORE_ASSERT(internalFormat && dataFormat, "Format not supported!");

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        stbi_image_free(data);
      }
    else
      {
        GC_CORE_WARN("Could not load {0}", path);
      }
  }  

  EGLTexture2D::~EGLTexture2D()
  {
    

    glDeleteTextures(1, &m_RendererID);
  }

  // void EGLTexture2D::SetData(void* data, uint32_t size)
  // {


  //   uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
  //   GC_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire
  //   texture!"); glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height,
  //   m_DataFormat, GL_UNSIGNED_BYTE, data);
  // }

  void EGLTexture2D::SetData(void* data, uint32_t size)
  {
    uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
    GC_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");

    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
  }  

  // void EGLTexture2D::Bind(uint32_t slot) const
  // {

  //   GC_CORE_ASSERT(m_RendererID != 0, "Texture RendererID is 0!");
  //   glBindTextureUnit(slot, m_RendererID);
  //   // glActiveTexture(GL_TEXTURE0 + slot);                // Set the active
  //   texture slot
  //   // glBindTexture(GL_TEXTURE_2D, m_RendererID);         // Bind the
  //   texture
  // }

  void EGLTexture2D::Bind(uint32_t slot) const
  {
    GC_CORE_ASSERT(m_RendererID != 0, "Texture RendererID is 0!");
    
    glActiveTexture(GL_TEXTURE0 + slot);        // Select texture unit
    glBindTexture(GL_TEXTURE_2D, m_RendererID); // Bind the texture to unit
  }
  
}
