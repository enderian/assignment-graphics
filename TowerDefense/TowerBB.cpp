#include "TowerBB.h"
#include "Pirate.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>

GeometricMesh* m_towerBB_mesh;

bool TowerBB::InitializeMeshes()
{
	OBJLoader loader;
	m_towerBB_mesh = loader.load("../assets/MedievalTower/tower.obj");
	return true;
}

TowerBB::TowerBB(float time) : Tower(time)
{
	m_tower->Init(m_towerBB_mesh);
}

void TowerBB::SetPosition(glm::vec3 position)
{
	this->pos = position;
	m_transformation_matrix = glm::translate(glm::mat4(1), position*glm::vec3(4));
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(0.65));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void TowerBB::SetUsed(bool used)
{
	this->used = used;
}

void TowerBB::update(Game* game)
{
	if (used && !game->get_game_over())
	{
		std::vector<Pirate*> pirates = game->m_pirates1();
		for (Pirate* p : pirates)
		{
			if ((glm::abs(p->GetPos().x - this->pos.x) <= 4) && (glm::abs(p->GetPos().z - this->pos.z) <= 4) && (game->time() - ready) >= 1)
			{
				auto pos = p->GetPosAt(game->time() + 1.0f);
				game->spawn_projectile(pos, glm::vec3(ceil(pos.x), pos.y + 1.40196, ceil(pos.z)), this);
				ready = game->time();
			}
		}
	}
}