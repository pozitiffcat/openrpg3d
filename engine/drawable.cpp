#include "drawable.h"

#include "mesh.h"

namespace engine {

void drawable::attach_mesh(const std::shared_ptr<mesh> &mesh)
{
    m_mesh_list.push_back(mesh);
}

void drawable::render(const render_context &context)
{
    for (auto mesh : m_mesh_list) {
        mesh->render(context);
    }
}

}
