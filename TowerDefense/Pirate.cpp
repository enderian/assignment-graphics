#include "Pirate.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"
#include "Projectile.h"
#include "CannonBall.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>

#undef min
#undef max

GeometricMesh* m_body_mesh;
GeometricMesh* m_arm_mesh;
GeometricMesh* m_left_foot_mesh;
GeometricMesh* m_right_foot_mesh;

Pirate::Pirate()
{
	m_body = new GeometryNode();
	m_body->Init(m_body_mesh);
	m_arm = new GeometryNode();
	m_arm->Init(m_arm_mesh);
	m_left_foot = new GeometryNode();
	m_left_foot->Init(m_left_foot_mesh);
	m_right_foot = new GeometryNode();
	m_right_foot->Init(m_right_foot_mesh);
}

Pirate::Pirate(float spawn_time)
{
	m_body = new GeometryNode();
	m_body->Init(m_body_mesh);
	m_arm = new GeometryNode();
	m_arm->Init(m_arm_mesh);
	m_left_foot = new GeometryNode();
	m_left_foot->Init(m_left_foot_mesh);
	m_right_foot = new GeometryNode();
	m_right_foot->Init(m_right_foot_mesh);
	this->spawn_time = spawn_time;
}


Pirate::~Pirate()
{
	delete m_body;
	delete m_arm;
	delete m_left_foot;
	delete m_right_foot;
}

bool Pirate::InitializeMeshes()
{
	OBJLoader loader;
	m_body_mesh = loader.load("../assets/Pirate/pirate_body.obj");
	m_arm_mesh = loader.load("../assets/Pirate/pirate_arm.obj");
	m_left_foot_mesh = loader.load("../assets/Pirate/pirate_left_foot.obj");
	m_right_foot_mesh = loader.load("../assets/Pirate/pirate_right_foot.obj");
	return true;
}

void Pirate::Update(Game* game)
{
	m_current_tile = std::min(int((game->time() - spawn_time) / SECONDS_PER_TILE / SECONDS_PER_TILE), 28);
	pos = GetPosAt(game->time());

	auto translate = glm::translate(glm::mat4(1), pos * glm::vec3(4));
	auto scale = glm::scale(glm::mat4(1), glm::vec3(0.12f));
	auto rotation = glm::mat4(1);

	if (m_current_tile < 28) {
		rotation = glm::inverse(glm::lookAt(game_tiles[m_current_tile], game_tiles[m_current_tile + 1], glm::vec3(0, 1, 0)));
	}

	m_transformation_matrix = translate * scale * rotation;

	m_body_transformation_matrix = m_transformation_matrix * glm::mat4(1);
	auto hand_rotation = glm::rotate(glm::mat4(1), glm::sin((game->time() - spawn_time) * 2) * 0.1f, glm::vec3(1, 0, 0));
	m_arm_transformation_matrix = m_transformation_matrix * glm::translate(glm::mat4(1), glm::vec3(4.5, 12, 0)) * hand_rotation;

	auto feet_rotation = glm::rotate(glm::mat4(1), glm::sin((game->time() - spawn_time) * 4), glm::vec3(1, 0, 0));
	m_left_foot_transformation_matrix = m_transformation_matrix * feet_rotation * glm::translate(glm::mat4(1), glm::vec3(-4, 0, -2));
	feet_rotation = glm::inverse(feet_rotation);
	m_right_foot_transformation_matrix = m_transformation_matrix * feet_rotation * glm::translate(glm::mat4(1), glm::vec3(4, 0, -2));

	m_body_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_body_transformation_matrix))));;
	m_arm_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_arm_transformation_matrix))));
	m_left_foot_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_left_foot_transformation_matrix))));
	m_right_foot_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_right_foot_transformation_matrix))));

	std::vector<Projectile*> m_projectiles = game->GetCannonBalls();
	glm::vec3 center(pos.x*(-.071464) + pos.x, pos.y*1.40196 + pos.y, pos.z*(-.51288) + pos.z);
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		int erase = 0;
		glm::vec3 p_pos = m_projectiles[i]->GetPos();
		//std::cout << p_pos.x << " " << p_pos.y << " " << p_pos.z << std::endl;
		glm::vec3 dif(glm::abs(center - p_pos));
		//std::cout << dif.x << " " << dif.y << " " << dif.z << std::endl;
		if(dif.x < .52 && dif.y < 1.41 && dif.z < 3.01)
		{
			if(dynamic_cast<CannonBall*>(m_projectiles[i]) && !m_projectiles[i]->GetHit())
			{
				PlaySound(TEXT("../assets/Sounds/hit.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_PURGE);
				health -= 25;
				printf("KAPPA\n");
				m_projectiles[i]->SetHit(true);
			}
		}
	}
}

void Pirate::DrawGeometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_body, m_body_transformation_matrix, m_body_transformation_matrix_normal);
	renderer->DrawGeometryNode(m_arm, m_arm_transformation_matrix, m_arm_transformation_matrix_normal);
	renderer->DrawGeometryNode(m_left_foot, m_left_foot_transformation_matrix, m_left_foot_transformation_matrix_normal);
	renderer->DrawGeometryNode(m_right_foot, m_right_foot_transformation_matrix, m_right_foot_transformation_matrix_normal);
}

void Pirate::DrawGeometryToShadowMap(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_body, m_body_transformation_matrix, m_body_transformation_matrix_normal);
	renderer->DrawGeometryNodeToShadowMap(m_arm, m_arm_transformation_matrix, m_arm_transformation_matrix_normal);
	renderer->DrawGeometryNodeToShadowMap(m_left_foot, m_left_foot_transformation_matrix, m_left_foot_transformation_matrix_normal);
	renderer->DrawGeometryNodeToShadowMap(m_right_foot, m_right_foot_transformation_matrix, m_right_foot_transformation_matrix_normal);
}

void Pirate::SetPosition(glm::vec3 pos)
{
	this->pos = pos;
}

glm::vec3 Pirate::GetPos()
{
	return this->pos;
}

glm::vec3 Pirate::GetPosAt(float time)
{
	auto tile = std::min(int((time - spawn_time) / SECONDS_PER_TILE / SECONDS_PER_TILE), 28);

	if (m_current_tile == 28)
	{
		return game_tiles[tile];
	}
	else
	{
		const float alpha = std::fmod((time - spawn_time) / SECONDS_PER_TILE, SECONDS_PER_TILE) / SECONDS_PER_TILE;
		return glm::mix(game_tiles[m_current_tile], game_tiles[m_current_tile + 1], alpha);
	}
}
