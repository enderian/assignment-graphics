#include "SelectionPlane.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OBJLoader.h"
#include "Tower.h"

GeometricMesh* m_plane_r_mesh;
GeometricMesh* m_plane_g_mesh;

bool SelectionPlane::initialize_meshes(OBJLoader& loader)
{
	m_plane_r_mesh = loader.load("../assets/Various/plane_red.obj");
	m_plane_g_mesh = loader.load("../assets/Various/plane_green.obj");
	return true;
}

SelectionPlane::SelectionPlane()
{
	m_plane_g = new GeometryNode();
	m_plane_r = new GeometryNode();
	curr_plane = m_plane_g;
	m_plane_r->Init(m_plane_r_mesh);
	m_plane_g->Init(m_plane_g_mesh);
}

SelectionPlane::~SelectionPlane()
{
	delete m_plane_r;
	delete m_plane_g;
}


void SelectionPlane::set_position(const glm::vec3& highp_vec3)
{
	m_position = highp_vec3;
}

glm::vec3 SelectionPlane::position() const
{
	return glm::vec4(m_position.x, m_position.y, m_position.z, (curr_plane == m_plane_g) ? 1 : 0);;
}

void SelectionPlane::update(Game* game)
{
	m_transformation_matrix = glm::translate(glm::mat4(1), position());
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(2, 2, 2));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));

	for (glm::vec3 i : game_tiles)
	{
		if(i.x == position().x && i.z == position().z)
		{
			curr_plane = m_plane_r;
			return;
		}
		else curr_plane = m_plane_g;
	}
	std::vector<Tower*> towers = game->towers();
	for (auto t : towers)
	{
		if(t->position().x == position().x && t->position().z == position().z && t->used())
		{
			curr_plane = m_plane_r;
			return;
		}
		else curr_plane = m_plane_g;
	}
}

void SelectionPlane::draw_geometry(Renderer* renderer)
{
	renderer->DrawGeometryNode(curr_plane, m_transformation_matrix, m_transformation_matrix_normal);
}

void SelectionPlane::draw_geometry_to_shadow_map(Renderer* renderer)
{
	renderer->DrawGeometryNodeToShadowMap(curr_plane, m_transformation_matrix, m_transformation_matrix_normal);
}

void SelectionPlane::move_up()
{
	(m_position.z < 9 * multiplier) ? m_position.z += 1 * multiplier : 0;
}

void SelectionPlane::move_down()
{
	(m_position.z > 0 * multiplier) ? m_position.z -= 1 * multiplier : 0;
}

void SelectionPlane::move_left()
{
	(m_position.x < 9 * multiplier) ? m_position.x += 1 * multiplier : 0;
}

void SelectionPlane::move_right()
{
	(m_position.x > 0 * multiplier) ? m_position.x -= 1 * multiplier : 0;
}


