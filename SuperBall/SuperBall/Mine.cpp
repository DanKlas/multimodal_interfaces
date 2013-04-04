#include "Mine.h"
#include <math.h>
#include <iostream>
#include <glut.h>	

#define PI2 6.283185307f
#define one_tenth_PI 0.31141592654f





Mine::Mine(float x, float y) : SpaceObject(x,y,0) 
{ 
	this->width = 30;
	this->height = 30;
	buildThePointsCountingForTheIntersection();
	randMovementVector = Vector2D(rand(), rand());
	randMovementVector *= normOfTheRandMovementVector/Magnitude(randMovementVector);
}

Mine::Mine(float x, float y, double scoreForThePlayer) : SpaceObject(x,y,scoreForThePlayer) 
{ 
	this->width = 30;
	this->height = 30;
	buildThePointsCountingForTheIntersection(); 
	randMovementVector = Vector2D(rand(), rand());
	randMovementVector *= normOfTheRandMovementVector/Magnitude(randMovementVector);
}


Mine::~Mine(void)
{
}


void Mine::drawIt()  //called from the main loop
{

		/*
		glBegin(GL_TRIANGLES); //idea: draw two triangles and add a shader as the image

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(x, y, 0);
		glVertex3f(x+width, y, 0);
		glVertex3f(x,y+height, 0);

		glVertex3f(x+width, y+height, 0);
		glVertex3f(x+width, y, 0);
		glVertex3f(x,y+height, 0);

		//texture
		GLuint bombTexture;
		glGenTextures(1, &bombTexture);
		glBindTexture(GL_TEXTURE_2D, bombTexture);
		
		// select modulate to mix texture with color for shading
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                 GL_LINEAR_MIPMAP_NEAREST );
		// when texture area is large, bilinear filter the original
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// the texture wraps over at the edges (repeat)
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );


		void * data;
		FILE * file;
		int imgwidth = 256, imgheight = 256; //to change with an actual image

		try{
			// allocate buffer
			data = malloc( width * height * 3 );
			// open and read texture data
			file = fopen( "bomb.jpg", "rb" );
			fread( data, width * height * 3, 1, file );
			fclose( file );
		}
		catch(int e){}
		

		glEnd();

		*/
	
	glBegin(GL_TRIANGLES);

		GLfloat color[3] = {0.0, 0.0, 0.0};
		glColor3fv(color);

		for(float a=0; a<PI2; a+=one_tenth_PI)
		{
			glVertex3f(x, y ,0);
			glVertex3f(x + cos(a)*radius, y-sin(a)*radius ,0);
			glVertex3f(x + cos(a+one_tenth_PI)*radius, y-sin(a+one_tenth_PI)*radius ,0);
		}
    glEnd();
	
}

void Mine::buildThePointsCountingForTheIntersection()
{
	//TODO: adapt to the image:
	for(float a=0; a<PI2; a+=one_tenth_PI)
		{
			pointsCountingForAnIntersection.push_back( Point2D(    (float)(x + cos(a)*radius), (float)(y-sin(a)*radius)   ));
		}
}


void Mine::updateTheRandMovementVector()
{

	int rand1 = rand()%100; if(rand1==0) rand1=1; //  in [1,..,99]
	int rand2 = rand()%100; if(rand2==0) rand2=1;//  in [1,..,99]
	float moins1ouPlus1_0_1;
	float moins1ouPlus1_0_2;
	if(rand()%2==1) moins1ouPlus1_0_1=0.1f; else moins1ouPlus1_0_1=-0.1f;
	if(rand()%2==1) moins1ouPlus1_0_2=0.1f; else moins1ouPlus1_0_2=-0.1f;

	this->randMovementVector += Vector2D( moins1ouPlus1_0_1 * (rand()%rand1), moins1ouPlus1_0_2 * (rand()%rand2) );
	this->randMovementVector *= normOfTheRandMovementVector/Magnitude(this->randMovementVector);
}

void Mine::setTheComponentYofTheRandomVectorNegative() {this->randMovementVector.y = (float) -1.0f*abs(this->randMovementVector.y); this->randMovementVector *= normOfTheRandMovementVector/Magnitude(this->randMovementVector);}
void Mine::setTheComponentYofTheRandomVectorPositive() {this->randMovementVector.y = (float) abs(this->randMovementVector.y); this->randMovementVector *= normOfTheRandMovementVector/Magnitude(this->randMovementVector);}
void Mine::setTheComponentXofTheRandomVectorNegative() {this->randMovementVector.x = (float) -1.0f*abs(this->randMovementVector.x); this->randMovementVector *= normOfTheRandMovementVector/Magnitude(this->randMovementVector);}
void Mine::setTheComponentXofTheRandomVectorPositive() {this->randMovementVector.x = (float) abs(this->randMovementVector.x); this->randMovementVector *= normOfTheRandMovementVector/Magnitude(this->randMovementVector);}