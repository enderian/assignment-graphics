#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "GLEW\glew.h"
#include "glm\glm.hpp"
#include "ShaderProgram.h"
#include "SpotlightNode.h"

class Renderable;

class Renderer
{
public:
	enum RENDERING_MODE
	{
		TRIANGLES,
		LINES,
		POINTS
	};

	float time() const
	{
		return m_continous_time;
	}

protected:
	int m_screen_width, m_screen_height;
	glm::mat4 m_view_matrix;
	glm::mat4 m_projection_matrix;
	glm::vec3 m_camera_position;
	glm::vec3 m_camera_target_position;
	glm::vec3 m_camera_up_vector;
	glm::vec2 m_camera_movement;
	glm::vec2 m_camera_look_angle_destination;

	// Geometry Rendering Intermediate Buffer
	GLuint m_fbo;
	GLuint m_fbo_depth_texture;
	GLuint m_fbo_texture;
	GLuint m_texture_green;
	GLuint m_texture_red;

	GLuint m_vao_fbo, m_vbo_fbo_vertices;

	float m_continous_time;

	// Rendering Mode
	RENDERING_MODE m_rendering_mode;

	// Lights
	SpotLightNode m_spotlight_node;

	// Meshes
	class GeometryNode* m_tower_object;
	glm::mat4 m_tower_object_transformation_matrix;
	glm::mat4 m_tower_object_transformation_normal_matrix;

	// Protected Functions
	bool InitRenderingTechniques();
	bool InitDeferredShaderBuffers();
	bool InitCommonItems();
	bool InitLightSources();
	bool InitGeometricMeshes();

	ShaderProgram m_geometry_rendering_program;
	ShaderProgram m_postprocess_program;
	ShaderProgram m_spot_light_shadow_map_program;
	ShaderProgram m_hud_program;

public:
	Renderer();
	~Renderer();
	bool Init(int SCREEN_WIDTH, int SCREEN_HEIGHT);
	bool ResizeBuffers(int SCREEN_WIDTH, int SCREEN_HEIGHT);
	bool ReloadShaders();

	// Passes
	void RenderShadowMaps(Renderable* geometries);
	void RenderGeometry(Renderable* geometries);
	void PostRender();
	//void RenderHud();
	void RenderToOuterRenderBuffer();

	void DrawGeometryNode(class GeometryNode* node, glm::mat4 model_matrix, glm::mat4 normal_matrix);
	void DrawGeometryNodeToShadowMap(class GeometryNode* node, glm::mat4 model_matrix, glm::mat4 normal_matrix);

	// Set functions
	void SetRenderingMode(RENDERING_MODE mode);

	// Camera Function
	void CameraMoveForward(bool enable);
	void CameraMoveBackWard(bool enable);
	void CameraMoveLeft(bool enable);
	void CameraMoveRight(bool enable);
	void CameraLook(glm::vec2 lookDir);
};
class Renderable
{
public:
	virtual void draw_geometry(class Renderer* renderer) = 0;
	virtual void draw_geometry_to_shadow_map(class Renderer* renderer) = 0;
};
#endif // RENDERER_H
