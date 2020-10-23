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

void engine::movable::update_matrix()
{
    m_matrix = glm::translate(glm::mat4(1.0), m_position);
    m_matrix = glm::rotate(m_matrix, m_rotation.y, glm::vec3(0, 1, 0));
    m_matrix = glm::rotate(m_matrix, m_rotation.x, glm::vec3(1, 0, 0));
    m_matrix = glm::rotate(m_matrix, m_rotation.z, glm::vec3(0, 0, 1));
    m_matrix = glm::scale(m_matrix, m_scale);
}
