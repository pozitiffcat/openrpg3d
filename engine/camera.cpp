#include "camera.h"

#include <GL/glew.h>
#include <glm/ext.hpp>

namespace engine {

camera::camera()
{
    m_projection_matrix = glm::perspective(glm::degrees(70.0), 1.3, 1.0, 100.0);
}

void camera::render(const render_context &context)
{
    glClearColor(0.2, 0.3, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto global_matrix = get_global_matrix();

    m_view_matrix = glm::lookAt(glm::vec3(global_matrix[3]), glm::vec3(global_matrix[3] + global_matrix[2]), glm::vec3(0, 1, 0));

    if (context.proj_matrix_uniform != -1)
        glUniformMatrix4fv(context.proj_matrix_uniform, 1, false, glm::value_ptr(m_projection_matrix));

    if (context.view_matrix_uniform != - 1)
        glUniformMatrix4fv(context.view_matrix_uniform, 1, false, glm::value_ptr(m_view_matrix));

    if (context.proj_view_matrix_uniform != - 1)
        glUniformMatrix4fv(context.proj_view_matrix_uniform, 1, false, glm::value_ptr(m_projection_matrix * m_view_matrix));
}

}
