#ifndef TERRAIN_H
#define TERRAIN_H

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"
#include "Collidable.h"

class OBJLoader;

class Terrain : public GameObject, public Collidable
{
private:
	GeometryNode* m_terrain;
	glm::mat4 m_transformation_matrix;
	glm::mat4 m_transformation_matrix_normal;

public:
	Terrain();
	virtual ~Terrain();

	static bool initialize_meshes(OBJLoader& loader);

	void set_position(const glm::vec3& highp_vec3) override;
	void update(Game* game) override;
	void draw_geometry(class Renderer* renderer) override;
	void draw_geometry_to_shadow_map(class Renderer* renderer) override;

	glm::vec3 get_center() override;
	bool collides_with(Collidable* other) override;
};

#endif