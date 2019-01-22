#include "Renderer.h"
#include "Game.h"
#include "Pirate.h"
#include "Road.h"
#include "OBJLoader.h"
#include <glm/gtc/matrix_transform.inl>

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

	OBJLoader loader;
	m_terrain = new GeometryNode();
	m_terrain->Init(loader.load("../assets/Terrain/terrain.obj"));

	auto translate = glm::translate(glm::mat4(1), glm::vec3(18, -0.01, 18));
	auto scale = glm::scale(glm::mat4(1), glm::vec3(20, 20, 20));

	m_terrain_transformation_matrix = translate * scale;
	m_terrain_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_terrain_transformation_matrix))));

	//Create an empty pirate vector.
	this->m_pirates = std::vector<class Pirate*>();

	auto pirate = new Pirate();
	this->m_pirates.push_back(pirate);

	for (auto pos : game_tiles)
	{
		auto road = new Road();
		road->SetPosition(pos);
		this->m_roads.push_back(road);
	}

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
}
