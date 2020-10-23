#include "mesh.h"

namespace engine {

mesh::mesh(GLuint buffer)
    : m_buffer(buffer)
{
}

mesh::~mesh()
{
    glDeleteBuffers(1, &m_buffer);
}

}
