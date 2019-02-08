#include "CannonBall.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"
#include "Tower.h"
#include "Pirate.h"

GeometricMesh* m_cannonball_mesh;

bool CannonBall::InitializeMeshes()
{
	OBJLoader loader;
	m_cannonball_mesh = loader.load("../assets/Various/cannonball.obj");
	return true;
}

CannonBall::CannonBall() : Projectile()
{
	m_projectile->Init(m_cannonball_mesh);
}

CannonBall::CannonBall(glm::vec3 direction, float time)
{
	m_projectile->Init(m_cannonball_mesh);
	this->direction = direction;
	this->time = time;
}

void CannonBall::SetPosition(glm::vec3 position)
{
	this->pos = position;
	m_transformation_matrix = glm::translate(glm::mat4(1), position*glm::vec3(4, 1, 4));
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(0.1));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void CannonBall::Update(Game* game)
{
	//pos.x += ((this->direction.x - this->pos.x) >= 0 ? this->direction.x*0.009 : -this->direction.x*0.009);
	//pos.z += ((this->direction.z - this->pos.z) >= 0 ? this->direction.z*0.009 : -this->direction.z*0.009);
	const float alpha = (std::fmod((game->time() - this->time) / 1.0f, 1.0f) / 1.0f);
	pos = glm::mix(this->pos, this->direction, alpha);
	SetPosition(pos);
	
}
