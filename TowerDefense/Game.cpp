#include "Renderer.h"
#include "Game.h"
#include "Pirate.h"
#include "Road.h"
#include "Treasure.h"
#include "TreasureContainer.h"
#include "PlaneRG.h"
#include "Tower.h"
#include "TowerMed.h"
#include "TowerBB.h"
#include "CannonBall.h"
#include "BulletBill.h"
#include "Terrain.h"
#include <glm/gtc/matrix_transform.inl>
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
	TowerMed::InitializeMeshes();
	TowerBB::InitializeMeshes();
	CannonBall::InitializeMeshes();
	BulletBill::InitializeMeshes();
	Terrain::InitializeMeshes();

	m_terrain = new Terrain();
	m_terrain->SetPosition(glm::vec3(18, -0.01, 18));

	m_pirates = std::vector<class Pirate*>();
	m_towers = std::vector<class Tower*>();
	m_projectiles = std::vector<class Projectile*>();

	for(int i = 0; i < 3; i++)
	{
		auto tower = new TowerMed(time());
		this->m_towers.push_back(tower);
	}

	this->m_towers.push_back(new TowerBB(time()));

	for (auto pos : game_tiles)
	{
		auto road = new Road();
		road->SetPosition(pos);
		this->m_roads.push_back(road);
	}

	m_treasure_container = new TreasureContainer();
	plane_rg = new PlaneRG();
	plane_rg->SetPosition(plane_rg->pos);

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
	//m_renderer->RenderHud();
	m_renderer->RenderToOuterRenderBuffer();
}

void Game::Update(float elapsed)
{
	m_time += elapsed;
	plane_rg->Update(this);
	m_treasure_container->Update(this);

	//Update all the pirates.
	for (auto pirate : m_pirates)
	{
		pirate->Update(this);
	}
	if(!finished)
	{
		for (auto projectile : m_projectiles)
		{
			projectile->Update(this);
		}
		for (auto tower : m_towers)
		{
			tower->Update(this);
		}
	}
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
	if(!finished)
	{
		for (auto tower : m_towers)
		{
			if (tower->IsUsed()) tower->DrawGeometry(renderer);
		}
		for (auto projectile : m_projectiles)
		{
			projectile->DrawGeometry(renderer);
		}
		plane_rg->DrawGeometry(renderer);
		m_treasure_container->DrawGeometry(renderer);
	}
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
	if(!finished)
	{
		for (auto tower : m_towers)
		{
			if (tower->IsUsed()) tower->DrawGeometryToShadowMap(renderer);
		}
		for (auto projectile : m_projectiles)
		{
			projectile->DrawGeometryToShadowMap(renderer);
		}
		plane_rg->DrawGeometryToShadowMap(renderer);
		m_treasure_container->DrawGeometryToShadowMap(renderer);
	}
}

void Game::SpawnPirate(float dt)
{
	auto pirate = new Pirate(dt);
	this->m_pirates.push_back(pirate);
}

void Game::SpawnProjectile(glm::vec3 pos, glm::vec3 dir, Tower* tower)
{
	if(dynamic_cast<TowerMed*>(tower))
	{
		auto origin = glm::vec3(pos.x - 0.00404, 3.8, pos.z - 0.03032);
		auto projectile = new CannonBall(origin, dir, time());
		projectile->SetPosition(origin);
		this->m_projectiles.push_back(projectile);
	}
	else if(dynamic_cast<TowerBB*>(tower))
	{
		auto projectile = new BulletBill(dir, time());
		projectile->SetPosition(glm::vec3(pos.x - 0.006565, 6.175, pos.z - 0.04927));
		this->m_projectiles.push_back(projectile);
	}
}


void Game::DeployTower(glm::vec3 pos)
{
	for (Tower* t : m_towers)
	{
		if (!t->IsUsed())
		{
			if(dynamic_cast<TowerMed*>(t))
			{
				t->SetPosition(pos);
				t->SetUsed(true);
				break;
			}
		}
	}
}

void Game::DeployTowerBB(glm::vec3 pos)
{
	for (Tower* t : m_towers)
	{
		if (!t->IsUsed())
		{
			if (dynamic_cast<TowerBB*>(t))
			{
				t->SetPosition(pos);
				t->SetUsed(true);
				break;
			}
		}
	}
}

bool Game::RemoveTower(glm::vec3 pos)
{
	for (Tower* t: m_towers)
	{
		if(pos.x == t->GetPos().x && pos.z == t->GetPos().z && t->IsUsed())
		{
			t->SetUsed(false);
			return true;
		}
	}
	return false;
}

void Game::AddTower()
{
	auto tower = new TowerMed(time());
	this->m_towers.push_back(tower);
}

void Game::GameOver()
{
	finished = true;

	for (auto it = m_projectiles.begin(); it != m_projectiles.end(); ++it)
	{
		delete *it;
	}
	m_projectiles.clear();

	for (auto it = m_pirates.begin(); it != m_pirates.end(); ++it)
	{
		delete *it;
	}
	m_pirates.clear();

	float time = 0;
	for (auto& tile: game_tiles)
	{
		time += 0.25f;
		auto pirate = new Pirate(time);
		pirate->SetPosition(tile);
		this->m_pirates.push_back(pirate);
	}
}

bool Game::GetGameOver()
{
	return this->finished;
}
