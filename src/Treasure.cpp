#include "Treasure.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OBJLoader.h"

GeometricMesh* m_treasure_mesh;

bool Treasure::InitializeMeshes()
{
	OBJLoader loader;
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

void Treasure::SetPosition(glm::vec3 position)
{
	m_transformation_matrix = glm::translate(glm::mat4(1), position*glm::vec3(4));
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(0.1));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void Treasure::Update(Game* game)
{
	
}

void Treasure::DrawGeometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_treasure, m_transformation_matrix, m_transformation_matrix_normal);
}

void Treasure::DrawGeometryToShadowMap(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_treasure, m_transformation_matrix, m_transformation_matrix_normal);
}