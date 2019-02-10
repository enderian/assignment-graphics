#ifndef SELECTION_PLANE_H
#define SELECTION_PLANE_H

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"

class OBJLoader;

class SelectionPlane : public GameObject
{
private:

	class GeometryNode* m_plane_r;
	class GeometryNode* m_plane_g;
	class GeometryNode* curr_plane;

	glm::vec3 m_position;
	glm::mat4 m_transformation_matrix;
	glm::mat4 m_transformation_matrix_normal;

public:
	SelectionPlane();
	virtual ~SelectionPlane();

	static bool initialize_meshes(OBJLoader& loader);

	glm::vec3 position() const override;
	void set_position(const glm::vec3& highp_vec3) override;
	void update(Game* game) override;
	void draw_geometry(class Renderer* renderer) override;
	void draw_geometry_to_shadow_map(class Renderer* renderer) override;

	void move_up();
	void move_down();
	void move_left();
	void move_right();
};

#endif