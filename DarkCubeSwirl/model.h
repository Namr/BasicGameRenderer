#ifndef MODEL_H
#define MODEL_H
#include <GL/glew.h>
#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <sstream>

#include "camera.h"
#include "shader.h"
#include "mesh.h"
class Model
{
public:
	Model(GLchar* path)
	{
		this->loadModel(path);
	}
	void draw(Shader shader);
private:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		string typeName);
	GLint TextureFromFile(const char* path, string directory);
};

#endif