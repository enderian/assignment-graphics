#ifndef PIRATE_H
#define PIRATE_H

#define SECONDS_PER_TILE 1.0f

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"

class Pirate : public GameObject
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

	glm::vec3 pos;

	int m_current_tile = 0;

	float spawn_time;

	int health = 50;

public:
	Pirate();
	Pirate(float spawn_time);
	virtual ~Pirate();

	float getTime();

	static bool InitializeMeshes();

	void Update(Game* game) override;
	void DrawGeometry(Renderer* renderer) override;
	void DrawGeometryToShadowMap(Renderer* renderer) override;
	void SetPosition(glm::vec3 pos);
	
	glm::vec3 GetPosAt(float dt);
	glm::vec3 GetPos();
};
#endif // PIRATE_H
