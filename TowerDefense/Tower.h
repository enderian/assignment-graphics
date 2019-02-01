#ifndef TOWER_H
#define TOWER_H

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"

class Tower : public GameObject
{
private:

	class GeometryNode* m_tower;
	glm::mat4 m_transformation_matrix;
	glm::mat4 m_transformation_matrix_normal;
	glm::vec3 pos;

	bool used = false;

	float ready;

public:
	Tower(float ready);
	virtual ~Tower();

	static bool InitializeMeshes();

	void SetPosition(glm::vec3 position);
	void SetUsed(bool used);
	void Update(Game* game) override;
	void DrawGeometry(class Renderer* renderer) override;
	void DrawGeometryToShadowMap(class Renderer* renderer) override;

	void setUsed(bool used);

	bool IsUsed();
	glm::vec3 GetPos();
};

#endif