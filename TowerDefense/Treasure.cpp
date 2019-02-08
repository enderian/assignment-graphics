#include "Treasure.h"
#include "Pirate.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"
#include <iostream>

GeometricMesh* m_treasure_mesh;

bool Treasure::InitializeMeshes()
{
	OBJLoader loader;
	m_treasure_mesh = loader.load("../assets/Treasure/treasure_chest.obj");
	return true;
}

Treasure::Treasure()
{
	m_treasure = new GeometryNode();
	m_treasure->Init(m_treasure_mesh);
}

Treasure::~Treasure()
{
	delete m_treasure;
}

void Treasure::SetPosition(glm::vec3 position)
{
	this->pos = position;
	m_transformation_matrix = glm::translate(glm::mat4(1), position*glm::vec3(4));
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(0.1));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void Treasure::Update(Game* game)
{
	std::vector<Pirate*> m_pirates = game->GetPirates();
	glm::vec3 center(pos.x*(-.0176) + pos.x, pos.y*1.08174+pos.y, pos.z*(-.80619)+pos.z);
	for (int i = 0; i < m_pirates.size(); i++)
	{
		int erase = 0;
		glm::vec3 p_pos = m_pirates[i]->GetPos();
		glm::vec3 pirate_center(p_pos.x*(-.071464) + p_pos.x, p_pos.y*1.40196 + p_pos.y, p_pos.z*(-.51288) + p_pos.z);
		glm::vec3 dif(glm::abs(center - pirate_center));
		if (dif.x < .33 && dif.y < .33 && dif.z < .33)
		{
			coins -= 10;
			erase = i;
			m_pirates.erase(m_pirates.begin() + erase);
			game->SetPirates(m_pirates);
		}
	}
}

void Treasure::DrawGeometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_treasure, m_transformation_matrix, m_transformation_matrix_normal);
}

void Treasure::DrawGeometryToShadowMap(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_treasure, m_transformation_matrix, m_transformation_matrix_normal);
}