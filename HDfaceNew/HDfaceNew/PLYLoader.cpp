#include "PLYLoader.h"

// Header File For Standard Input/Output
//#include <string.h>

CPLYLoader::CPLYLoader(void)
{
	vn = 0;
	fn = 0;
	tn = 0;
	vertex = NULL;
	faces = NULL;
	textcord = NULL;
}

void CPLYLoader::release()
{
	if(vn!=0)
	{
		if(vertex!=NULL)
		{
			delete [] vertex[0];
			delete [] vertex;
			vertex = NULL;
		}
		vn = 0;
	}
	if(fn!=0)
	{
		if(faces!=NULL)
		{
			delete [] faces[0];
			delete [] faces;
			faces = NULL;
		}
		if(textcord!=NULL)
		{
			delete [] textcord[0];
			delete [] textcord;
			textcord = NULL;
		}
		fn = 0;
	}
	tn = 0;
}

bool CPLYLoader::read(char filename[])
{
	float height , width;
	int i,ti1,ti2;
	char buf[128];
	char filename2[200];
	FILE *fid = fopen(filename,"r");
	release();
	//glGenTextures(200,textures);

	fgets(buf, sizeof(buf), fid);
	fgets(buf, sizeof(buf), fid);
	fgets(buf, sizeof(buf), fid);
	
	while(fscanf(fid, "%s", buf) != EOF) 
	{
		if(strcmp(buf,"end_header") == 0)
			break;
		switch(buf[0]) 
		{
			case 'c':    
				fgets(buf, sizeof(buf), fid);
				//sscanf(buf, "%s %s ", buf, filename2);
				//glGenTextures(1, &textures[tn]);
				//glBindTexture(GL_TEXTURE_2D, textures[tn] );
				//textures[tn] = glmLoadTexture(filename2, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE, &width, &height);
				//tn++;
				break;
			case 'e': 
				fscanf(fid, "%s", buf);
				if(buf[0] == 'v')
					fscanf(fid, "%d", &vn);
				else
					fscanf(fid, "%d", &fn);
				break;
			case 'p':
				fgets(buf, sizeof(buf), fid);
				break;
		}
	}

	vertex = new float* [vn];
	vertex[0] = new float [vn*3];
	faces = new int* [fn];
	faces[0] = new int[fn*3];
	//textcord = new float* [fn];
	//textcord[0] = new float[fn*7];
	for(i=1;i<vn;i++)
		vertex[i] = vertex[i-1]+3;
	for(i=1;i<fn;i++)
	{
		faces[i] = faces[i-1]+3;
		//textcord[i] = textcord[i-1]+7;
	}
	for(i=0;i<vn;i++){
		fscanf(fid,"%f %f %f",&vertex[i][0],&vertex[i][1],&vertex[i][2]);
		fgets(buf, sizeof(buf), fid);
	}
	if(tn == 1)
	{
		for(i=0;i<fn;i++)
		{
			textcord[i][6] = 0;
			fscanf(fid,"%d %d %d %d %d %f %f %f %f %f %f",&ti1,&faces[i][0],&faces[i][1],&faces[i][2],&ti2,&textcord[i][0],&textcord[i][1],&textcord[i][2],&textcord[i][3],&textcord[i][4],&textcord[i][5]);
		}			
	}else
		for(i=0;i<fn;i++)
			fscanf(fid,"%d %d %d %d",&ti1,&faces[i][0],&faces[i][1],&faces[i][2]);
	fclose(fid);
	return true;
}

void CPLYLoader::draw()
{
	if(vn>0)
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		for(int i=0;i<fn;i++)
		{			
			//if(textcord[i][6] >= 0)
			{				
				//glBindTexture(GL_TEXTURE_2D, textures[(int)textcord[i][6]]);

				//glColor4f(1.0, 1.0, 1.0, 1.0);

				glBegin(GL_TRIANGLES);
				//glTexCoord2f(textcord[i][0], textcord[i][1]); 
				glVertex3f(vertex[faces[i][0]][0], vertex[faces[i][0]][1],  vertex[faces[i][0]][2]);
				//glTexCoord2f(textcord[i][2], textcord[i][3]);
				glVertex3f(vertex[faces[i][1]][0], vertex[faces[i][1]][1],  vertex[faces[i][1]][2]);
				//glTexCoord2f(textcord[i][4], textcord[i][5]); 
				glVertex3f(vertex[faces[i][2]][0], vertex[faces[i][2]][1],  vertex[faces[i][2]][2]);
				glEnd();				
			}					
		}
		glDisable(GL_TEXTURE_2D);		
		
	}
}

CPLYLoader::~CPLYLoader(void)
{
	release();
}