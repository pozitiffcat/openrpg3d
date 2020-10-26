#include "mesh.h"

#include "vertex.h"

namespace engine {

mesh::mesh(const mesh_data &data)
    : m_buffer(0),
      m_vertices_count(data.vertices.size())
{
    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertices_count * sizeof(vertex), data.vertices.data(), GL_STATIC_DRAW);
}

mesh::~mesh()
{
    glDeleteBuffers(1, &m_buffer);
}

void mesh::render(const render_context &context)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

    if (context.position_attrib != -1)
        glVertexAttribPointer(context.position_attrib, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*) 0);

    if (context.normal_attrib != -1)
        glVertexAttribPointer(context.normal_attrib, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*) 12);

    if (context.tangent_attrib != -1)
        glVertexAttribPointer(context.tangent_attrib, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*) 24);

    if (context.bitangent_attrib != -1)
        glVertexAttribPointer(context.bitangent_attrib, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*) 36);

    if (context.texcoord_attrib != -1)
        glVertexAttribPointer(context.texcoord_attrib, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const GLvoid*) 48);

    glDrawArrays(GL_TRIANGLES, 0, m_vertices_count);
}

}
