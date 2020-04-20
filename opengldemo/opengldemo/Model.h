#pragma once
#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
class Model
{
public:
	Model(std::string path);
	~Model();

	void Draw(Shader shader);
	std::vector<Mesh> m_meshes;
private:
	
	std::string m_directory;
	std::vector<Texture> m_texture_loaded;
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

