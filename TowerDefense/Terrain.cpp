#include "Terrain.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"

GeometricMesh* m_terrain_mesh;

bool Terrain::InitializeMeshes()
{
	OBJLoader loader;
	m_terrain_mesh = loader.load("../assets/Terrain/terrain.obj");
	return true;
}

Terrain::Terrain()
{
	m_terrain = new GeometryNode();
	m_terrain->Init(m_terrain_mesh);
}

Terrain::~Terrain()
{
	delete m_terrain;
}

void Terrain::SetPosition(glm::vec3 position)
{
	m_transformation_matrix = glm::translate(glm::mat4(1), position);
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(20));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void Terrain::update(Game* game)
{

}

void Terrain::draw_geometry(Renderer* renderer)
{
	renderer->draw_geometry_node(m_terrain, m_transformation_matrix, m_transformation_matrix_normal);
}

void Terrain::draw_geometry_to_shadow_map(Renderer* renderer)
{
	renderer->draw_geometry_node_to_shadow_map(m_terrain, m_transformation_matrix, m_transformation_matrix_normal);
}