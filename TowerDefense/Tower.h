#ifndef TOWER_H
#define TOWER_H

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"

class Tower : public GameObject
{
	
protected:
	float ready;
	bool used = false;
	class GeometryNode* m_tower;
	glm::mat4 m_transformation_matrix;
	glm::mat4 m_transformation_matrix_normal;
	glm::vec3 pos;

public:
	Tower(float ready);
	virtual ~Tower();

	static bool InitializeMeshes();

	virtual void SetPosition(glm::vec3 position);
	void SetUsed(bool used);
	void update(Game* game) override;
	void draw_geometry(class Renderer* renderer) override;
	void draw_geometry_to_shadow_map(class Renderer* renderer) override;

	bool IsUsed();
	glm::vec3 GetPos();
};

#endif