#ifndef BULLETBILL_H
#define BULLETBILL_H

#include "Projectile.h"
#include "Pirate.h"

class BulletBill : public Projectile
{
private:
	Pirate* pirate;
	glm::vec3 pos, direction;
	float time;

public:
	BulletBill();

	BulletBill(glm::vec3 dir, float time);

	static bool initialize_meshes();

	void set_position(glm::vec3 position);
	void update(Game* game) override;

};

#endif