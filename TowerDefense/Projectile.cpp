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

void Projectile::update(Game* game)
{
	
}

void Projectile::draw_geometry(Renderer* renderer)
{
	renderer->draw_geometry_node(m_projectile, m_transformation_matrix, m_transformation_matrix_normal);
}

void Projectile::draw_geometry_to_shadow_map(Renderer* renderer)
{
	renderer->draw_geometry_node_to_shadow_map(m_projectile, m_transformation_matrix, m_transformation_matrix_normal);
}

glm::vec3 Projectile::get_pos()
{
	return this->m_position;
}