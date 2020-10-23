#include "renderer.h"

#include <GL/glew.h>

#include "camera.h"
#include "mesh.h"
#include "drawable.h"

namespace engine {

std::shared_ptr<camera> renderer::create_camera()
{
    return std::make_shared<camera>();
}

std::shared_ptr<mesh> renderer::create_mesh(const mesh_def &def)
{
    GLuint buffer = 0;
    glGenBuffers(1, &buffer);
    return std::make_shared<mesh>(buffer);
}

std::shared_ptr<drawable> renderer::create_drawable()
{
    return std::make_shared<drawable>();
}

void renderer::attach_camera(const std::shared_ptr<camera> &camera)
{
    m_camera = camera;
}

void renderer::attach_drawable(const std::shared_ptr<drawable> &drawable)
{
    m_drawable_list.push_back(drawable);
}

void renderer::render_frame()
{
    glEnable(GL_DEPTH_TEST);

    if (m_camera != nullptr)
        m_camera->clear_screen();
}

}
