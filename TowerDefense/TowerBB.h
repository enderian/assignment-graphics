#ifndef TOWER_BB_H
#define TOWER_BB_H

#include "GeometryNode.h"
#include "Renderer.h"
#include "Game.h"
#include "Tower.h"

class TowerBB : public Tower
{

public:
	TowerBB(float ready);

	static bool InitializeMeshes();

	void SetPosition(glm::vec3 position) override;
	void SetUsed(bool used);
	void update(Game* game) override;
};

#endif
