#include "TowerMed.h"
#include "Pirate.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"
#include <iostream>

GeometricMesh* m_tower_mesh;

bool TowerMed::InitializeMeshes()
{
	OBJLoader loader;
	m_tower_mesh = loader.load("../assets/MedievalTower/tower.obj");
	return true;
}

TowerMed::TowerMed(float time) : Tower(time)
{
	m_tower->Init(m_tower_mesh);
}

void TowerMed::SetPosition(glm::vec3 position)
{
	this->pos = position;
	m_transformation_matrix = glm::translate(glm::mat4(1), position*glm::vec3(4));
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(0.4));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void TowerMed::SetUsed(bool used)
{
	this->used = used;
}

void TowerMed::Update(Game* game)
{
	if (used)
	{
		std::vector<Pirate*> pirates = game->m_pirates1();
		for (Pirate* p : pirates)
		{
			if ((glm::abs(p->GetPos().x - this->pos.x) <= 1.2) && (glm::abs(p->GetPos().z - this->pos.z) <= 1.2) && (game->time() - ready) >= 1)
			{
				//printf("Here\n");
				game->SpawnProjectile(pos, glm::vec3(ceil(p->GetPos().x), p->GetPos().y + 1.40196, ceil(p->GetPos().z)), this);
				ready = game->time();
			}
		}
	}
}