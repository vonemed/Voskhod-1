#include <string>
#include <vector>

class VertexArray;
class Texture;

class ShaderProgram
{
	GLuint id;

public:
	ShaderProgram(std::string vert, std::string frag);

	void draw(VertexArray *vertexArray);
	void setUniform(std::string uniform, glm::vec4 value);
	void setUniform(std::string uniform, float value);
	void setUniform(std::string uniform, glm::mat4 value);
	void setUniform(std::string uniform, Texture *texture);

	GLuint getId();

};