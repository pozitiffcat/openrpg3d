#include "drawable.h"

#include <glm/ext.hpp>
#include "mesh.h"
#include "texture.h"

namespace engine {

void drawable::attach_mesh(const std::shared_ptr<mesh> &mesh)
{
    m_mesh = mesh;
}

void drawable::attach_material(const material_data &material)
{
    m_material = material;
}

void drawable::render(const render_context &context)
{
    auto global_matrix = get_global_matrix();

    if (context.model_matrix_uniform != -1)
        glUniformMatrix4fv(context.model_matrix_uniform, 1, false, glm::value_ptr(global_matrix));

    if (context.normal_matrix_uniform != -1)
        glUniformMatrix3fv(context.normal_matrix_uniform, 1, false, glm::value_ptr(glm::inverseTranspose(glm::mat3(global_matrix))));

    // diffuse

    glActiveTexture(GL_TEXTURE0);
    if (context.diffuse_texture_uniform != -1 && m_material.diffuse_texture != nullptr)
        m_material.diffuse_texture->bind();
    else
        context.default_diffuse_texture->bind();
    glUniform1i(context.diffuse_texture_uniform, 0);

    // normal

    glActiveTexture(GL_TEXTURE1);
    if (context.normal_texture_uniform != -1 && m_material.normal_texture != nullptr)
        m_material.normal_texture->bind();
    else
        context.default_normal_texture->bind();
    glUniform1i(context.normal_texture_uniform, 1);

    // roughness

    glActiveTexture(GL_TEXTURE2);
    if (context.roughness_texture_uniform != -1 && m_material.roughness_texture != nullptr)
        m_material.roughness_texture->bind();
    else
        context.default_roughness_texture->bind();
    glUniform1i(context.roughness_texture_uniform, 2);

    // occlussion

    glActiveTexture(GL_TEXTURE3);
    if (context.occlusion_texture_uniform != -1 && m_material.occlusion_texture != nullptr)
        m_material.occlusion_texture->bind();
    else
        context.default_occlusion_texture->bind();
    glUniform1i(context.occlusion_texture_uniform, 3);

    m_mesh->render(context);
}

}
