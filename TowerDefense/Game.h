#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SDL2/SDL.h>
#include "Collidable.h"

const int tiles_total = 29;
const int multiplier = 4;

const glm::vec3 game_tiles[] = {
	glm::vec3(0 * multiplier, 0, 0 * multiplier),
	glm::vec3(0 * multiplier, 0, 1 * multiplier),
	glm::vec3(0 * multiplier, 0, 2 * multiplier),
	glm::vec3(0 * multiplier, 0, 3 * multiplier),
	glm::vec3(1 * multiplier, 0, 3 * multiplier),
	glm::vec3(1 * multiplier, 0, 4 * multiplier),
	glm::vec3(1 * multiplier, 0, 5 * multiplier),
	glm::vec3(1 * multiplier, 0, 6 * multiplier),
	glm::vec3(1 * multiplier, 0, 7 * multiplier),
	glm::vec3(2 * multiplier, 0, 7 * multiplier),
	glm::vec3(2 * multiplier, 0, 8 * multiplier),
	glm::vec3(3 * multiplier, 0, 8 * multiplier),
	glm::vec3(4 * multiplier, 0, 8 * multiplier),
	glm::vec3(5 * multiplier, 0, 8 * multiplier),
	glm::vec3(6 * multiplier, 0, 8 * multiplier),
	glm::vec3(6 * multiplier, 0, 7 * multiplier),
	glm::vec3(6 * multiplier, 0, 6 * multiplier),
	glm::vec3(7 * multiplier, 0, 6 * multiplier),
	glm::vec3(7 * multiplier, 0, 5 * multiplier),
	glm::vec3(7 * multiplier, 0, 4 * multiplier),
	glm::vec3(7 * multiplier, 0, 3 * multiplier),
	glm::vec3(8 * multiplier, 0, 3 * multiplier),
	glm::vec3(9 * multiplier, 0, 3 * multiplier),
	glm::vec3(9 * multiplier, 0, 2 * multiplier),
	glm::vec3(9 * multiplier, 0, 1 * multiplier),
	glm::vec3(8 * multiplier, 0, 1 * multiplier),
	glm::vec3(7 * multiplier, 0, 1 * multiplier),
	glm::vec3(6 * multiplier, 0, 1 * multiplier),
	glm::vec3(6 * multiplier, 0, 0 * multiplier)
};

const glm::vec3 treasure_locations[] = {
	glm::vec3(5 * multiplier, 0, -.5 * multiplier),
	glm::vec3(6 * multiplier, 0, -.5 * multiplier),
	glm::vec3(7 * multiplier, 0, -.5 * multiplier)
};

class Game: public Renderable
{
private:
	SDL_Event event;

	float m_time = 0.0f;
	float m_last_frame = 0.0f;
	float m_next_spawn = 0.0f;
	float m_next_allow_tower = 0.0f;
	float m_next_addition = 0.0f;

	class Renderer* m_renderer;
	class SelectionPlane* m_selection_plane;
	class Terrain* m_terrain;
	class Hud* m_hud;

	std::vector<class Road*> m_roads;
	std::vector<class Treasure*> m_treasures;
	std::vector<class Pirate*> m_pirates;
	std::vector<class Tower*> m_towers;
	std::vector<class Projectile*> m_projectiles;

public:
	Game();
	~Game();

	float time() const
	{
		return m_time;
	}

	float last_frame() const
	{
		return m_last_frame;
	}

	Renderer* renderer() const
	{
		return m_renderer;
	}

	SelectionPlane* selection_plane() const
	{
		return m_selection_plane;
	}

	bool initialize_renderer(int screen_width, int screen_height);
	bool initialize_objects();
	auto initialize_logic() -> bool;

	void update(float elapsed);
	void render();

	void spawn_pirate(float dt);
	void kill_pirate(Pirate* pirate);

	void spawn_projectile(glm::vec3 origin, glm::vec3 direction, Tower* tower);
	void kill_projectile(Projectile* projectile);

	void deploy_tower(glm::vec3 pos);
	bool remove_tower(glm::vec3 pos);
	void add_tower();

	void set_pirates(std::vector<Pirate*> m_pirates);

	void draw_geometry(Renderer* renderer) override;
	void draw_geometry_to_shadow_map(Renderer* renderer) override;

	std::vector<Tower*> towers() const
	{
		return m_towers;
	}

	Terrain* terrain() const
	{
		return m_terrain;
	}

	std::vector<Pirate*> pirates() const
	{
		return m_pirates;
	};

	std::vector<Projectile*> projectiles() const
	{
		return m_projectiles;
	};

};

class GameObject : public Renderable
{
private:
	glm::vec3 m_position;
public:

	virtual glm::vec3 position() const
	{
		return m_position;
	}

	virtual void set_position(const glm::vec3& highp_vec3)
	{
		m_position = highp_vec3;
	}

	virtual void update(Game* game) = 0;
};
#endif // GAME_H
