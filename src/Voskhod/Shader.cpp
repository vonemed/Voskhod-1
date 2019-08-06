#include "Shader.h"
#include "VertexArray.h"

#include <GL/glew.h>

#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(std::string vert, std::string frag)
{
	std::ifstream file(vert.c_str());
	std::string vertSrc;

	if (!file.is_open())
	{
		throw std::exception; // If file didn't open
	}

	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		vertSrc += line + "\n";
	}
	
	file.close();

	file.open(frag.c_str());
	std::string fragSrc;

	if (!file.is_open())
	{
		throw std::exception();
	}

	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		fragSrc += line + "\n";
	}


}
