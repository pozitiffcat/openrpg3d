#ifndef MESH_H
#define MESH_H

#include "mesh_def.h"
#include "render_context.h"

namespace engine {

class drawable;

class mesh
{
    friend class drawable;
public:
    explicit mesh(const mesh_def &def);
    ~mesh();

private:
    void render(const render_context &context);

private:
    GLuint m_buffer = 0;
    size_t m_vertices_count = 0;
};

}

#endif // MESH_H
