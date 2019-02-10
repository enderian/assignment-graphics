#include "Projectile.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"

Projectile::Projectile()
{
	m_projectile = new GeometryNode();
}

Projectile::~Projectile()
{
	delete m_projectile;
}

void Projectile::Update(Game* game)
{
	
}

void Projectile::DrawGeometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_projectile, m_transformation_matrix, m_transformation_matrix_normal);
}

void Projectile::DrawGeometryToShadowMap(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_projectile, m_transformation_matrix, m_transformation_matrix_normal);
}

void Projectile::SetHit(bool hit)
{
	this->hit = hit;
}


glm::vec3 Projectile::GetPos()
{
	return this->pos;
}

bool Projectile::GetHit()
{
	return this->hit;
}
