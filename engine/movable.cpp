#include "movable.h"

#include <glm/ext.hpp>

void engine::movable::set_parent(const std::shared_ptr<engine::movable> &parent)
{
    m_parent = parent;
}

void engine::movable::set_position(float x, float y, float z)
{
    m_position = glm::vec3(x, y, z);
    update_local_matrix();
}

void engine::movable::set_rotation(float x, float y, float z)
{
    m_rotation = glm::vec3(x, y, z);
    update_local_matrix();
}

void engine::movable::set_scale(float x, float y, float z)
{
    m_scale = glm::vec3(x, y, z);
    update_local_matrix();
}

glm::mat4 engine::movable::get_global_matrix() const
{
    if (m_parent == nullptr) {
        return m_local_matrix;
    } else {
        return m_parent->get_global_matrix() * m_local_matrix;
    }
}

void engine::movable::update_local_matrix()
{
    m_local_matrix = glm::translate(glm::mat4(1.0), m_position);
    m_local_matrix = glm::rotate(m_local_matrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
    m_local_matrix = glm::rotate(m_local_matrix, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
    m_local_matrix = glm::rotate(m_local_matrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
    m_local_matrix = glm::scale(m_local_matrix, m_scale);
}
