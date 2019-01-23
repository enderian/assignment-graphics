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

	for(int i = 0; i < 3; i++)
	{
		auto tower = new Tower();
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

	test_ball = new CannonBall();

	test_ball->SetPosition(glm::vec3(4, 1, 4));

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
	plane_rg->Update(this);
	test_ball->Update(this);
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
	plane_rg->DrawGeometry(renderer);
	//test_ball->DrawGeometry(renderer);
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
	plane_rg->DrawGeometryToShadowMap(renderer);
	//test_ball->DrawGeometryToShadowMap(renderer);
}

void Game::SpawnPirate(float dt)
{
	auto pirate = new Pirate(dt);
	this->m_pirates.push_back(pirate);
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
	auto tower = new Tower();
	this->m_towers.push_back(tower);
}


std::vector<Tower*> Game::GetTowers()
{
	return this->m_towers;
}
