#include "Tower.h"
#include "Pirate.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"
#include <iostream>

GeometricMesh* m_tower_mesh;

bool Tower::InitializeMeshes()
{
	OBJLoader loader;
	m_tower_mesh = loader.load("../assets/MedievalTower/tower.obj");
	return true;
}

Tower::Tower(float time)
{
	m_tower = new GeometryNode();
	m_tower->Init(m_tower_mesh);
	ready = time;
}

Tower::~Tower()
{
	delete m_tower;
}

void Tower::SetPosition(glm::vec3 &position)
{
	this->pos = position;
	m_transformation_matrix = glm::translate(glm::mat4(1), position*glm::vec3(4));
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(0.4));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void Tower::SetUsed(bool used)
{
	this->used = used;
}

void Tower::Update(Game* game)
{
	if(used)
	{
		std::vector<Pirate*> pirates = game->GetPirates();
		for(Pirate* p: pirates)
		{
			if ((glm::abs(p->GetPos().x - this->pos.x) <= 1) && (glm::abs(p->GetPos().z - this->pos.z) <= 1) && (game->time() - ready) >= 0.5)
			{
				game->SpawnProjectile(pos, p->GetPos());
				ready = game->time();
			}
		}
	}
}

void Tower::DrawGeometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_tower, m_transformation_matrix, m_transformation_matrix_normal);
}

void Tower::DrawGeometryToShadowMap(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_tower, m_transformation_matrix, m_transformation_matrix_normal);
}

void Tower::setUsed(bool used)
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