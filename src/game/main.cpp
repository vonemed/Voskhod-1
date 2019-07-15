#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <exception>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(int argc, char *argv[])
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0) // If initialization of SDL failed throw an exception
  {
    throw std::exception();
  }

  SDL_Window *window = SDL_CreateWindow("Window",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  // OpenGL rendering context for created window
  if (!SDL_GL_CreateContext(window))
  {
	  throw std::exception();	
  }

  if (glewInit() != GLEW_OK)
  {
	  throw std::exception();
  }

  bool quit = false;

  while(!quit)
  {
    SDL_Event event = {0};

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window); // To eliminate flicker

    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
