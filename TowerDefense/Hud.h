#ifndef HUD
#define HUD

#include "Renderer.h"
#include "SDL2/SDL.h"
#include "OBJLoader.h"
#include "GeometryNode.h"

class Hud: public Renderable
{
private:
	GeometryNode* m_coin_1, m_coin_2, m_coin_3;
public:
	Hud();
	virtual ~Hud();

	static bool initialize_meshes(OBJLoader& loader);


	void draw_geometry(Renderer* renderer) override;
	void draw_geometry_to_shadow_map(Renderer* renderer) override {};
};
#endif