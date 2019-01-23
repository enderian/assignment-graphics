#include "CannonBall.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"

GeometricMesh* m_cannonball_mesh;

bool CannonBall::InitializeMeshes()
{
	OBJLoader loader;
	m_cannonball_mesh = loader.load("../assets/Various/cannonball.obj");
	return true;
}

CannonBall::CannonBall() : Projectile()
{
	m_projectile->Init(m_cannonball_mesh);
}