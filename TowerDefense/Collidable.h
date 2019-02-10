#ifndef COLLIDABLE_H
#define COLLIDABLE_H
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/func_geometric.hpp>

class Collidable
{
private:
	float m_radius;

public:

	Collidable(float radius)
	{
		m_radius = radius;
	}

	virtual glm::vec3 get_center() = 0;

	virtual bool collides_with(Collidable* other)
	{
		return glm::distance(other->get_center(), get_center()) <= m_radius + other->m_radius;
	}
};

#endif