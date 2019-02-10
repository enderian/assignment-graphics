#ifndef PIRATE_H
#define PIRATE_H

#define PIRATE_SPEED 5.0f
#define PIRATE_INITIAL_HEALTH 100.0f
#define PIRATE_SCALE 0.12f

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"
#include "Collidable.h"

class OBJLoader;

class Pirate : public GameObject, public Collidable
{
	glm::mat4 m_transformation_matrix;

	class GeometryNode* m_body;
	glm::mat4 m_body_transformation_matrix;
	glm::mat4 m_body_transformation_matrix_normal;

	class GeometryNode* m_arm;
	glm::mat4 m_arm_transformation_matrix;
	glm::mat4 m_arm_transformation_matrix_normal;

	class GeometryNode* m_left_foot;
	glm::mat4 m_left_foot_transformation_matrix;
	glm::mat4 m_left_foot_transformation_matrix_normal;

	class GeometryNode* m_right_foot;
	glm::mat4 m_right_foot_transformation_matrix;
	glm::mat4 m_right_foot_transformation_matrix_normal;

	int m_current_tile = 0;
	float m_spawn_time;
	float m_health;

public:
	Pirate();
	Pirate(float spawn_time);
	virtual ~Pirate();

	static bool initialize_meshes(OBJLoader& loader);

	glm::vec3 location_at(float time) const;

	void update(Game* game) override;
	void draw_geometry(Renderer* renderer) override;
	void draw_geometry_to_shadow_map(Renderer* renderer) override;

	glm::vec3 get_center() override;
};
#endif // PIRATE_H
