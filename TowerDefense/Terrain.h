#ifndef TERRAIN_H
#define TERRAIN_H

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"

class Terrain : public GameObject
{
private:
	GeometryNode* m_terrain;
	glm::mat4 m_transformation_matrix;
	glm::mat4 m_transformation_matrix_normal;

public:
	Terrain();
	virtual ~Terrain();

	static bool InitializeMeshes();

	void SetPosition(glm::vec3 position);
	void update(Game* game) override;
	void draw_geometry(class Renderer* renderer) override;
	void draw_geometry_to_shadow_map(class Renderer* renderer) override;

};

#endif