#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "movable.h"

#include <list>
#include "render_context.h"

namespace engine {

class mesh;
class renderer;

class drawable : public movable
{
    friend class renderer;
public:
    void attach_mesh(const std::shared_ptr<mesh> &mesh);

private:
    void render(const render_context &context);

private:
    std::list<std::shared_ptr<mesh>> m_mesh_list;
};

}

#endif // DRAWABLE_H
