#ifndef CANNONBALL_H
#define CANNONBALL_H

#define CANNONBALL_SCALE 0.1f

#include "Projectile.h"
#include "Collidable.h"

class OBJLoader;

class CannonBall : public Projectile, public Collidable
{
private:
	glm::vec3 m_origin, m_target;
	float m_spawn_time;

public:
	CannonBall();
	CannonBall(glm::vec3 origin, glm::vec3 target, float spawn_time);

	static bool initialize_meshes(OBJLoader& loader);

	void update(Game* game) override;
	glm::vec3 get_center() override;
};

#endif
