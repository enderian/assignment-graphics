#include "PlaneRG.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"
#include "Tower.h"

GeometricMesh* m_plane_r_mesh;
GeometricMesh* m_plane_g_mesh;

bool PlaneRG::InitializeMeshes()
{
	OBJLoader loader;
	m_plane_r_mesh = loader.load("../assets/Various/plane_red.obj");
	m_plane_g_mesh = loader.load("../assets/Various/plane_green.obj");
	return true;
}

PlaneRG::PlaneRG()
{
	m_plane_g = new GeometryNode();
	m_plane_r = new GeometryNode();
	curr_plane = m_plane_g;
	m_plane_r->Init(m_plane_r_mesh);
	m_plane_g->Init(m_plane_g_mesh);
}

PlaneRG::~PlaneRG()
{
	delete m_plane_r;
	delete m_plane_g;
}

void PlaneRG::SetPosition(glm::vec3 position)
{
	m_transformation_matrix = glm::translate(glm::mat4(1), position * glm::vec3(4));
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(2, 2, 2));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void PlaneRG::update(Game* game)
{
	SetPosition(pos);
	for (glm::vec3 i : game_tiles)
	{
		if(i.x == pos.x && i.z == pos.z)
		{
			curr_plane = m_plane_r;
			return;
		}
		else curr_plane = m_plane_g;
	}
	std::vector<Tower*> towers = game->m_towers1();
	for (auto t : towers)
	{
		if(t->GetPos().x == pos.x && t->GetPos().z == pos.z && t->IsUsed())
		{
			curr_plane = m_plane_r;
			return;
		}
		else curr_plane = m_plane_g;
	}
}

void PlaneRG::draw_geometry(Renderer* renderer)
{
	renderer->draw_geometry_node(curr_plane, m_transformation_matrix, m_transformation_matrix_normal);
}

void PlaneRG::draw_geometry_to_shadow_map(Renderer* renderer)
{
	renderer->draw_geometry_node_to_shadow_map(curr_plane, m_transformation_matrix, m_transformation_matrix_normal);
}

void PlaneRG::moveUp()
{
	(pos.z < 9) ? pos.z += 1 : 0;
}

void PlaneRG::moveDown()
{
	(pos.z > 0) ? pos.z -= 1 : 0;
}

void PlaneRG::moveLeft()
{
	(pos.x < 9) ? pos.x += 1 : 0;
}

void PlaneRG::moveRight()
{
	(pos.x > 0) ? pos.x -= 1 : 0;
}

glm::vec4 PlaneRG::getPos()
{
	return glm::vec4(pos.x, pos.y, pos.z, (curr_plane == m_plane_g) ? 1 : 0);
}


