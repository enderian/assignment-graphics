#include "Tower.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"

GeometricMesh* m_tower_mesh;

bool Tower::InitializeMeshes()
{
	OBJLoader loader;
	m_tower_mesh = loader.load("../assets/MedievalTower/tower.obj");
	return true;
}

Tower::Tower()
{
	m_tower = new GeometryNode();
	m_tower->Init(m_tower_mesh);
}

Tower::~Tower()
{
	delete m_tower;
}

void Tower::SetPosition(glm::vec3 position)
{
	m_transformation_matrix = glm::translate(glm::mat4(1), position*glm::vec3(4));
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(0.6));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void Tower::Update(Game* game)
{
	
}

void Tower::DrawGeometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_tower, m_transformation_matrix, m_transformation_matrix_normal);
}

void Tower::DrawGeometryToShadowMap(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_tower, m_transformation_matrix, m_transformation_matrix_normal);
}




