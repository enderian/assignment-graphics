#include "Tower.h"
#include "Pirate.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"
#include <iostream>

Tower::Tower(float time)
{
	m_tower = new GeometryNode();
	ready = time;
}

Tower::~Tower()
{
	delete m_tower;
}

void Tower::draw_geometry(Renderer* renderer)
{
	renderer->draw_geometry_node(m_tower, m_transformation_matrix, m_transformation_matrix_normal);
}

void Tower::draw_geometry_to_shadow_map(Renderer* renderer)
{
	renderer->draw_geometry_node_to_shadow_map(m_tower, m_transformation_matrix, m_transformation_matrix_normal);
}

void Tower::SetPosition(glm::vec3 position)
{
	
}

void Tower::update(Game* game)
{

}


void Tower::SetUsed(bool used)
{
	this->used = used;
}

bool Tower::IsUsed()
{
	return this->used;
}

glm::vec3 Tower::GetPos()
{
	return this->pos;
}