#include "Renderer.h"
#include "Game.h"
#include "Pirate.h"
#include "Road.h"
#include "Treasure.h"
#include "PlaneRG.h"
#include "Tower.h"
#include "OBJLoader.h"
#include <glm/gtc/matrix_transform.inl>
#include <SDL2/SDL.h>
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

	OBJLoader loader;
	m_terrain = new GeometryNode();
	m_terrain->Init(loader.load("../assets/Terrain/terrain.obj"));

	auto translate = glm::translate(glm::mat4(1), glm::vec3(18, -0.01, 18));
	auto scale = glm::scale(glm::mat4(1), glm::vec3(20, 20, 20));

	m_terrain_transformation_matrix = translate * scale;
	m_terrain_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_terrain_transformation_matrix))));

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
	/*for (auto tower : m_towers)
	{
		tower->Update(this);
	}*/
	plane_rg->Update(this);
}

void Game::DrawGeometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(m_terrain, m_terrain_transformation_matrix, m_terrain_transformation_matrix_normal);
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
}

void Game::DrawGeometryToShadowMap(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(m_terrain, m_terrain_transformation_matrix, m_terrain_transformation_matrix_normal);
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
			t->setPos(pos);
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
			t->setPos(glm::vec3(-1));
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
