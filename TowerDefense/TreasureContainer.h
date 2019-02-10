#pragma once
#include "Renderer.h"
#include "Game.h"

class TreasureContainer: public GameObject
{
private:

	int m_coins = 3;
	glm::vec3 pos;

	class Treasure* m_treasure_1;
	class Treasure* m_treasure_2;
	class Treasure* m_treasure_3;

public:
	TreasureContainer();
	~TreasureContainer();

	void update(Game* game) override;
	void draw_geometry(Renderer* renderer) override;
	void draw_geometry_to_shadow_map(Renderer* renderer) override;

	int GetCoins();
};

