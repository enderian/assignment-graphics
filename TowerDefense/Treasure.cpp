#include "Treasure.h"
#include "Pirate.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OBJLoader.h"
#include <iostream>

GeometricMesh* m_treasure_mesh;

bool Treasure::initialize_meshes(OBJLoader& loader)
{
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

void Treasure::set_position(const glm::vec3& highp_vec3)
{
	GameObject::set_position(highp_vec3);
	m_transformation_matrix = glm::translate(glm::mat4(1), highp_vec3);
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(0.2));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void Treasure::update(Game* game)
{
	
}

void Treasure::draw_geometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_treasure, m_transformation_matrix, m_transformation_matrix_normal);
}

void Treasure::draw_geometry_to_shadow_map(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_treasure, m_transformation_matrix, m_transformation_matrix_normal);
}