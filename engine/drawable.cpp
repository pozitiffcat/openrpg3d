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

    if (context.model_matrix_uniform != -1)
        glUniformMatrix4fv(context.model_matrix_uniform, 1, false, glm::value_ptr(global_matrix));

    if (context.normal_matrix_uniform != -1)
        glUniformMatrix3fv(context.normal_matrix_uniform, 1, false, glm::value_ptr(glm::inverseTranspose(glm::mat3(global_matrix))));

    for (auto mesh : m_mesh_list) {
        mesh->render(context);
    }
}

}
