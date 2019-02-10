#include "Projectile.h"
#include <glm/gtc/matrix_transform.hpp>
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
	//TODO FIND THE RELATIVE POSITIONS FOR THE PROJECTILE FROM THE TOWER
	/*pos.z += 0.001;
	pos.y -= 0.001;
	pos.x += 0.001;*/
	
	//SetPosition(pos);
}

void Projectile::draw_geometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_projectile, m_transformation_matrix, m_transformation_matrix_normal);
}

void Projectile::draw_geometry_to_shadow_map(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_projectile, m_transformation_matrix, m_transformation_matrix_normal);
}

glm::vec3 Projectile::GetPos()
{
	return this->pos;
}
