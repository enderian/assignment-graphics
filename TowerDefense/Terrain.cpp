#include "Terrain.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OBJLoader.h"

GeometricMesh* m_terrain_mesh;

bool Terrain::initialize_meshes(OBJLoader& loader)
{
	m_terrain_mesh = loader.load("../assets/Terrain/terrain.obj");
	return true;
}

Terrain::Terrain(): Collidable(0.0f)
{
	m_terrain = new GeometryNode();
	m_terrain->Init(m_terrain_mesh);
}

Terrain::~Terrain()
{
	delete m_terrain;
}


void Terrain::set_position(const glm::vec3& highp_vec3)
{
	GameObject::set_position(highp_vec3);
	m_transformation_matrix = glm::translate(glm::mat4(1), highp_vec3);
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(20));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void Terrain::update(Game* game)
{

}

void Terrain::draw_geometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_terrain, m_transformation_matrix, m_transformation_matrix_normal);
}

void Terrain::draw_geometry_to_shadow_map(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_terrain, m_transformation_matrix, m_transformation_matrix_normal);
}

bool Terrain::collides_with(Collidable* other)
{
	return other->get_center().y <= 0;
}

glm::vec3 Terrain::get_center()
{
	return glm::vec3(0);
}