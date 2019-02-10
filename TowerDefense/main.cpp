#include "SDL2/SDL.h"
#include <iostream>
#include <chrono>
#include <Windows.h>
#include "GLEW\glew.h"
#include "Renderer.h"
#include "Game.h"
#include "PlaneRG.h"
#include "freeglut/freeglut.h"

using namespace std;

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

//Screen attributes
SDL_Window * window;

//OpenGL context 
SDL_GLContext gContext;
const int SCREEN_WIDTH = 1380;	//800;	//640;
const int SCREEN_HEIGHT = 1024;	//600;	//480;

//Event handler
SDL_Event event;

Game * game = nullptr;

bool over = false;

void func()
{
	system("pause");
}

// initialize SDL and OpenGL
bool init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	// use Double Buffering
	if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0)
		cout << "Error: No double buffering" << endl;

	// set OpenGL Version (3.3)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Create Window
	window = SDL_CreateWindow("Tower Defense", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (window == NULL)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return false;
	}

	//Create OpenGL context
	gContext = SDL_GL_CreateContext(window);
	if (gContext == NULL)
	{
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Disable Vsync
	if (SDL_GL_SetSwapInterval(0) == -1)
		printf("Warning: Unable to disable VSync! SDL Error: %s\n", SDL_GetError());

	// Initialize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error loading GLEW\n");
		return false;
	}
	// some versions of glew may cause an opengl error in initialization
	glGetError();

	game = new Game();
	bool engine_initialized = game->initialize_renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
	engine_initialized |= game->initialize_objects();

	mciSendString(TEXT("open \"*.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
	
	return engine_initialized;
}


void clean_up()
{
	delete game;

	SDL_GL_DeleteContext(gContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	//Initialize
	if (init() == false)
	{
		system("pause");
		return EXIT_FAILURE;
	}

	glutInit(&argc, argv);

	//Quit flag
	bool quit = false;
	bool mouse_button_pressed = false;
	glm::vec2 prev_mouse_position(0);

	auto simulation_start = chrono::steady_clock::now();

	float start_of_spawns = game->time();
	float start_of_towers = game->time();
	float start_of_additions = game->time();
	boolean allowed = false;
	double passed;
	// Wait for user exit
	while (quit == false)
	{
		// While there are events to handle
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				// Key down events
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
				else if (event.key.keysym.sym == SDLK_UP)
				{
					game->get_plane_rg()->moveUp();
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					game->get_plane_rg()->moveDown();
				}	
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					game->get_plane_rg()->moveLeft();
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					game->get_plane_rg()->moveRight();
				}
				else if (event.key.keysym.sym == SDLK_r)
				{
					if(allowed)
					{
						glm::vec4 place = game->get_plane_rg()->getPos();
						bool res = game->remove_tower(glm::vec3(place.x, place.y, place.z));
						if (res) allowed = false;
					}
				}
				else if (event.key.keysym.sym == SDLK_t)
				{
					glm::vec4 place = game->get_plane_rg()->getPos();
					if(place.w)
					{
						game->deploy_tower(glm::vec3(place.x, place.y, place.z));
						//if (!res) allowed = false;
					}
				}
				else if (event.key.keysym.sym == SDLK_y)
				{
					glm::vec4 place = game->get_plane_rg()->getPos();
					if (place.w)
					{
						game->deploy_tower_bb(glm::vec3(place.x, place.y, place.z));
						//if (!res) allowed = false;
					}
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
				{
					game->renderer()->camera_move_forward(false);
				}
				else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
				{
					game->renderer()->camera_move_back_ward(false);
				}
				else if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
				{
					game->renderer()->CameraMoveLeft(false);
				}
				else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				{
					game->renderer()->CameraMoveRight(false);
				}
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				int x = event.motion.x;
				int y = event.motion.y;
				if (mouse_button_pressed)
				{
					game->renderer()->CameraLook(glm::vec2(x, y) - prev_mouse_position);
					prev_mouse_position = glm::vec2(x, y);
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					int x = event.button.x;
					int y = event.button.y;
					mouse_button_pressed = (event.type == SDL_MOUSEBUTTONDOWN);
					prev_mouse_position = glm::vec2(x, y);
				}
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{
				int x = event.wheel.x;
				int y = event.wheel.y;
			}
			else if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					game->renderer()->resize_buffers(event.window.data1, event.window.data2);
				}
			}
		}
		// Compute the elapsed time
		auto simulation_end = chrono::steady_clock::now();
		float dt = chrono::duration <float>(simulation_end - simulation_start).count(); // in seconds
		simulation_start = chrono::steady_clock::now();

		if (!game->get_game_over()) {
			passed = (game->time() - start_of_spawns);
			if (passed >= 10 - (9 * (game->time() / 300.0f)) - rand() % 2)
			{
				game->spawn_pirate(game->time());
				start_of_spawns = game->time();
			}
			if ((game->time() - start_of_towers) >= 30)
			{
				allowed = true;
				start_of_towers = game->time();
			}

			if ((game->time() - start_of_additions) >= 120)
			{
				game->add_tower();
				start_of_additions = game->time();
			}
		}

		// Update
		game->update(dt);
		game->render();
		
		//Update screen (swap buffer for double buffering)
		SDL_GL_SwapWindow(window);
	}

	//Clean up
	clean_up();

	return 0;
}
