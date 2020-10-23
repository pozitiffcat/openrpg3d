#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

namespace engine {

class mesh
{
public:
    explicit mesh(GLuint buffer);
    ~mesh();

private:
    GLuint m_buffer;
};

}

#endif // MESH_H
