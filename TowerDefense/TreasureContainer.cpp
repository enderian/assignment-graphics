#include "TreasureContainer.h"
#include "Treasure.h"
#include "Pirate.h"
#include "Game.h"

TreasureContainer::TreasureContainer()
{
	pos = treasure_locs[1];

	m_treasure_1 = new Treasure();
	m_treasure_1->SetPosition(treasure_locs[0]);
	m_treasure_2 = new Treasure();
	m_treasure_2->SetPosition(treasure_locs[1]);
	m_treasure_3 = new Treasure();
	m_treasure_3->SetPosition(treasure_locs[2]);
}


void TreasureContainer::Update(Game* game)
{
	std::vector<Pirate*> m_pirates = game->GetPirates();
	glm::vec3 center(pos.x*(-.0176) + pos.x, pos.y*1.08174 + pos.y, pos.z*(-.80619) + pos.z);
	for (int i = 0; i < m_pirates.size(); i++)
	{
		auto pirate = m_pirates[i];
		int erase = 0;
		glm::vec3 p_pos = pirate->GetPos();
		glm::vec3 pirate_center(p_pos.x*(-.071464) + p_pos.x, p_pos.y*1.40196 + p_pos.y, p_pos.z*(-.51288) + p_pos.z);
		glm::vec3 dif(glm::abs(center - pirate_center));
		if (dif.x < .33 && dif.y < .33 && dif.z < .33)
		{
			m_coins--;
			erase = i;
			delete pirate;
			m_pirates.erase(m_pirates.begin() + erase);
			game->SetPirates(m_pirates);
		}
	}
}

TreasureContainer::~TreasureContainer()
{
}

void TreasureContainer::DrawGeometry(Renderer* renderer)
{
	if (m_coins > 2) m_treasure_1->DrawGeometry(renderer);
	if (m_coins > 0) m_treasure_2->DrawGeometry(renderer);
	if (m_coins > 1) m_treasure_3->DrawGeometry(renderer);
}

void TreasureContainer::DrawGeometryToShadowMap(Renderer* renderer)
{
	if (m_coins > 2) m_treasure_1->DrawGeometryToShadowMap(renderer);
	if (m_coins > 0) m_treasure_2->DrawGeometryToShadowMap(renderer);
	if (m_coins > 1) m_treasure_3->DrawGeometryToShadowMap(renderer);
}
