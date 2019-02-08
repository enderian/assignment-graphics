#ifndef TOWER_MED_H
#define TOWER_MED_H

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"
#include "Tower.h"

class TowerMed : public Tower
{

public:
	TowerMed(float ready);

	static bool InitializeMeshes();

	void SetPosition(glm::vec3 position);
	void SetUsed(bool used);
	void Update(Game* game) override;
};

#endif