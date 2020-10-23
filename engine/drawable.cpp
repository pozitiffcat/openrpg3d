#include "drawable.h"

namespace engine {

void drawable::attach_mesh(const std::shared_ptr<mesh> &mesh)
{
    m_mesh_list.push_back(mesh);
}

}
