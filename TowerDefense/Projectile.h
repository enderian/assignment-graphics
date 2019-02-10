#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"

class Projectile : public GameObject
{
private:

protected:
	glm::mat4 m_transformation_matrix;
	glm::mat4 m_transformation_matrix_normal;
	class GeometryNode* m_projectile;
	glm::vec3 pos;

public:
	Projectile();
	virtual ~Projectile();

	void update(Game* game) override;
	void draw_geometry(class Renderer* renderer) override;
	void draw_geometry_to_shadow_map(class Renderer* renderer) override;

	glm::vec3 GetPos();
};

#endif