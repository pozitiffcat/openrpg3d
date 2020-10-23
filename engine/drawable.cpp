#include "drawable.h"

#include <glm/ext.hpp>
#include "mesh.h"

namespace engine {

void drawable::attach_mesh(const std::shared_ptr<mesh> &mesh)
{
    m_mesh_list.push_back(mesh);
}

void drawable::render(const render_context &context)
{
    auto global_matrix = get_global_matrix();
    auto normal_matrix = glm::inverseTranspose(glm::mat3(global_matrix));

    glUniformMatrix4fv(context.model_matrix_uniform, 1, false, glm::value_ptr(global_matrix));
    glUniformMatrix3fv(context.normal_matrix_uniform, 1, false, glm::value_ptr(normal_matrix));

    for (auto mesh : m_mesh_list) {
        mesh->render(context);
    }
}

}
