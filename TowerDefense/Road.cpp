#include "Road.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"

GeometricMesh* m_road_mesh;

bool Road::InitializeMeshes()
{
	OBJLoader loader;
	m_road_mesh = loader.load("../assets/Terrain/road.obj");
	return true;
}

Road::Road()
{
	m_road = new GeometryNode();
	m_road->Init(m_road_mesh);
}

Road::~Road()
{
	delete m_road;
}


void Road::SetPosition(glm::vec3 position)
{
	m_transformation_matrix = glm::translate(glm::mat4(1), position * glm::vec3(4));
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(2, 2, 2));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void Road::update(Game* game)
{
}

void Road::draw_geometry(Renderer* renderer)
{
	renderer->draw_geometry_node(m_road, m_transformation_matrix, m_transformation_matrix_normal);
}

void Road::draw_geometry_to_shadow_map(Renderer* renderer)
{
	renderer->draw_geometry_node_to_shadow_map(m_road, m_transformation_matrix, m_transformation_matrix_normal);
}