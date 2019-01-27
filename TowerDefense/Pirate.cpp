#include "Pirate.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"
#include <iostream>

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

	auto translate = glm::mat4(1);
	auto scale = glm::scale(glm::mat4(1), glm::vec3(0.12f));
	auto rotation = glm::mat4(1);

	if (m_current_tile == 28)
	{
		translate = glm::translate(translate, game_tiles[m_current_tile] * glm::vec3(4));
		pos = game_tiles[m_current_tile];
	} else
	{
		const float alpha = std::fmod((game->time() - spawn_time) / SECONDS_PER_TILE, SECONDS_PER_TILE) / SECONDS_PER_TILE;
		translate = glm::translate(translate, glm::mix(game_tiles[m_current_tile], game_tiles[m_current_tile + 1], alpha) * glm::vec3(4));
		rotation = glm::inverse(glm::lookAt(game_tiles[m_current_tile], game_tiles[m_current_tile + 1], glm::vec3(0, 1, 0)));
		pos = glm::mix(game_tiles[m_current_tile], game_tiles[m_current_tile + 1], alpha);
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

glm::vec3 Pirate::GetPos()
{
	return this->pos;
}