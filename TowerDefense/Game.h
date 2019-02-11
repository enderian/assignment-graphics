#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL2/SDL.h>

#define GAME_TILES_ALL 29

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

const glm::vec3 treasure_locations[] = {
	glm::vec3(5, 0, -.5),
	glm::vec3(6, 0, -.5),
	glm::vec3(7, 0, -.5)
};

class Game: public Renderable
{
private:
	SDL_Event m_event;

	float m_time = 0.0f;
	class Renderer* m_renderer;
	class PlaneRG* plane_rg;
	class Terrain* m_terrain;
	class TreasureContainer* m_treasure_container;

	std::vector<class Road*> m_roads;
	std::vector<class Pirate*> m_pirates;
	std::vector<class Tower*> m_towers;
	std::vector<class Projectile*> m_projectiles;

	bool m_finished = false;

public:
	Game();
	~Game();

	float time() const
	{
		return m_time;
	}

	Renderer* renderer() const
	{
		return m_renderer;
	}

	PlaneRG* get_plane_rg() const
	{
		return plane_rg;
	}

	bool initialize_renderer(int SCREEN_WIDTH, int SCREEN_HEIGHT);
	bool initialize_objects();
	bool initialize_logic();

	void update(float elapsed);
	void render();
	void spawn_pirate(float dt);
	void spawn_projectile(glm::vec3 pos, glm::vec3 dir, Tower* tower);
	void deploy_tower(glm::vec3 pos);
	void deploy_tower_bb(glm::vec3 pos);
	bool remove_tower(glm::vec3 pos);
	void add_tower();
	void game_over();
	bool get_game_over();

	void draw_geometry(Renderer* renderer) override;
	void draw_geometry_to_shadow_map(Renderer* renderer) override;

	std::vector<Pirate*> m_pirates1() const
	{
		return m_pirates;
	}

	void set_m_pirates(const std::vector<Pirate*>& pirates)
	{
		m_pirates = pirates;
	}

	std::vector<Tower*> m_towers1() const
	{
		return m_towers;
	}

	void set_m_towers(const std::vector<Tower*>& towers)
	{
		m_towers = towers;
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
	virtual void update(Game* game) = 0;
};
#endif // GAME_H
