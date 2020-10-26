#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "render_context.h"
#include "movable.h"

namespace engine {

class renderer;

class camera : public movable
{
    friend class renderer;
public:
    explicit camera();
    void set_viewport(int x, int y, unsigned short width, unsigned short height);

private:
    void update_projection_matrix();
    void render(const render_context &context);

private:
    glm::mat4 m_projection_matrix = glm::mat4(1.0);
    glm::mat4 m_view_matrix = glm::mat4(1.0);
    int m_viewport_x = 0;
    int m_viewport_y = 0;
    unsigned short m_viewport_width = 100;
    unsigned short m_viewport_height = 100;
    double m_fov = 75.0;
    double m_near = 1.0;
    double m_far = 100.0;
};

}

#endif // CAMERA_H
