#include "BulletBill.h"
#include <glm/gtc/matrix_transform.inl>
#include "OBJLoader.h"
#include "Tower.h"

GeometricMesh* m_bulletbill_mesh;

bool BulletBill::InitializeMeshes()
{
	OBJLoader loader;
	m_bulletbill_mesh = loader.load("../assets/Various/BulletBill.obj");
	return true;
}

BulletBill::BulletBill() : Projectile()
{
	m_projectile->Init(m_bulletbill_mesh);
}

BulletBill::BulletBill(glm::vec3 dir, float time)
{
	m_projectile->Init(m_bulletbill_mesh);
	this->direction = dir;
	this->time = time;
}

void BulletBill::SetPosition(glm::vec3 position)
{
	this->pos = position;
	m_transformation_matrix = glm::translate(glm::mat4(1), position*glm::vec3(4, 1, 4));
	m_transformation_matrix *= glm::scale(glm::mat4(1), glm::vec3(0.01));
	m_transformation_matrix_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_transformation_matrix))));
}

void BulletBill::Update(Game* game)
{
	const float alpha = (std::fmod((game->time() - this->time) / 1.0f, 1.0f) / 1.0f);
	pos = glm::mix(this->pos, this->direction, alpha);
	SetPosition(pos);
}
