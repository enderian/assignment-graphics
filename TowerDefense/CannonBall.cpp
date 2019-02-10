#include "CannonBall.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OBJLoader.h"
#include "Tower.h"
#include "Pirate.h"

GeometricMesh* m_cannonball_mesh;

bool CannonBall::initialize_meshes(OBJLoader& loader)
{
	m_cannonball_mesh = loader.load("../assets/Various/cannonball.obj");
	return true;
}

CannonBall::CannonBall() : Collidable(1.0 * CANNONBALL_SCALE)
{
	m_projectile->Init(m_cannonball_mesh);
}

CannonBall::CannonBall(glm::vec3 origin, glm::vec3 target, float time): CannonBall()
{
	this->m_origin = origin;
	this->m_target = target;
	this->m_spawn_time = time;
}

void CannonBall::update(Game* game)
{
	const float alpha = game->time() - this->m_spawn_time / 2.0f;
	set_position(glm::mix(this->m_origin, this->m_target, alpha));

	m_transformation_matrix = glm::translate(glm::mat4(1), position());
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(CANNONBALL_SCALE));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

glm::vec3 CannonBall::get_center()
{
	return position() + CANNONBALL_SCALE * glm::vec3(1);
}
