#pragma once
#include "includeHeader.h"
#include <vector>
#include <string>
#include "Coordinates.h"
class ModelLoader
{
public:
	ModelLoader(void);
	~ModelLoader(void);

	void ModelLoader::drawModel();

	void ModelLoader::readInModel(std::string filename);

private:
//Titan
int random;
std::vector<Coordinates> vertices;
std::vector<Coordinates> normals;
std::vector<Coordinates> textures;
std::vector<std::vector<std::vector<int>>> faceVertex;
std::vector<std::vector<std::vector<int>>> faceNormal;
std::vector<std::vector<std::vector<int>>> faceTexture;
std::vector<std::string> texNames;

};

