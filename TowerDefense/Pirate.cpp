#include "Pirate.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OBJLoader.h"
#include "Projectile.h"
#include <iostream>

GeometricMesh* m_body_mesh;
GeometricMesh* m_arm_mesh;
GeometricMesh* m_left_foot_mesh;
GeometricMesh* m_right_foot_mesh;

Pirate::Pirate(): Collidable(PIRATE_SCALE * 12.87075f)
{
	m_body = new GeometryNode();
	m_body->Init(m_body_mesh);
	m_arm = new GeometryNode();
	m_arm->Init(m_arm_mesh);
	m_left_foot = new GeometryNode();
	m_left_foot->Init(m_left_foot_mesh);
	m_right_foot = new GeometryNode();
	m_right_foot->Init(m_right_foot_mesh);

	m_health = PIRATE_INITIAL_HEALTH;
}

Pirate::Pirate(float spawn_time): Pirate()
{
	m_spawn_time = spawn_time;
}

Pirate::~Pirate()
{
	delete m_body;
	delete m_arm;
	delete m_left_foot;
	delete m_right_foot;
}

bool Pirate::initialize_meshes(OBJLoader& loader)
{
	m_body_mesh = loader.load("../assets/Pirate/pirate_body.obj");
	m_arm_mesh = loader.load("../assets/Pirate/pirate_arm.obj");
	m_left_foot_mesh = loader.load("../assets/Pirate/pirate_left_foot.obj");
	m_right_foot_mesh = loader.load("../assets/Pirate/pirate_right_foot.obj");
	return true;
}

void Pirate::update(Game* game)
{
	//Calculate the current tile.

	int current_tile = (game->time() - m_spawn_time) / PIRATE_SPEED;
	auto alpha = fmod(game->time() - m_spawn_time, PIRATE_SPEED) / PIRATE_SPEED;

	auto translate = glm::mat4(1);
	auto scale = glm::scale(glm::mat4(1), glm::vec3(PIRATE_SCALE));
	auto rotation = glm::mat4(1);

	glm::vec3 position;

	if (current_tile >= 28)
	{
		current_tile = 28;
		position = game_tiles[current_tile];
		translate = glm::translate(translate, position);
		rotation = glm::inverse(glm::lookAt(game_tiles[current_tile - 1], game_tiles[current_tile], glm::vec3(0, 1, 0)));
	} 
	else
	{
		position = glm::mix(game_tiles[current_tile], game_tiles[current_tile + 1], alpha);
		translate = glm::translate(translate, position);
		rotation = glm::inverse(glm::lookAt(game_tiles[current_tile], game_tiles[current_tile + 1], glm::vec3(0, 1, 0)));
	}

	set_position(position);
	m_transformation_matrix = rotation * translate * scale;

	m_body_transformation_matrix = m_transformation_matrix * glm::mat4(1);

	auto hand_rotation = glm::rotate(glm::mat4(1), glm::sin((game->time() - m_spawn_time) * 2) * 0.1f, glm::vec3(1, 0, 0));
	m_arm_transformation_matrix = m_transformation_matrix * glm::translate(glm::mat4(1), glm::vec3(4.5, 12, 0)) * hand_rotation;

	auto feet_rotation = glm::rotate(glm::mat4(1), glm::sin((game->time() - m_spawn_time) * 4), glm::vec3(1, 0, 0));
	m_left_foot_transformation_matrix = m_transformation_matrix * feet_rotation * glm::translate(glm::mat4(1), glm::vec3(-4, 0, -2));
	feet_rotation = glm::inverse(feet_rotation);
	m_right_foot_transformation_matrix = m_transformation_matrix * feet_rotation * glm::translate(glm::mat4(1), glm::vec3(4, 0, -2));

	m_body_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_body_transformation_matrix))));;
	m_arm_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_arm_transformation_matrix))));
	m_left_foot_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_left_foot_transformation_matrix))));
	m_right_foot_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_right_foot_transformation_matrix))));

	//Handle death scenario.
	if (m_health <= 0)
	{
		//game->KillPirate(this);
	}
}

void Pirate::draw_geometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_body, m_body_transformation_matrix, m_body_transformation_matrix_normal);
	renderer->DrawGeometryNode(m_arm, m_arm_transformation_matrix, m_arm_transformation_matrix_normal);
	renderer->DrawGeometryNode(m_left_foot, m_left_foot_transformation_matrix, m_left_foot_transformation_matrix_normal);
	renderer->DrawGeometryNode(m_right_foot, m_right_foot_transformation_matrix, m_right_foot_transformation_matrix_normal);
}

void Pirate::draw_geometry_to_shadow_map(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_body, m_body_transformation_matrix, m_body_transformation_matrix_normal);
	renderer->DrawGeometryNodeToShadowMap(m_arm, m_arm_transformation_matrix, m_arm_transformation_matrix_normal);
	renderer->DrawGeometryNodeToShadowMap(m_left_foot, m_left_foot_transformation_matrix, m_left_foot_transformation_matrix_normal);
	renderer->DrawGeometryNodeToShadowMap(m_right_foot, m_right_foot_transformation_matrix, m_right_foot_transformation_matrix_normal);
}

glm::vec3 Pirate::get_center()
{
	return position() + PIRATE_SCALE * glm::vec3(-0.5957, 11.683, -4.274);
}
