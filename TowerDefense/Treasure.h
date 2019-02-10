#ifndef TREASURE_H
#define TREASURE_H

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"

class OBJLoader;

class Treasure : public GameObject
{
private:
	
	class GeometryNode* m_treasure;
	glm::mat4 m_transformation_matrix;
	glm::mat4 m_transformation_matrix_normal;
	glm::vec3 pos;

public:
	int coins = 100;
	Treasure();
	virtual ~Treasure();

	static bool initialize_meshes(OBJLoader& loader);

	void set_position(const glm::vec3& highp_vec3) override;
	void update(Game* game) override;
	void draw_geometry(class Renderer* renderer) override;
	void draw_geometry_to_shadow_map(class Renderer* renderer) override;

};


#endif
