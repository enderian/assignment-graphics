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

CannonBall::CannonBall(glm::vec3 origin, glm::vec3 direction, float time)
{
	m_projectile->Init(m_cannonball_mesh);
	this->origin = origin;
	this->direction = direction;
	this->time = time;
}

void CannonBall::SetPosition(glm::vec3 position)
{
	this->m_position = position;
	m_transformation_matrix = glm::translate(glm::mat4(1), position*glm::vec3(4, 1, 4));
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(0.1));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void CannonBall::update(Game* game)
{
	const float alpha = (game->time() - this->time) / 0.2f;
	m_position = glm::mix(this->origin, this->direction, alpha);

	if (m_position.y < 0)
	{
		auto balls = game->m_projectiles1();
		for (auto it = balls.begin(); it != balls.end(); ++it) {
			if (*it == this) {
				balls.erase(it);
				game->set_m_projectiles(balls);
				delete this;
				return;
			}
		}
	}

	SetPosition(m_position);
}
