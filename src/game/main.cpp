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

  // Primitive shape data
  // GLfoat - just a typedef of float
  const GLfloat positions[] = {
	  0.0f, 0.5f, 0.0f,
	  -0.5f, -0.5f, 0.0f,
	  0.5f, -0.5f, 0.0f
  };

  // GLuint - just a typedef of unsigned int
  GLuint positionsVboId = 0;

  // Creating a new VBO on the GPU and binding it

  // Creating
  glGenBuffers(1, &positionsVboId);

  if (!positionsVboId)
  {
	  throw std::exception();
  }

  // Binding
  glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

  // Uploading a copy of the data from memory into the new VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

  // Reset the state
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint vaoId = 0;

  // Creating a new VAO on the GPU and binding it
  glGenVertexArrays(1, &vaoId);

  if (!vaoId)
  {
	  throw std::exception();
  }

  glBindVertexArray(vaoId);

  // Bind the position VBO, assign it to position 0 on the bound VAO
  // and flag it to be used
  glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
	  3 * sizeof(GLfloat), (void *)0);

  glEnableVertexAttribArray(0);

  // Reset the state
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Simple Vertex Shader //
  const GLchar *vertexShaderSrc =
	  "attribute vec3 in_Position;			  " \
	  "										  " \
	  "void main()							  " \
	  "{									  " \
	  "	gl_Position = vec4(in_Position, 1.0); " \
	  "}									  ";

  // Create a new vertex shader, attach source code, compile it and
  // check for errors.
  GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
  glCompileShader(vertexShaderId);
  GLint success = 0;
  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

  if (!success)
  {
	  throw std::exception();
  }

  // Simple Fragment Shader //
  const GLchar *fragmentShaderSrc =
	  "void main()" \
	  "{" \
	  "	gl_FragColor = vec4(0,0,1,1);" \
	  "}";

  // Create a new fragment shader, attach source code, compile it and
  // check for errors.
  GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
  glCompileShader(fragmentShaderId);
  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

  if (!success)
  {
	  throw std::exception();
  }

  // Create new shaderprogram and attach our shader objects
  GLuint programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);

  // Ensure the VAO "position" attribute stream gets set as the first position
  // during the link
  glBindAttribLocation(programId, 0, "in_Position");

  // Perform the link and check for failure
  glLinkProgram(programId);
  glGetProgramiv(programId, GL_LINK_STATUS, &success);

  if (!success)
  {
	  throw std::exception();
  }

  // Detach and destroy the shader objects. These are no longer needed
  // because we now have a complete shader program.
  glDetachShader(programId, vertexShaderId);
  glDeleteShader(vertexShaderId);
  glDetachShader(programId, fragmentShaderId);
  glDeleteShader(fragmentShaderId);

  // Instruct OpenGL to use our shader program and our VAO
  glUseProgram(programId);
  glBindVertexArray(vaoId);
 
  bool quit = false;

  while(!quit)
  {
    SDL_Event event = {0};

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw 3 vertices (a triangle)
	glDrawArrays(GL_TRIANGLES, 0, 3);

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
  // Reset the state
  glBindVertexArray(0);
  glUseProgram(0);
  return 0;
}
