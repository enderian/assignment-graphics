#ifndef ROAD_H
#define ROAD_H

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"

class Road: public GameObject
{
private:

	class GeometryNode* m_road;
	glm::mat4 m_transformation_matrix;
	glm::mat4 m_transformation_matrix_normal;

public:
	Road();
	virtual ~Road();

	static bool InitializeMeshes();

	void SetPosition(glm::vec3 position);
	void update(Game* game) override;
	void draw_geometry(class Renderer* renderer) override;
	void draw_geometry_to_shadow_map(class Renderer* renderer) override;
};

#endif // ROAD_H
