#include "Terrain.h"
#include "imageloader.h"

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
		glDisable(GL_BLEND);

		float terrainSegmentSize= 80.0f;
		glColor3f(1.0, 1.0, 1.0);
		for(int i= terrainSegmentSize; i >= -terrainSegmentSize; i-= 10){
			   glBegin(GL_QUAD_STRIP);
			   for(int j=terrainSegmentSize; j >= -terrainSegmentSize; j-=10){
					glNormal3f(0.0,1.0,0.0);
					glTexCoord2f(i/(2*terrainSegmentSize), j/(2*terrainSegmentSize));
					glVertex3f(i, -terrainSegmentSize, j);
					glNormal3f(0.0,1.0,0.0);
					glTexCoord2f((i+10)/(2*terrainSegmentSize), j/(2*terrainSegmentSize));
					glVertex3f(i+10,-terrainSegmentSize, j);
			   }

			   glEnd();
		   }
		glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	glPopMatrix();
}

void Terrain::DrawTerrain(void){
	float segmentSize = 80.0f;
	float doubleTranslate = segmentSize*2.0f;
	float fullTranslate = segmentSize*30.0f;
			for(int i = 0; i <=10; i++){
				TerrainSurface();
				glPushMatrix();
					for(int j=0; j<=10; j++){
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
				for(int j=0; j<=10; j++){
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
				for(int j=0; j<=10; j++){
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
				for(int j=0; j<=10; j++){
					TerrainSurface();
					glTranslatef(0.0,0.0,doubleTranslate);
				}
				glPopMatrix();
				glTranslatef(doubleTranslate,0.0, 0.0);
			}

}

