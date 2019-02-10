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
	TowerMed::InitializeMeshes();
	TowerBB::InitializeMeshes();
	CannonBall::InitializeMeshes();
	BulletBill::InitializeMeshes();
	Terrain::InitializeMeshes();

	m_terrain = new Terrain();

	m_terrain->SetPosition(glm::vec3(18, -0.01, 18));

	//Create an empty pirate vector.
	this->m_pirates = std::vector<class Pirate*>();

	this->m_towers = std::vector<class Tower*>();

	this->m_projectiles = std::vector<class Projectile*>();

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

	test_bill = new BulletBill();

	test_bill->SetPosition(glm::vec3(5, 2, 5));

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

	m_treasure_container->Update(this);
	plane_rg->Update(this);
	/*test_ball->Update(this);
	test_tower->Update(this);*/
	//test_bill->Update(this);
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
	for (auto tower : m_towers)
	{
		if(tower->IsUsed()) tower->DrawGeometry(renderer);
	}
	for (auto projectile : m_projectiles)
	{
		projectile->DrawGeometry(renderer);
	}
	plane_rg->DrawGeometry(renderer);
	m_treasure_container->DrawGeometry(renderer);
	/*test_ball->DrawGeometry(renderer);
	test_tower->DrawGeometry(renderer);*/
	test_bill->DrawGeometry(renderer);
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
	/*test_ball->DrawGeometryToShadowMap(renderer);
	test_tower->DrawGeometryToShadowMap(renderer);*/
	test_bill->DrawGeometryToShadowMap(renderer);
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