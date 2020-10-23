#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "movable.h"

#include <list>

namespace engine {

class mesh;

class drawable : public movable
{
public:
    void attach_mesh(const std::shared_ptr<mesh> &mesh);

private:
    std::list<std::shared_ptr<mesh>> m_mesh_list;
};

}

#endif // DRAWABLE_H
