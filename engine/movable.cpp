#include "movable.h"

#include <glm/ext.hpp>

void engine::movable::set_parent(const std::shared_ptr<engine::movable> &parent)
{
    m_parent = parent;
}

void engine::movable::set_position(float x, float y, float z)
{
    m_position = glm::vec3(x, y, z);
}

void engine::movable::set_rotation(float x, float y, float z)
{
    m_rotation = glm::vec3(x, y, z);
}

void engine::movable::set_scale(float x, float y, float z)
{
    m_scale = glm::vec3(x, y, z);
}

glm::mat4 engine::movable::get_global_matrix() const
{
    auto matrix = glm::translate(glm::mat4(1.0), m_position);
    matrix = glm::rotate(matrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
    matrix = glm::scale(matrix, m_scale);

    if (m_parent == nullptr) {
        return matrix;
    } else {
        return m_parent->get_global_matrix() * matrix;
    }
}
