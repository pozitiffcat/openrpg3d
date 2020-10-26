#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include "texture_data.h"

namespace engine {

class texture
{
public:
    explicit texture(const texture_data &data);
    ~texture();

private:
    GLuint m_texture;
};

}

#endif // TEXTURE_H
