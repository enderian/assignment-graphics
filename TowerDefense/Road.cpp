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

void Road::Update(Game* game)
{
}

void Road::DrawGeometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_road, m_transformation_matrix, m_transformation_matrix_normal);
}

void Road::DrawGeometryToShadowMap(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_road, m_transformation_matrix, m_transformation_matrix_normal);
}