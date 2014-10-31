#pragma once

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

	//static void loadTextures();

private:

	TerrainType type;

};

