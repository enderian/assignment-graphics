#include "Renderer.h"
#include "Game.h"
#include "Pirate.h"
#include "Road.h"
#include "Treasure.h"
#include "PlaneRG.h"
#include "Tower.h"
#include "CannonBall.h"
#include "Terrain.h"
#include <glm/gtc/matrix_transform.inl>
#include <SDL2/SDL.h>
#include "OBJLoader.h"
#include <iostream>

Game::Game()
{
	m_renderer = new Renderer();
}

Game::~Game()
{
	delete m_renderer;
}

bool Game::InitializeRenderer(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	return m_renderer->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool Game::InitializeObjects()
{
	//Initialize the meshes into memory.
	Pirate::InitializeMeshes();
	Road::InitializeMeshes();
	Treasure::InitializeMeshes();
	PlaneRG::InitializeMeshes();
	Tower::InitializeMeshes();
	CannonBall::InitializeMeshes();
	Terrain::InitializeMeshes();

	m_terrain = new Terrain();

	m_terrain->SetPosition(glm::vec3(18, -0.01, 18));

	//Create an empty pirate vector.
	this->m_pirates = std::vector<class Pirate*>();

	this->m_towers = std::vector<class Tower*>();

	this->m_projectiles = std::vector<class Projectile*>();

	for(int i = 0; i < 3; i++)
	{
		auto tower = new Tower(time());
		this->m_towers.push_back(tower);
	}

	for (auto pos : game_tiles)
	{
		auto road = new Road();
		road->SetPosition(pos);
		this->m_roads.push_back(road);
	}

	this->m_treasures = std::vector<class Treasure*>();

	for (auto tr_pos : treasure_locs)
	{
		auto treasure = new Treasure();
		treasure->SetPosition(tr_pos);
		this->m_treasures.push_back(treasure);
	}

	plane_rg = new PlaneRG();
	
	plane_rg->SetPosition(plane_rg->pos);

	test_tower = new Tower(time());

	test_tower->SetPosition(glm::vec3(4, 0, 4));
	test_tower->SetUsed(true);

	std::cout << test_tower->GetPos().x << std::endl;

	test_ball = new CannonBall();

	test_ball->SetPosition(glm::vec3(3.99596, 3.8, 3.96968));

	return true;
}

bool Game::InitializeLogic()
{
	return true;
}

void Game::Render()
{
	m_renderer->RenderGeometry(this);
	m_renderer->RenderShadowMaps(this);
	m_renderer->RenderToOuterRenderBuffer();
}

void Game::Update(float elapsed)
{
	m_time += elapsed;

	//Update all the pirates.
	for (auto pirate : m_pirates)
	{
		pirate->Update(this);
	}
	for (auto projectile : m_projectiles)
	{
		projectile->Update(this);
	}
	for (auto tower : m_towers)
	{
		tower->Update(this);
	}
	plane_rg->Update(this);
	test_ball->Update(this);
	test_tower->Update(this);
}

void Game::DrawGeometry(Renderer* renderer)
{
	m_terrain->DrawGeometry(renderer);
	for (auto pirate : m_pirates)
	{
		pirate->DrawGeometry(renderer);
	}
	for (auto road : m_roads)
	{
		road->DrawGeometry(renderer);
	}
	for (auto treasure : m_treasures)
	{
		treasure->DrawGeometry(renderer);
	}
	for (auto tower : m_towers)
	{
		if(tower->IsUsed()) tower->DrawGeometry(renderer);
	}
	for (auto projectile : m_projectiles)
	{
		projectile->DrawGeometry(renderer);
	}
	plane_rg->DrawGeometry(renderer);
	test_ball->DrawGeometry(renderer);
	test_tower->DrawGeometry(renderer);
}

void Game::DrawGeometryToShadowMap(Renderer* renderer)
{
	m_terrain->DrawGeometryToShadowMap(renderer);
	for (auto pirate : m_pirates)
	{
		pirate->DrawGeometryToShadowMap(renderer);
	}
	for (auto road : m_roads)
	{
		road->DrawGeometryToShadowMap(renderer);
	}
	for (auto treasure : m_treasures)
	{
		treasure->DrawGeometryToShadowMap(renderer);
	}
	for (auto tower : m_towers)
	{
		if (tower->IsUsed()) tower->DrawGeometryToShadowMap(renderer);
	}
	for (auto projectile : m_projectiles)
	{
		projectile->DrawGeometryToShadowMap(renderer);
	}
	plane_rg->DrawGeometryToShadowMap(renderer);
	test_ball->DrawGeometryToShadowMap(renderer);
	test_tower->DrawGeometryToShadowMap(renderer);
}

void Game::SpawnPirate(float dt)
{
	auto pirate = new Pirate(dt);
	this->m_pirates.push_back(pirate);
}

void Game::SpawnProjectile(glm::vec3 pos, glm::vec3 dir)
{
	auto projectile = new CannonBall(dir, time());
	projectile->SetPosition(glm::vec3(pos.x - 0.00404, 3.8, pos.z - 0.03032));
	this->m_projectiles.push_back(projectile);
}


void Game::DeployTower(glm::vec3 pos)
{
	for (Tower* t : m_towers)
	{
		if (!t->IsUsed())
		{
			t->SetPosition(pos);
			t->setUsed(true);
			break;
		}
	}
}

bool Game::RemoveTower(glm::vec3 pos)
{
	for (Tower* t: m_towers)
	{
		if(pos.x == t->GetPos().x && pos.z == t->GetPos().z && t->IsUsed())
		{
			t->setUsed(false);
			return true;
		}
	}
	return false;
}

void Game::AddTower()
{
	auto tower = new Tower(time());
	this->m_towers.push_back(tower);
}


std::vector<Tower*> Game::GetTowers()
{
	return this->m_towers;
}

std::vector<Pirate*> Game::GetPirates()
{
	return this->m_pirates;
}

