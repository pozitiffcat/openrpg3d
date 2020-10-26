#ifndef MOVABLE_H
#define MOVABLE_H

#include <memory>

#include <glm/glm.hpp>

namespace engine {

class movable
{
public:
    virtual ~movable() = default;
    void set_parent(const std::shared_ptr<movable> &parent);
    void set_position(float x, float y, float z);
    void set_rotation(float x, float y, float z);
    void set_scale(float x, float y, float z);

protected:
    glm::mat4 get_global_matrix() const;

private:
    void update_local_matrix();

private:
    std::shared_ptr<movable> m_parent;
    glm::vec3 m_position = glm::vec3(0, 0, 0);
    glm::vec3 m_rotation = glm::vec3(0, 0, 0);
    glm::vec3 m_scale = glm::vec3(1, 1, 1);
    glm::mat4 m_local_matrix = glm::mat4(1.0);
};

}

#endif // MOVABLE_H
