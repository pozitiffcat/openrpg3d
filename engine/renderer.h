#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <vector>
#include <memory>

#include "render_context.h"
#include "mesh_data.h"
#include "texture_data.h"

namespace engine {

class camera;
class mesh;
class drawable;
class texture;

class renderer
{
public:
    explicit renderer();
    std::shared_ptr<camera> create_camera();
    std::shared_ptr<mesh> create_mesh(const mesh_data &data);
    std::shared_ptr<mesh> load_mesh(const char *name);
    std::shared_ptr<drawable> create_drawable();
    std::shared_ptr<texture> create_texture(const texture_data &data);
    std::shared_ptr<texture> load_texture(const char *name);
    void attach_camera(const std::shared_ptr<camera> &camera);
    void attach_drawable(const std::shared_ptr<drawable> &drawable);
    void render_frame();

private:
    std::shared_ptr<camera> m_camera;
    std::vector<std::shared_ptr<drawable>> m_drawable_list;
    GLuint m_program = 0;
    render_context m_program_context;
};

}

#endif // RENDERER_H
