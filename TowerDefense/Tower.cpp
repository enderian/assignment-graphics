#include "Tower.h"
#include "Pirate.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OBJLoader.h"
#include <iostream>

GeometricMesh* m_tower_mesh;

bool Tower::initialize_meshes(OBJLoader& loader)
{
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

void Tower::set_position(const glm::vec3& highp_vec3)
{
	GameObject::set_position(highp_vec3);
	m_transformation_matrix = glm::translate(glm::mat4(1), highp_vec3);
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(TOWER_SCALE));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void Tower::draw_geometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_tower, m_transformation_matrix, m_transformation_matrix_normal);
}

void Tower::draw_geometry_to_shadow_map(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_tower, m_transformation_matrix, m_transformation_matrix_normal);
}

void Tower::update(Game* game)
{
	if (m_used)
	{
		for (auto pirate : game->pirates())
		{
			if (glm::distance(pirate->get_center(), shoot_from()) < TOWER_SHOOT_DISTANCE)
			{
				std::cout << "Shoot!" << std::endl;
				game->spawn_projectile(shoot_from(), pirate->position(), this);
			}
		}
	}
}


glm::vec3 Tower::shoot_from()
{
	return position() + TOWER_SCALE * glm::vec3(-0.0101, 9.5, -0.0758);
}