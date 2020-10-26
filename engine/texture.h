#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include "texture_data.h"
#include "render_context.h"

namespace engine {

class texture
{
    friend class drawable;
public:
    explicit texture(const texture_data &data);
    ~texture();

private:
    void bind();

private:
    GLuint m_texture;
};

}

#endif // TEXTURE_H
