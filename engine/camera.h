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

private:
    void render(const render_context &context);

private:
    glm::mat4 m_projection_matrix = glm::mat4(1.0);
    glm::mat4 m_view_matrix = glm::mat4(1.0);
};

}

#endif // CAMERA_H
