#pragma once
#include "includeHeader.h"

class Terrain
{
public:
	Terrain(void);
	~Terrain(void);

	//piece of terrain to draw
	void TerrainSurface(void);

	//draws many TerrainSurfaces over an area
	void DrawTerrain(void);
private:

};

