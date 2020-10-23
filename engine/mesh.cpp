#include "mesh.h"

#include "vertex.h"

namespace engine {

mesh::mesh(const mesh_def &def)
    : m_buffer(0),
      m_vertices_count(def.vertices.size())
{
    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertices_count * sizeof(vertex), def.vertices.data(), GL_STATIC_DRAW);
}

mesh::~mesh()
{
    glDeleteBuffers(1, &m_buffer);
}

void mesh::render(const render_context &context)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glVertexAttribPointer(context.position_attrib, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*) 0);
    glVertexAttribPointer(context.normal_attrib, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*) 12);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices_count);
}

}
