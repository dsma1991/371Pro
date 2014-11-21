#include "Terrain.h"

Terrain::Terrain(void)
{
}


Terrain::~Terrain(void)
{
}

float terrainSegmentSize = 80.0f;

void Terrain::TerrainSurface(void){
	glPushMatrix();
		glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);

		float terrainSegmentSize= 80.0f;
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		   glTexCoord2f(0, 0); glVertex3f( -terrainSegmentSize, -terrainSegmentSize, -terrainSegmentSize );
		   glTexCoord2f(0, 1); glVertex3f( -terrainSegmentSize, -terrainSegmentSize,  terrainSegmentSize );
		   glTexCoord2f(1, 1); glVertex3f(  terrainSegmentSize, -terrainSegmentSize,  terrainSegmentSize );
		   glTexCoord2f(1, 0); glVertex3f(  terrainSegmentSize, -terrainSegmentSize, -terrainSegmentSize );
		glEnd();

	  // Restore enable bits and matrix
	glPopAttrib();
	glPopMatrix();
}

void Terrain::FullSurface(void){

}
void Terrain::DrawTerrain(void){
	float segmentSize = 80.0f;
	float doubleTranslate = segmentSize*2.0f;
	float fullTranslate = segmentSize*30.0f;
			//	TerrainSurface();
			for(int i = 0; i <=10; i++){
				TerrainSurface();
				glPushMatrix();
					for(int j=0; j<=15; j++){
						TerrainSurface();
						glTranslatef(0.0,0.0,doubleTranslate);
					}
				glPopMatrix();
				glTranslatef(doubleTranslate,0.0, 0.0);
			}

			glTranslatef(-doubleTranslate, 0.0f, -doubleTranslate);

			for(int i = 0; i <=10; i++){
				TerrainSurface();

				glPushMatrix();
				for(int j=0; j<=15; j++){
					TerrainSurface();
					glTranslatef(0.0,0.0,-doubleTranslate);
				}
				glPopMatrix();
				glTranslatef(-doubleTranslate,0.0, 0.0);
			}
			
			glTranslatef(0.0f, 0.0,-fullTranslate);

			for(int i = 0; i <=10; i++){
				TerrainSurface();
				glPushMatrix();
				for(int j=0; j<=15; j++){
					TerrainSurface();
					glTranslatef(0.0,0.0,doubleTranslate);
				}
				glPopMatrix();
				glTranslatef(-doubleTranslate,0.0, 0.0);
			}

			glTranslatef(doubleTranslate,0.0f, fullTranslate);
			for(int i = 0; i <=10; i++){
				TerrainSurface();
				glPushMatrix();
				for(int j=0; j<=15; j++){
					TerrainSurface();
					glTranslatef(0.0,0.0,doubleTranslate);
				}
				glPopMatrix();
				glTranslatef(doubleTranslate,0.0, 0.0);
			}
		/*
			glTranslatef(-doubleTranslate, 50.0, -doubleTranslate);

			for(int i = 0; i <=10; i++){
				TerrainSurface();
				glPushMatrix();
				for(int j=0; j<=15; j++){
					TerrainSurface();
					glTranslatef(0.0,0.0,doubleTranslate);
				}
				glPopMatrix();
				glTranslatef(-doubleTranslate,0.0, 0.0);
			}*/
}

