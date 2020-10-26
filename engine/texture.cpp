#include "texture.h"

namespace engine {

texture::texture(const texture_data &data)
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.rgba.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}

texture::~texture()
{
    glDeleteTextures(1, &m_texture);
}

void texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

}
