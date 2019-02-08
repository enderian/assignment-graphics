#ifndef CANNONBALL_H
#define CANNONBALL_H

#include "Projectile.h"

class CannonBall : public Projectile
{
private:
	glm::vec3 direction;
	float time;

public:
	CannonBall();

	CannonBall(glm::vec3 direction, float time);

	static bool InitializeMeshes();

	void SetPosition(glm::vec3 position);
	void Update(Game* game) override;

};

#endif
