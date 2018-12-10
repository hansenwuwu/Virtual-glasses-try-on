#pragma once

#include <windows.h>
#include <stdio.h>
#include "gl\glut.h"
//#include "glmint.h"
#include "math.h"

/*extern "C" {
 #include <jpeg-9\jpeglib.h>
}*/

//#include "glaux.h"

class CPLYLoader
{
public:
	CPLYLoader(void);
	bool read(char filename[]);
	void release();
	void draw();
	void draw2();
	~CPLYLoader(void);
private:
	int vn;
	int fn;
	int tn;
	float **vertex;
	int **faces;
	float **textcord;
	GLuint	textures[200];	

};