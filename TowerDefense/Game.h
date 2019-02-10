#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL2/SDL.h>
#define TOTAL_GAME_TIMES = 29;

const glm::vec3 game_tiles[] = {
	glm::vec3(0, 0, 0),
	glm::vec3(0, 0, 1),
	glm::vec3(0, 0, 2),
	glm::vec3(0, 0, 3),
	glm::vec3(1, 0, 3),
	glm::vec3(1, 0, 4),
	glm::vec3(1, 0, 5),
	glm::vec3(1, 0, 6),
	glm::vec3(1, 0, 7),
	glm::vec3(2, 0, 7),
	glm::vec3(2, 0, 8),
	glm::vec3(3, 0, 8),
	glm::vec3(4, 0, 8),
	glm::vec3(5, 0, 8),
	glm::vec3(6, 0, 8),
	glm::vec3(6, 0, 7),
	glm::vec3(6, 0, 6),
	glm::vec3(7, 0, 6),
	glm::vec3(7, 0, 5),
	glm::vec3(7, 0, 4),
	glm::vec3(7, 0, 3),
	glm::vec3(8, 0, 3),
	glm::vec3(9, 0, 3),
	glm::vec3(9, 0, 2),
	glm::vec3(9, 0, 1),
	glm::vec3(8, 0, 1),
	glm::vec3(7, 0, 1),
	glm::vec3(6, 0, 1),
	glm::vec3(6, 0, 0)
};

const glm::vec3 treasure_locs[] = {
	glm::vec3(5, 0, -.5),
	glm::vec3(6, 0, -.5),
	glm::vec3(7, 0, -.5)
};

class Game: public Renderable
{
private:
	SDL_Event event;

	float m_time = 0.0f;
	class Renderer* m_renderer;
	class PlaneRG* plane_rg;
	class Terrain* m_terrain;
	class TreasureContainer* m_treasure_container;

	//Testing
	class CannonBall* test_ball;
	class Tower* test_tower;
	class BulletBill* test_bill;

	std::vector<class Road*> m_roads;
	std::vector<class Pirate*> m_pirates;
	std::vector<class Tower*> m_towers;
	std::vector<class Projectile*> m_projectiles;

public:
	Game();
	~Game();

	float time()
	{
		return m_time;
	}

	Renderer* renderer()
	{
		return m_renderer;
	}

	PlaneRG* getPlaneRG()
	{
		return plane_rg;
	}

	bool InitializeRenderer(int SCREEN_WIDTH, int SCREEN_HEIGHT);
	bool InitializeObjects();
	bool InitializeLogic();

	void Update(float elapsed);
	void Render();
	void SpawnPirate(float dt);
	void SpawnProjectile(glm::vec3 pos, glm::vec3 dir, Tower* tower);
	void DeployTower(glm::vec3 pos);
	void DeployTowerBB(glm::vec3 pos);
	bool RemoveTower(glm::vec3 pos);
	void AddTower();

	void DrawGeometry(Renderer* renderer) override;
	void DrawGeometryToShadowMap(Renderer* renderer) override;


	std::vector<Tower*> m_towers1() const
	{
		return m_towers;
	}

	std::vector<Pirate*> m_pirates1() const
	{
		return m_pirates;
	}

	void set_m_pirates(const std::vector<Pirate*>& pirates)
	{
		m_pirates = pirates;
	}

	std::vector<Projectile*> m_projectiles1() const
	{
		return m_projectiles;
	}

	void set_m_projectiles(const std::vector<Projectile*>& projectiles)
	{
		m_projectiles = projectiles;
	}
};

class GameObject : public Renderable
{
public:
	virtual void Update(Game* game) = 0;
};
#endif // GAME_H
