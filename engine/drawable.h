#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "movable.h"

#include <vector>
#include "render_context.h"
#include "material_data.h"

namespace engine {

class mesh;
class renderer;

class drawable : public movable
{
    friend class renderer;
public:
    void attach_mesh(const std::shared_ptr<mesh> &mesh);
    void attach_material(const material_data &material);

private:
    void render(const render_context &context);

private:
    std::shared_ptr<mesh> m_mesh;
    material_data m_material;
};

}

#endif // DRAWABLE_H
