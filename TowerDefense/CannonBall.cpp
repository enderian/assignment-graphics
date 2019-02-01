#include "CannonBall.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"
#include "Tower.h"

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


void CannonBall::Update(Game* game)
{
	//pos.x += ((this->direction.x - this->pos.x) >= 0 ? this->direction.x*0.009 : -this->direction.x*0.009);
	//pos.z += ((this->direction.z - this->pos.z) >= 0 ? this->direction.z*0.009 : -this->direction.z*0.009);
	const float alpha = (std::fmod((game->time() - this->time) / 1.0f, 1.0f) / 1.0f);
	pos = glm::mix(this->pos, this->direction, alpha);
	SetPosition(pos);
}
