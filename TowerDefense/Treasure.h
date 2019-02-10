#ifndef TREASURE_H
#define TREASURE_H

#include "GeometryNode.h"
#include "Pirate.h"
#include "Renderer.h"
#include "Game.h"

class Treasure : public GameObject
{
private:
	
	class GeometryNode* m_treasure;
	glm::mat4 m_transformation_matrix;
	glm::mat4 m_transformation_matrix_normal;

public:
	Treasure();
	virtual ~Treasure();

	static bool InitializeMeshes();

	void SetPosition(glm::vec3 position);
	void update(Game* game) override;
	void draw_geometry(class Renderer* renderer) override;
	void draw_geometry_to_shadow_map(class Renderer* renderer) override;

};


#endif
