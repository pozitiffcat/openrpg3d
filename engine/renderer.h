#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include <memory>

#include "mesh_def.h"

namespace engine {

class camera;
class mesh;
class drawable;

class renderer
{
public:
    std::shared_ptr<camera> create_camera();
    std::shared_ptr<mesh> create_mesh(const mesh_def &def);
    std::shared_ptr<drawable> create_drawable();
    void attach_camera(const std::shared_ptr<camera> &camera);
    void attach_drawable(const std::shared_ptr<drawable> &drawable);
    void render_frame();

private:
    std::shared_ptr<camera> m_camera;
    std::list<std::shared_ptr<drawable>> m_drawable_list;
};

}

#endif // RENDERER_H
