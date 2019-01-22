#ifndef PLANERG_H
#define PLANERG_H

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"

class PlaneRG : public GameObject
{
private:

	class GeometryNode* m_plane_r;
	class GeometryNode* m_plane_g;
	class GeometryNode* curr_plane;
	glm::mat4 m_transformation_matrix;
	glm::mat4 m_transformation_matrix_normal;

public:
	glm::vec3 pos = glm::vec3(4, 0, 4);

	PlaneRG();
	virtual ~PlaneRG();

	static bool InitializeMeshes();

	void SetPosition(glm::vec3 position);
	void Update(Game* game) override;
	void DrawGeometry(class Renderer* renderer) override;
	void DrawGeometryToShadowMap(class Renderer* renderer) override;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
};

#endif