#include "Hud.h"

GeometricMesh* m_coin;

bool Hud::initialize_meshes(OBJLoader& loader)
{
	m_coin = loader.load("../assets/Hud/coin.obj");
	return true;
}

Hud::Hud()
{
	m_coin_1 = new GeometryNode();
	m_coin_1->Init(m_coin);
}

Hud::~Hud()
{
	
}

void Hud::draw_geometry(Renderer* renderer)
{
	renderer->DrawSimpleGeometryNode(m_coin_1);
}
