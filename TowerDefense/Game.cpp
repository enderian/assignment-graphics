#include "Renderer.h"
#include "Game.h"
#include "Pirate.h"
#include "Road.h"
#include "Treasure.h"
#include "Tower.h"
#include "CannonBall.h"
#include "SelectionPlane.h"
#include "Terrain.h"
#include "OBJLoader.h"
#include <iostream>
#include "Hud.h"

Game::Game()
{
	m_renderer = new Renderer();
}

Game::~Game()
{
	delete m_hud;
	delete m_renderer;
}

bool Game::initialize_renderer(int screen_width, int screen_height)
{
	return m_renderer->Init(screen_width, screen_height);
}

bool Game::initialize_objects()
{
	//Initialize the meshes into memory.
	OBJLoader loader;
	Hud::initialize_meshes(loader);
	Pirate::initialize_meshes(loader);
	Road::initialize_meshes(loader);
	Treasure::initialize_meshes(loader);
	SelectionPlane::initialize_meshes(loader);
	CannonBall::initialize_meshes(loader);
	Terrain::initialize_meshes(loader);
	Tower::initialize_meshes(loader);

	m_terrain = new Terrain();
	m_terrain->set_position(glm::vec3(18, -0.01, 18));

	m_hud = new Hud();

	//Create an empty pirate vector.
	this->m_pirates = std::vector<class Pirate*>();
	this->m_towers = std::vector<class Tower*>();
	this->m_projectiles = std::vector<class Projectile*>();

	for(int i = 0; i < 3; i++)
	{
		auto tower = new Tower(0.0f);
		this->m_towers.push_back(tower);
	}

	for (auto pos : game_tiles)
	{
		auto road = new Road();
		road->set_position(pos);
		this->m_roads.push_back(road);
	}

	this->m_treasures = std::vector<class Treasure*>();

	for (auto tr_pos : treasure_locations)
	{
		auto treasure = new Treasure();
		treasure->set_position(tr_pos);
		this->m_treasures.push_back(treasure);
	}

	m_selection_plane = new SelectionPlane();
	m_selection_plane->set_position(m_selection_plane->position());

	return true;
}

bool Game::initialize_logic()
{
	return true;
}

void Game::render()
{
	m_renderer->RenderGeometry(this);
	m_renderer->RenderShadowMaps(this);
	m_renderer->RenderToOuterRenderBuffer();
}

void Game::update(float elapsed)
{
	m_time += elapsed;
	m_last_frame = elapsed;

	//Process new pirates and tower allowance.
	auto time_passed = (m_time - m_next_spawn);
	if (time_passed >= rand() % 3 + 9.5)
	{
		spawn_pirate(time());
		m_next_spawn = m_time;
	}
	if ((m_time - m_next_allow_tower) >= 30)
	{
		m_next_allow_tower = m_time;
	}
	if ((m_time - m_next_addition) >= 120)
	{
		m_next_addition = m_time;
	}

	//Update all the pirates.
	for (auto pirate : m_pirates)
	{
		pirate->update(this);
	}
	for (auto projectile : m_projectiles)
	{
		projectile->update(this);
	}
	for (auto tower : m_towers)
	{
		tower->update(this);
	}
	for (auto chest : m_treasures)
	{
		chest->update(this);
	}

	m_selection_plane->update(this);
}

void Game::draw_geometry(Renderer* renderer)
{
	m_terrain->draw_geometry(renderer);
	for (auto pirate : m_pirates)
	{
		pirate->draw_geometry(renderer);
	}
	for (auto road : m_roads)
	{
		road->draw_geometry(renderer);
	}
	for (auto treasure : m_treasures)
	{
		treasure->draw_geometry(renderer);
	}
	for (auto tower : m_towers)
	{
		if(tower->used()) tower->draw_geometry(renderer);
	}
	for (auto projectile : m_projectiles)
	{
		projectile->draw_geometry(renderer);
	}
	m_selection_plane->draw_geometry(renderer);
}

void Game::draw_geometry_to_shadow_map(Renderer* renderer)
{
	m_terrain->draw_geometry_to_shadow_map(renderer);
	for (auto pirate : m_pirates)
	{
		pirate->draw_geometry_to_shadow_map(renderer);
	}
	for (auto road : m_roads)
	{
		road->draw_geometry_to_shadow_map(renderer);
	}
	for (auto treasure : m_treasures)
	{
		treasure->draw_geometry_to_shadow_map(renderer);
	}
	for (auto tower : m_towers)
	{
		if (tower->used()) tower->draw_geometry_to_shadow_map(renderer);
	}
	for (auto projectile : m_projectiles)
	{
		projectile->draw_geometry_to_shadow_map(renderer);
	}
	m_selection_plane->draw_geometry_to_shadow_map(renderer);
}

void Game::spawn_pirate(float dt)
{
	auto pirate = new Pirate(dt);
	this->m_pirates.push_back(pirate);
}

void Game::spawn_projectile(glm::vec3 pos, glm::vec3 dir, Tower* tower)
{
	if(dynamic_cast<Tower*>(tower))
	{
		auto projectile = new CannonBall(pos, dir, time());
		this->m_projectiles.push_back(projectile);
	}
}


void Game::deploy_tower(glm::vec3 pos)
{
	for (Tower* t : m_towers)
	{
		if (!t->used())
		{
			if(dynamic_cast<Tower*>(t))
			{
				t->set_position(pos);
				t->set_used(true);
				break;
			}
		}
	}
}

bool Game::remove_tower(glm::vec3 pos)
{
	for (Tower* t: m_towers)
	{
		if(pos.x == t->position().x && pos.z == t->position().z && t->used())
		{
			t->set_used(false);
			return true;
		}
	}
	return false;
}

void Game::add_tower()
{
	auto tower = new Tower(time());
	this->m_towers.push_back(tower);
}

void Game::set_pirates(std::vector<Pirate*> m_pirates)
{
	this->m_pirates = m_pirates;
}

void Game::kill_pirate(Pirate* pirate)
{
	auto it = std::find(m_pirates.begin(), m_pirates.end(), pirate);
	if (it != m_pirates.end())
		m_pirates.erase(it);
}

void Game::kill_projectile(Projectile* projectile)
{
	auto it = std::find(m_projectiles.begin(), m_projectiles.end(), projectile);
	if (it != m_projectiles.end())
		m_projectiles.erase(it);
}