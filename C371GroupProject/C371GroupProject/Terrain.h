#pragma once
#include "includeHeader.h"

//static textures for all textures used
class Terrain
{
public:
	Terrain(void);
	~Terrain(void);

	enum TerrainType
	{
		Rock,
		Rubble,
		Grass,
	};

	void draw();
	void modify(TerrainType newType);

	void TerrainSurface(void);
	void DrawTerrain(void);
	//static void loadTextures();

private:

	TerrainType type;
	void FullSurface(void);
};

