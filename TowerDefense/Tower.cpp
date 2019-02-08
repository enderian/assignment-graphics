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

void Tower::DrawGeometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_tower, m_transformation_matrix, m_transformation_matrix_normal);
}

void Tower::DrawGeometryToShadowMap(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_tower, m_transformation_matrix, m_transformation_matrix_normal);
}

void Tower::SetPosition(glm::vec3 position)
{
	
}

void Tower::Update(Game* game)
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