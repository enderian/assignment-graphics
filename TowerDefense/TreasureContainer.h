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

	void Update(Game* game) override;
	void DrawGeometry(Renderer* renderer) override;
	void DrawGeometryToShadowMap(Renderer* renderer) override;

	int GetCoins();
};

