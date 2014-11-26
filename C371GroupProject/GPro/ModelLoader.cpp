#include "ModelLoader.h"


ModelLoader::ModelLoader(void)
{
	random = 2;
}


ModelLoader::~ModelLoader(void)
{
}


void ModelLoader::drawModel()
{
	// also need to have texture reading and whatever
	for(int k = 0; k < faceVertex.size(); ++k)
		for(int i = 0; i < faceVertex[k].size(); ++i)
		{
			glBegin(GL_POLYGON);
			for(int j = 0; j < faceVertex[k][i].size(); ++j)
			{
				Coordinates tempTex = textures[faceTexture[k][i][j]-1];
				Coordinates tempNorm = normals[faceNormal[k][i][j]-1];
				Coordinates tempVert= vertices[faceVertex[k][i][j]-1];
				glTexCoord2d(tempTex.x,tempTex.y);
				glNormal3d(tempNorm.x,tempNorm.y,tempNorm.z);
				glVertex3d(tempVert.x,tempVert.y,tempVert.z);
			}
			glEnd();
		}
}

void ModelLoader::readInModel(std::string filename)
{
	std::ifstream fin(filename.c_str());

	std::vector<std::vector<int>> faceTempV;
	std::vector<std::vector<int>> faceTempT;
	std::vector<std::vector<int>> faceTempN;


	char input;
	while(fin>>input)
	{
		if(input=='v')
		{
			input = fin.peek();
			if(input=='n')
			{
				fin>>input;
				Coordinates temp;
				fin>>temp.x;
				fin>>temp.y;
				fin>>temp.z;
				normals.push_back(temp);
			}
			else if(input=='t')
			{
				fin>>input;
				Coordinates temp;
				fin>>temp.x;
				fin>>temp.y;
				textures.push_back(temp);
			}
			else // if input==' '
			{
				Coordinates temp;
				fin>>temp.x;
				fin>>temp.y;
				fin>>temp.z;
				vertices.push_back(temp);
			}
		}
		else if(input=='f')
		{
			std::stringstream stream;
			int temp;
			int next;
			std::string faceLine;
			std::getline(fin,faceLine); //?
			stream << faceLine;
			
			std::vector<int> tempVectorV;
			std::vector<int> tempVectorN;
			std::vector<int> tempVectorT;
			while(stream >> next) // ?
			{
				tempVectorV.push_back(next);
				stream>>input; // to get rid of the /
				stream>>next;
				tempVectorT.push_back(next);
				stream>>input; // to get rid of the /
				stream>>next;
				tempVectorN.push_back(next);
			}
			faceTempV.push_back(tempVectorV);
			faceTempT.push_back(tempVectorT);
			faceTempN.push_back(tempVectorN);
		}
		else if(input == 'u')
		{
			fin>>input;//s
			fin>>input;//e
			fin>>input;//m
			fin>>input;//t
			fin>>input;//l
			std::string tempName;
			fin>>tempName;
			texNames.push_back(tempName);
			if(faceTempV.size() != 0)
			{
				faceVertex.push_back(faceTempV);
				faceNormal.push_back(faceTempN);
				faceTexture.push_back(faceTempT);
			}
			faceTempV.clear();
			faceTempT.clear();
			faceTempN.clear();
		}
		else
		{
			std::string garbage;
			std::getline(fin,garbage);
		}
	}
	faceVertex.push_back(faceTempV);
	faceNormal.push_back(faceTempN);
	faceTexture.push_back(faceTempT);
	fin.close();
}