

class Scene
{
public:
	Scene();
	~Scene();

	void Update();
	void Draw();

protected:
	glm::mat4 _viewMatrix;
	glm::mat4 _projMatrix;;

	float _cameraAngleX, _cameraAngleY;
};