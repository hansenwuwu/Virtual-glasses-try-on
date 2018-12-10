//kinect head
#include <Kinect.h>
#include <Kinect.Face.h>

//opencv
#include <opencv2\opencv.hpp>

//PLY.h
#include "PLYLoader.h"

//system head
#include <iostream>		//define cerr
#define _USE_MATH_DEFINES	//before math.h to define M_PI
#include <math.h>
#include "scene.h"	//define vector
#include <time.h>	//random
//#include <ostream>
//#include <stdlib.h>
//#include <stdlib.h>

#include "gl\glut.h"
#include "gl\glui.h"

//#include <Windows.h>
//#include <wingdi.h>

//model
#define glassesmodel1 "glasses1_flame.ply"
#define glassesmodel2 "glasses3_flame.ply"
#define glassesmodel3 "glasses4_flame.ply"
#define glassesleg1 "glasses1_leg.ply"
#define glassesleg2 "temple2_2.ply"
#define facemodel "face.ply"
#define facemodel2 "head.ply"

using namespace std;

template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL){
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

struct quaternion{
	double x, y, z, w;
};

//opengl
void display(void);
void idle(void);
void changesize(GLsizei, GLsizei);
void keyboard(unsigned char, int, int);
void init(GLsizei, GLsizei);
//glui
void initglui(void);
void glui_callback(int);
//kinect process
void ColorFrame(void);
void BodyFrame(void);
void hdface(void);

enum{
	QUIT_BUTTON,
	RESETCOLOR_BUTTON,
	COLOR_LISTBOX,
	COLOR_LISTBOX2,
	GLASSES_LISTBOX,
	TEMPLE_LISTBOX,
	TEXTURE_LISTBOX,
	SCALE_UP_BUTTON,
	SCALE_DOWN_BUTTON,
	RESET_SCALE_BUTTON,
	X_ENABLED_ID,
	RANDOMCOLOR_BUTTON
};

//glui
GLUI *glui;
GLUI_Spinner *XSpinner;
GLUI_Listbox *color_listbox_2;
GLUI_Listbox *color_listbox;
int main_window;
int listbox_item_id = 12, glasses_listbox_item_id = 3, temple_listbox_item_id = 2;
int listbox_item_id_2 = 12;
float ColorR = 0.0, ColorG = 0.0, ColorB = 0.0, ColorA = 1.0;
float ColorRL = 0.0, ColorGL = 0.0, ColorBL = 0.0, ColorAL = 1.0;
float XChange = 0.f;
float randcolorR[13] = { 0 / 255.0, 0 / 255.0, 64 / 255.0, 128 / 255.0, 0 / 255.0, 192 / 255.0, 192 / 255.0, 255 / 255.0, 255 / 255.0, 255 / 255.0, 255 / 255.0, 255 / 255.0, 0 / 255.0 };
float randcolorG[13] = { 0 / 255.0, 255 / 255.0, 64 / 255.0, 128 / 255.0, 255 / 255.0, 192 / 255.0, 64 / 255.0, 192 / 255.0, 0 / 255.0, 0 / 255.0, 255 / 255.0, 255 / 255.0, 0 / 255.0 };
float randcolorB[13] = { 255 / 255.0, 255 / 255.0, 64 / 255.0, 128 / 255.0, 0 / 255.0, 192 / 255.0, 192 / 255.0, 64 / 255.0, 255 / 255.0, 0 / 255.0, 255 / 255.0, 0 / 255.0, 0 / 255.0 };
float randcolorRL[26] = { 0 / 255.0, 0 / 255.0, 64 / 255.0, 128 / 255.0, 0 / 255.0, 192 / 255.0, 192 / 255.0, 255 / 255.0, 255 / 255.0, 255 / 255.0, 255 / 255.0, 255 / 255.0, 0 / 255.0, 0 / 255.0, 0 / 255.0, 64 / 255.0, 128 / 255.0, 0 / 255.0, 192 / 255.0, 192 / 255.0, 255 / 255.0, 255 / 255.0, 255 / 255.0, 255 / 255.0, 255 / 255.0, 0 / 255.0 };
float randcolorGL[26] = { 0 / 255.0, 255 / 255.0, 64 / 255.0, 128 / 255.0, 255 / 255.0, 192 / 255.0, 64 / 255.0, 192 / 255.0, 0 / 255.0, 0 / 255.0, 255 / 255.0, 255 / 255.0, 0 / 255.0, 0 / 255.0, 255 / 255.0, 64 / 255.0, 128 / 255.0, 255 / 255.0, 192 / 255.0, 64 / 255.0, 192 / 255.0, 0 / 255.0, 0 / 255.0, 255 / 255.0, 255 / 255.0, 0 / 255.0 };
float randcolorBL[26] = { 255 / 255.0, 255 / 255.0, 64 / 255.0, 128 / 255.0, 0 / 255.0, 192 / 255.0, 192 / 255.0, 64 / 255.0, 255 / 255.0, 0 / 255.0, 255 / 255.0, 0 / 255.0, 0 / 255.0, 255 / 255.0, 255 / 255.0, 64 / 255.0, 128 / 255.0, 0 / 255.0, 192 / 255.0, 192 / 255.0, 64 / 255.0, 255 / 255.0, 0 / 255.0, 255 / 255.0, 0 / 255.0, 0 / 255.0 };

//init color
IKinectSensor* pSensor = nullptr;
IColorFrameSource* pColorSource = nullptr;
IColorFrameReader* pColorReader = nullptr;
IFrameDescription* pDescription = nullptr;
//init body
IBodyFrameSource* pBodySource = nullptr;
IBodyFrameReader* pBodyReader = nullptr;
//value
BOOLEAN bTrackingIdValid = false;
BOOLEAN bTracked = false;
UINT64 trackingId = _UI64_MAX;
//init face
IHighDefinitionFaceFrameSource* pHDFaceSource = nullptr;
IHighDefinitionFaceFrameReader* pHDFaceReader = nullptr;
IFaceModelBuilder* pFaceModelBuilder = nullptr;
IFaceAlignment* pFaceAlignment = nullptr;
IFaceModel* pFaceModel = nullptr;
BOOLEAN bFaceTracked = false;
FaceModelBuilderCollectionStatus collection;
IFaceModelData* pFaceModelData = nullptr;
//std::vector<CameraSpacePoint> facePoints(1347);
CameraSpacePoint facePoints[1347] = { 0 };

bool produce = { false };
UINT32 vertex = 0;


//cv 彩色畫面
int width, height;
unsigned int bufferSize = 0;
cv::Mat bufferMat;
cv::Mat NewbufferMat;

//normal
HRESULT hResult = S_OK;
CPLYLoader obj, obj2, face;
float disx = 0.0, disz = 0.0;
int randindex, randindex2;

//idle
float scalex = 0;
//rotate
float x1, x2;
float Y1, Y2;
float z1, z2;

//vector3f vecX, vecY, vecZ, vecN;
vector3f vecX, vecY, vecZ, vecN;
vector3f vecTmpT, vecTmpB;
vector3f ModelRadian;


//vector function
void mvCross(const vector3f &va, const vector3f &vb, vector3f &v){
	v = vector3f(va.y*vb.z - vb.y*va.z, -va.x*vb.z + vb.x*va.z, va.x*vb.y - vb.x*va.y);
}
float mvDot(const vector3f &v){
	return v.x*v.x + v.y*v.y + v.z*v.z;
}
float mvLength(const vector3f &v){
	return sqrtf(mvDot(v));
}
void mvNormalize(vector3f &v){
	v *= 1.f / mvLength(v);
}

//quaternion function
quaternion EulerToQua(double x, double y, double z)
{
	quaternion quat;

	quat.x = sin(y*(M_PI / 180) / 2.0)*sin(z*(M_PI / 180) / 2.0)*cos(x*(M_PI / 180) / 2.0) + cos(y*(M_PI / 180) / 2.0)*cos(z*(M_PI / 180) / 2.0)*sin(x*(M_PI / 180) / 2.0);
	quat.y = sin(y*(M_PI / 180) / 2.0)*cos(z*(M_PI / 180) / 2.0)*cos(x*(M_PI / 180) / 2.0) + cos(y*(M_PI / 180) / 2.0)*sin(z*(M_PI / 180) / 2.0)*sin(x*(M_PI / 180) / 2.0);
	quat.z = cos(y*(M_PI / 180) / 2.0)*sin(z*(M_PI / 180) / 2.0)*cos(x*(M_PI / 180) / 2.0) - sin(y*(M_PI / 180) / 2.0)*cos(z*(M_PI / 180) / 2.0)*sin(x*(M_PI / 180) / 2.0);
	quat.w = cos(y*(M_PI / 180) / 2.0)*cos(z*(M_PI / 180) / 2.0)*cos(x*(M_PI / 180) / 2.0) - sin(y*(M_PI / 180) / 2.0)*sin(z*(M_PI / 180) / 2.0)*sin(x*(M_PI / 180) / 2.0);

	return quat;
}

quaternion q, qf;
float scaleq, angleq;

float dis3 = 1;

int collectionid = 0;

int main(int argc, char** argv){
	//random color
	srand(time(NULL));

	//glass model
	obj.read(glassesmodel1);
	//temple model
	obj2.read(glassesleg1);
	//face model
	face.read(facemodel2);

	//Init Sensor
	hResult = GetDefaultKinectSensor(&pSensor);
	if (FAILED(hResult)){
		std::cerr << "Error : GetDefaultKinectSensor" << std::endl;
		return -1;
	}

	hResult = pSensor->Open();
	if (FAILED(hResult)){
		std::cerr << "Error : IKinectSensor::Open()" << std::endl;
		return -1;
	}

	//Color Source
	hResult = pSensor->get_ColorFrameSource(&pColorSource);
	if (FAILED(hResult)){
		std::cerr << "Error : IKinectSensor::get_ColorFrameSource()" << std::endl;
		return -1;
	}
	//Body Source
	hResult = pSensor->get_BodyFrameSource(&pBodySource);
	if (FAILED(hResult)){
		std::cerr << "Error : IKinectSensor::get_BodyFrameSource()" << std::endl;
		return -1;
	}

	//Color Reader
	hResult = pColorSource->OpenReader(&pColorReader);
	if (FAILED(hResult)){
		std::cerr << "Error : IColorFrameSource::OpenReader()" << std::endl;
		return -1;
	}
	//Body Reader
	hResult = pBodySource->OpenReader(&pBodyReader);
	if (FAILED(hResult)){
		std::cerr << "Error : IBodyFrameSource::OpenReader()" << std::endl;
		return -1;
	}

	// Description
	hResult = pColorSource->get_FrameDescription(&pDescription);
	if (FAILED(hResult)){
		std::cerr << "Error : IColorFrameSource::get_FrameDescription()" << std::endl;
		return -1;
	}

	width = 0;
	height = 0;
	pDescription->get_Width(&width); // 1920
	pDescription->get_Height(&height); // 1080

	bufferSize = width * height * 4 * sizeof(unsigned char);

	//openCV
	bufferMat = cv::Mat(cv::Size(width, height), CV_8UC4);	//color buffer
	NewbufferMat = cv::Mat(cv::Size(width, height), CV_8UC4);

	//HD face
	hResult = CreateHighDefinitionFaceFrameSource(pSensor, &pHDFaceSource);
	if (FAILED(hResult)){
		std::cerr << "Error : CreateHighDefinitionFaceFrameSource()" << std::endl;
		return -1;
	}

	hResult = pHDFaceSource->OpenReader(&pHDFaceReader);
	if (FAILED(hResult)){
		std::cerr << "Error : IHighDefinitionFaceFrameSource::OpenReader()" << std::endl;
		return -1;
	}

	hResult = pHDFaceSource->OpenModelBuilder(FaceModelBuilderAttributes::FaceModelBuilderAttributes_None, &pFaceModelBuilder);
	if (FAILED(hResult)){
		std::cerr << "Error : IHighDefinitionFaceFrameSource::OpenModelBuilder()" << std::endl;
		return -1;
	}

	hResult = pFaceModelBuilder->BeginFaceDataCollection();
	if (FAILED(hResult)){
		std::cerr << "Error : IFaceModelBuilder::BeginFaceDataCollection()" << std::endl;
		return -1;
	}

	hResult = CreateFaceAlignment(&pFaceAlignment);
	if (FAILED(hResult)){
		std::cerr << "Error : CreateFaceAlignment()" << std::endl;
		return -1;
	}

	//float deformations[FaceShapeDeformations::FaceShapeDeformations_Count];
	float* deformations = new float[FaceShapeDeformations_Count];

	hResult = CreateFaceModel(1.0f, FaceShapeDeformations_Count, &deformations[0], &pFaceModel);
	if (FAILED(hResult)){
		std::cerr << "Error : CreateFaceModel()" << std::endl;
		return -1;
	}

	hResult = GetFaceModelVertexCount(&vertex); // 1347
	if (FAILED(hResult)){
		std::cerr << "Error : GetFaceModelVertexCount()" << std::endl;
		return -1;
	}

	//gl
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	//glutCreateWindow("HDFace");
	main_window = glutCreateWindow("Glasses");
	//glutFullScreen();

	//init gl
	init(1280, 720);

	//main loop
	glutIdleFunc(idle);
	//glutReshapeFunc(changesize);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);

	initglui();

	glutMainLoop();

	//release
	//color
	SafeRelease(pColorSource);
	SafeRelease(pColorReader);
	SafeRelease(pDescription);
	//body
	SafeRelease(pBodySource);
	SafeRelease(pBodyReader);

	//face
	SafeRelease(pHDFaceSource);
	SafeRelease(pHDFaceReader);
	SafeRelease(pFaceModelBuilder);
	SafeRelease(pFaceAlignment);
	SafeRelease(pFaceModel);
	SafeRelease(pFaceModelData);

	if (pSensor){
		pSensor->Close();
	}
	SafeRelease(pSensor);

	return 0;
}

void display(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	glPixelZoom((float)1 - 0.3333333, (float)1 - 0.3333333);
	//glPixelZoom((float)1, (float)1);
	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glDrawPixels(1920, 1080, GL_BGRA_EXT, GL_UNSIGNED_BYTE, NewbufferMat.data);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MATRIX_MODE);
	glLoadIdentity();

	//open tranparent
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//facemodel
	glPushMatrix();
	glColor4f(0.0, 0.0, 0.0, 0.0);
	glTranslatef(facePoints[24].X + 0.045, facePoints[24].Y - 0.02, -facePoints[24].Z + 0.026);
	//glTranslatef(facePoints[24].X + 0.053, facePoints[24].Y , -facePoints[24].Z + 0.026);
	glRotatef(57.3*angleq, qf.x, qf.y, qf.z);

	face.draw();
	glPopMatrix();

	//glasses model
	glPushMatrix();
	glColor3f(ColorR, ColorG, ColorB);
	glTranslatef(facePoints[24].X + 0.045, facePoints[24].Y - 0.02, -facePoints[24].Z + 0.026);
	//glTranslatef(facePoints[24].X + 0.053, facePoints[24].Y , -facePoints[24].Z + 0.026);
	glRotatef(57.3*angleq, qf.x, qf.y, qf.z);
	glScalef(scalex, dis3, 1);

	obj.draw();
	glPopMatrix();

	//glasses leg
	glPushMatrix();
	glColor3f(ColorRL, ColorGL, ColorBL);
	glTranslatef(facePoints[24].X + 0.045, facePoints[24].Y - 0.02, -facePoints[24].Z + 0.026);
	//glTranslatef(facePoints[24].X + 0.053, facePoints[24].Y , -facePoints[24].Z + 0.026);
	glRotatef(57.3*angleq, qf.x, qf.y, qf.z);
	glScalef(scalex, 1, 1);

	obj2.draw();
	glPopMatrix();

	//cout << disx << ",  " << disz << endl;

	//sign
	switch (collectionid){
	case 0:
		break;
	case 1:
		glPushMatrix();
		glPointSize(60.0);
		glTranslatef(-0.2, 0.5, -2);
		glBegin(GL_POINTS);
		glColor3f(0.5, 0.5, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-0.2, 0.5, -2);
		glColor3f(0.5, 0.5, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.3, 0.0, 0.0);
		glVertex3f(-0.3, 0.0, 0.0);
		glVertex3f(0.0, 0.4, 0.0);
		glEnd();
		glPopMatrix();
		break;
	case 2:
		glPushMatrix();
		glPointSize(60.0);
		glTranslatef(0.5, 0.0, -2);
		glBegin(GL_POINTS);
		glColor3f(0.5, 0.5, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.5, 0.0, -2);
		glColor3f(0.5, 0.5, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0, 0.3, 0.0);
		glVertex3f(0.0, -0.3, 0.0);
		glVertex3f(0.4, 0.0, 0.0);
		glEnd();
		glPopMatrix();
		break;
	case 3:
		glPushMatrix();
		glPointSize(60.0);
		glTranslatef(-1.2, 0.0, -2);
		glBegin(GL_POINTS);
		glColor3f(0.5, 0.5, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-1.2, 0.0, -2);
		glColor3f(0.5, 0.5, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0, 0.3, 0.0);
		glVertex3f(0.0, -0.3, 0.0);
		glVertex3f(-0.4, 0.0, 0.0);
		glEnd();
		glPopMatrix();
		break;
	case 4:
		glPushMatrix();
		glTranslatef(-0.2, 0.0, -2);
		glColor3f(0.5, 0.5, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.1, 0.3, 0.0);
		glVertex3f(-0.1, 0.3, 0.0);
		glVertex3f(0.0, 0.08, 0.0);
		glVertex3f(0.1, -0.3, 0.0);
		glVertex3f(-0.1, -0.3, 0.0);
		glVertex3f(0.0, -0.08, 0.0);
		glVertex3f(-0.3, 0.1, 0.0);
		glVertex3f(-0.3, -0.1, 0.0);
		glVertex3f(-0.08, 0.0, 0.0);
		glVertex3f(0.3, 0.1, 0.0);
		glVertex3f(0.3, -0.1, 0.0);
		glVertex3f(0.08, 0.0, 0.0);
		glEnd();
		glPopMatrix();
		break;
	case 5:
		glPushMatrix();
		glPointSize(50.0);
		glTranslatef(-0.2, 0.0, -2);
		glBegin(GL_POINTS);
		glColor3f(0.5, 0.5, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.3, 0.0, 0.0);
		glVertex3f(-0.3, 0.0, 0.0);
		glEnd();
		glPopMatrix();
		break;
	};

	glutSwapBuffers();
}

void idle(){
	glutSetWindow(main_window);
	//color
	ColorFrame();

	//body
	BodyFrame();

	//hdface
	hdface();

	glutPostRedisplay();
}

void init(GLsizei w, GLsizei h){
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//parameter of camera
	glFrustum(-0.47056, 0.45884, -0.265019, 0.257899, 0.5, 8);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void changesize(GLsizei w, GLsizei h){
	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluPerspective(53.8, (GLfloat) 1920/(GLfloat) 1080, 0.5, 8);
	//1280*720
	//glFrustum(-0.47056, 0.45884, -0.265019, 0.257899, 0.5, 8);
	glFrustum(-0.47056, 2.25253985, -1.19191319, 0.257899, 0.5, 8);
	//gluPerspective( 53.8, w/h, 0.01, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'q':
		disx += 0.001;
		break;
	case 'e':
		disx -= 0.001;
		break;
	case 'a':
		disz += 0.001;
		break;
	case 'd':
		disz -= 0.001;
		break;
	};
}

void ColorFrame(){
	IColorFrame* pColorFrame = nullptr;
	hResult = pColorReader->AcquireLatestFrame(&pColorFrame);
	if (SUCCEEDED(hResult)){
		hResult = pColorFrame->CopyConvertedFrameDataToArray(bufferSize, reinterpret_cast<BYTE*>(bufferMat.data), ColorImageFormat::ColorImageFormat_Bgra);
		if (SUCCEEDED(hResult)){
			for (int i = 0; i < 1080; i++){
				for (int j = 0; j < 1920; j++){
					int idx = 4 * (j + i * 1920);
					int fidx = 4 * (j + (1079 - i) * 1920);
					NewbufferMat.data[idx] = bufferMat.data[fidx];
					NewbufferMat.data[idx + 1] = bufferMat.data[fidx + 1];
					NewbufferMat.data[idx + 2] = bufferMat.data[fidx + 2];
					NewbufferMat.data[idx + 3] = bufferMat.data[fidx + 3];
				}
			}
		}
	}
	SafeRelease(pColorFrame);
}

void BodyFrame(){
	IBodyFrame* pBodyFrame = nullptr;
	hResult = pBodyReader->AcquireLatestFrame(&pBodyFrame);
	if (SUCCEEDED(hResult)){
		IBody* pBody[BODY_COUNT] = { 0 };
		hResult = pBodyFrame->GetAndRefreshBodyData(BODY_COUNT, pBody);
		if (SUCCEEDED(hResult)){
			for (int count = 0; count < BODY_COUNT; count++){
				bTrackingIdValid = false;
				hResult = pHDFaceSource->get_IsTrackingIdValid(&bTrackingIdValid);
				if (!bTrackingIdValid){
					bTracked = false;
					hResult = pBody[count]->get_IsTracked(&bTracked);
					if (SUCCEEDED(hResult) && bTracked){
						trackingId = _UI64_MAX;
						hResult = pBody[count]->get_TrackingId(&trackingId);
						if (SUCCEEDED(hResult)){
							pHDFaceSource->put_TrackingId(trackingId);
						}
					}
				}
			}
		}
		for (int count = 0; count < BODY_COUNT; count++){
			SafeRelease(pBody[count]);
		}
	}
	SafeRelease(pBodyFrame);
}

void hdface(){
	//HDface
	HRESULT hResult = S_OK;
	IHighDefinitionFaceFrame* pHDFaceFrame = nullptr;
	hResult = pHDFaceReader->AcquireLatestFrame(&pHDFaceFrame);
	if (SUCCEEDED(hResult) && pHDFaceFrame){
		bFaceTracked = false;
		hResult = pHDFaceFrame->get_IsFaceTracked(&bFaceTracked);
		if (SUCCEEDED(hResult) && bFaceTracked){
			hResult = pHDFaceFrame->GetAndRefreshFaceAlignmentResult(pFaceAlignment);
			if (SUCCEEDED(hResult) && pFaceAlignment){
				// Face Model Building
				if (!produce){
					hResult = pFaceModelBuilder->get_CollectionStatus(&collection);

					if (SUCCEEDED(hResult) && collection == FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_Complete){
						std::cout << "Status : Complete" << std::endl;
						collectionid = 5;

						//SafeRelease(pFaceModelData);
						pFaceModelData = nullptr;
						if (SUCCEEDED(hResult)){
							hResult = pFaceModelBuilder->GetFaceData(&pFaceModelData);
						}

						SafeRelease(pFaceModel);
						if (SUCCEEDED(hResult) && pFaceModelData){
							hResult = pFaceModelData->ProduceFaceModel(&pFaceModel);
							collectionid = 0;
						}

						if (SUCCEEDED(hResult) && pFaceModel){
							produce = true;
						}

						SafeRelease(pFaceModelData);

					}
					else{

						if (SUCCEEDED(hResult) && collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_TiltedUpViewsNeeded){
							std::cout << "Need : Tilted Up Views" << std::endl;
							collectionid = 1;
						}
						else if (SUCCEEDED(hResult) && collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_RightViewsNeeded){
							std::cout << "Need : Right Views" << std::endl;
							collectionid = 2;
						}
						else if (SUCCEEDED(hResult) && collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_LeftViewsNeeded){
							std::cout << "Need : Left Views" << std::endl;
							collectionid = 3;
						}
						else if (SUCCEEDED(hResult) && collection >= FaceModelBuilderCollectionStatus::FaceModelBuilderCollectionStatus_FrontViewFramesNeeded){
							std::cout << "Need : Front ViewFrames" << std::endl;
							collectionid = 4;
						}

					}

				}
				else if (SUCCEEDED(hResult) && produce){
					hResult = pFaceModel->CalculateVerticesForAlignment(pFaceAlignment, vertex, &facePoints[0]);
					if (SUCCEEDED(hResult)){

						//scale
						//	1.478
						//眼睛長度
						//scalex = sqrt( (facePoints[210].X - facePoints[469].X)*(facePoints[210].X - facePoints[469].X) + (facePoints[210].Y - facePoints[469].Y)*(facePoints[210].Y - facePoints[469].Y) + (facePoints[210].Z - facePoints[469].Z)*(facePoints[210].Z - facePoints[469].Z) );
						scalex = sqrt((facePoints[474].X - facePoints[1068].X)*(facePoints[474].X - facePoints[1068].X) + (facePoints[474].Y - facePoints[1068].Y)*(facePoints[474].Y - facePoints[1068].Y) + (facePoints[474].Z - facePoints[1068].Z)*(facePoints[474].Z - facePoints[1068].Z));
						scalex = scalex / 0.13;

						// Rotate

						vecX.x = 0;
						vecX.y = 0;
						vecX.z = 0;
						vecY.x = 0;
						vecY.y = 0;
						vecY.z = 0;
						vecZ.x = 0;
						vecZ.y = 0;
						vecZ.z = 0;

						//rotate
						//x axis
						x1 = facePoints[1117].X;
						Y1 = facePoints[1117].Y;
						z1 = facePoints[1117].Z;

						x2 = facePoints[469].X;
						Y2 = facePoints[469].Y;
						z2 = facePoints[469].Z;

						//x vec
						vecX.x = x1 - x2;
						vecX.y = Y1 - Y2;
						vecX.z = z1 - z2;

						mvNormalize(vecX);


						vecTmpT.x = (facePoints[210].X + facePoints[843].X) / 2;
						vecTmpT.y = (facePoints[210].Y + facePoints[843].Y) / 2;
						vecTmpT.z = (facePoints[210].Z + facePoints[843].Z) / 2;
						vecTmpB.x = facePoints[4].X;
						vecTmpB.y = facePoints[4].Y;
						vecTmpB.z = facePoints[4].Z;
						vecY.x = vecTmpB.x - vecTmpT.x;
						vecY.y = vecTmpB.y - vecTmpT.y;
						vecY.z = vecTmpB.z - vecTmpT.z;

						mvNormalize(vecY);

						//get Z
						mvCross(vecX, vecY, vecZ);
						mvNormalize(vecZ);

						//remake Y
						mvCross(vecZ, vecX, vecY);
						mvNormalize(vecY);


						//vecX'
						vecN.x = -vecZ.z;
						vecN.y = 0;
						vecN.z = vecZ.x;

						float tmpR;

						tmpR = acos((vecX.x*vecN.x + vecX.y*vecN.y + vecX.z*vecN.z) / (powf((vecX.x*vecX.x + vecX.y*vecX.y + vecX.z*vecX.z), 0.5)*powf((vecN.x*vecN.x + vecN.y*vecN.y + vecN.z*vecN.z), 0.5)));
						if (vecX.y < 0){
							ModelRadian.z = -tmpR;
						}
						else
							ModelRadian.z = tmpR;

						tmpR = std::asinf(-vecZ.y / powf((vecZ.x*vecZ.x + vecZ.y*vecZ.y + vecZ.z*vecZ.z), 0.5));
						if (57.3*std::fabs(ModelRadian.x - tmpR) > 1)
							ModelRadian.x = tmpR;

						tmpR = std::asinf(vecZ.x / powf((vecZ.z*vecZ.z + vecZ.x*vecZ.x), 0.5));
						if (57.3*std::fabs(ModelRadian.y - tmpR) > 1)
							ModelRadian.y = tmpR;

						q = EulerToQua(57.3*ModelRadian.x, 57.3*ModelRadian.y, 57.3*ModelRadian.z);

						scaleq = sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
						qf.x = q.x / scaleq;
						qf.y = q.y / scaleq;
						qf.z = q.z / scaleq;
						angleq = acos(q.w) * 2.0f;

					}
				}
			}
		}
	}
	SafeRelease(pHDFaceFrame);
}

void initglui(){
	GLUI_Master.set_glutIdleFunc(idle);

	glui = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_RIGHT);

	GLUI_Panel *GlassesPanel = glui->add_panel("Basic ", true);

	GLUI_Panel *TypePanel = glui->add_panel_to_panel(GlassesPanel, "Glasses", true);
	GLUI_Listbox *glasses_listbox = glui->add_listbox_to_panel(TypePanel, "Type : ", &glasses_listbox_item_id, GLASSES_LISTBOX, glui_callback);

	glasses_listbox->add_item(1, "Normal Glass");
	glasses_listbox->add_item(2, "Circle Glass");
	glasses_listbox->add_item(3, "Goggle Glass");

	color_listbox = glui->add_listbox_to_panel(TypePanel, "Color : ", &listbox_item_id, COLOR_LISTBOX, glui_callback);

	color_listbox->add_item(1, "                   ");
	color_listbox->add_item(2, "Blue");
	color_listbox->add_item(3, "Cyan");
	color_listbox->add_item(4, "Dark Grey");
	color_listbox->add_item(5, "Grey");
	color_listbox->add_item(6, "Green");
	color_listbox->add_item(7, "Light Grey");
	color_listbox->add_item(8, "Magenta");
	color_listbox->add_item(9, "Orange");
	color_listbox->add_item(10, "Pink");
	color_listbox->add_item(11, "Red");
	color_listbox->add_item(12, "White");
	color_listbox->add_item(13, "Yellow");
	color_listbox->add_item(14, "Black");

	GLUI_Panel *TemplePanel = glui->add_panel_to_panel(GlassesPanel, "Glasses Temple", true);
	//GLUI_Listbox *temple_listbox = glui->add_listbox_to_panel(TemplePanel, "Temple : ", &temple_listbox_item_id, TEMPLE_LISTBOX, glui_callback);

	//temple_listbox->add_item(1, "Temple1");
	//temple_listbox->add_item(2, "Temple2");

	color_listbox_2 = glui->add_listbox_to_panel(TemplePanel, "Color : ", &listbox_item_id_2, COLOR_LISTBOX2, glui_callback);

	color_listbox_2->add_item(1, "                   ");
	color_listbox_2->add_item(2, "Blue");
	color_listbox_2->add_item(3, "Cyan");
	color_listbox_2->add_item(4, "Dark Grey");
	color_listbox_2->add_item(5, "Grey");
	color_listbox_2->add_item(6, "Green");
	color_listbox_2->add_item(7, "Light Grey");
	color_listbox_2->add_item(8, "Magenta");
	color_listbox_2->add_item(9, "Orange");
	color_listbox_2->add_item(10, "Pink");
	color_listbox_2->add_item(11, "Red");
	color_listbox_2->add_item(12, "White");
	color_listbox_2->add_item(13, "Yellow");
	color_listbox_2->add_item(14, "Black");

	glui->add_button_to_panel(GlassesPanel, "Random Color", RANDOMCOLOR_BUTTON, glui_callback);
	glui->add_button_to_panel(GlassesPanel, "Reset Color", RESETCOLOR_BUTTON, glui_callback);

	GLUI_Panel *ScalePanel = glui->add_panel("Glasses Scale", true);
	XSpinner = glui->add_spinner_to_panel(ScalePanel, "Scale", GLUI_SPINNER_FLOAT, &XChange, X_ENABLED_ID, glui_callback);
	XSpinner->set_speed(0.1);
	XSpinner->set_float_limits(-0.5, 0.5);

	glui->add_button_to_panel(ScalePanel, "Reset Scale", RESET_SCALE_BUTTON, glui_callback);

	//glui->add_button("Restart", RESTART_BUTTON, glui_callback);

	glui->add_button("Quit", QUIT_BUTTON, glui_callback);

	glui->set_main_gfx_window(main_window);
}

void glui_callback(int control_id){
	switch (control_id){
	case RANDOMCOLOR_BUTTON:
		randindex = rand() % 13 + 1;
		ColorR = randcolorR[randindex];
		ColorG = randcolorG[randindex];
		ColorB = randcolorB[randindex];
		randindex2 = rand() % 13 + 9;
		ColorRL = randcolorRL[randindex2];
		ColorGL = randcolorGL[randindex2];
		ColorBL = randcolorBL[randindex2];

		color_listbox_2->set_int_val(1);
		color_listbox->set_int_val(1);
		break;
	case X_ENABLED_ID:
		dis3 = 1 + XChange * 10;
		break;
	case QUIT_BUTTON:
		exit(1);
		break;
	case RESETCOLOR_BUTTON:
		ColorR = 0.0;
		ColorG = 0.0;
		ColorB = 0.0;
		ColorA = 1.0;
		ColorRL = 0.0;
		ColorGL = 0.0;
		ColorBL = 0.0;
		ColorAL = 1.0;
		color_listbox_2->set_int_val(1);
		color_listbox->set_int_val(1);
		break;
	case RESET_SCALE_BUTTON:
		dis3 = 1;
		XSpinner->set_float_val(0.0);
		break;
	case TEMPLE_LISTBOX:
		switch (temple_listbox_item_id){
		case 1:
			obj2.release();
			obj2.read(glassesleg1);
			break;
		case 2:
			obj2.release();
			obj2.read(glassesleg2);
			break;
		};
		break;
	case GLASSES_LISTBOX:
		switch (glasses_listbox_item_id){
		case 1:
			obj.release();
			obj.read(glassesmodel1);
			obj2.release();
			obj2.read(glassesleg1);

			dis3 = 1;
			XSpinner->set_float_val(0.0);

			ColorR = 0.0;
			ColorG = 0.0;
			ColorB = 0.0;
			ColorA = 1.0;
			ColorRL = 0.0;
			ColorGL = 0.0;
			ColorBL = 0.0;
			ColorAL = 1.0;
			color_listbox_2->set_int_val(1);
			color_listbox->set_int_val(1);
			break;
		case 2:
			obj.release();
			obj.read(glassesmodel2);
			obj2.release();
			obj2.read(glassesleg2);

			dis3 = 1;
			XSpinner->set_float_val(0.0);

			ColorR = 0.0;
			ColorG = 0.0;
			ColorB = 0.0;
			ColorA = 1.0;
			ColorRL = 0.0;
			ColorGL = 0.0;
			ColorBL = 0.0;
			ColorAL = 1.0;
			color_listbox_2->set_int_val(1);
			color_listbox->set_int_val(1);
			break;
		case 3:
			obj.release();
			obj.read(glassesmodel3);
			obj2.release();

			dis3 = 1;
			XSpinner->set_float_val(0.0);

			ColorR = 0.0;
			ColorG = 0.0;
			ColorB = 0.0;
			ColorA = 1.0;
			ColorRL = 0.0;
			ColorGL = 0.0;
			ColorBL = 0.0;
			ColorAL = 1.0;
			color_listbox_2->set_int_val(1);
			color_listbox->set_int_val(1);
			break;
		};
		break;
	case COLOR_LISTBOX:
		switch (listbox_item_id){
			//  Select black color
		case 1:
			//ColorR = 0 / 255.0;
			//ColorG = 0 / 255.0;
			//ColorB = 0 / 255.0;
			break;
			//  Select blue color
		case 2:
			ColorR = 0 / 255.0;
			ColorG = 0 / 255.0;
			ColorB = 255 / 255.0;
			break;
			//  Select cyan color
		case 3:
			ColorR = 0 / 255.0;
			ColorG = 255 / 255.0;
			ColorB = 255 / 255.0;
			break;
			//  Select dark grey color
		case 4:
			ColorR = 64 / 255.0;
			ColorG = 64 / 255.0;
			ColorB = 64 / 255.0;
			break;
			//  Select grey color
		case 5:
			ColorR = 128 / 255.0;
			ColorG = 128 / 255.0;
			ColorB = 128 / 255.0;
			break;
			//  Select green color
		case 6:
			ColorR = 0 / 255.0;
			ColorG = 255 / 255.0;
			ColorB = 0 / 255.0;
			break;
			//  Select light gray color
		case 7:
			ColorR = 192 / 255.0;
			ColorG = 192 / 255.0;
			ColorB = 192 / 255.0;
			break;
			//  Select magenta color
		case 8:
			ColorR = 192 / 255.0;
			ColorG = 64 / 255.0;
			ColorB = 192 / 255.0;
			break;
			//  Select orange color
		case 9:
			ColorR = 255 / 255.0;
			ColorG = 192 / 255.0;
			ColorB = 64 / 255.0;
			break;
			//  Select pink color
		case 10:
			ColorR = 255 / 255.0;
			ColorG = 0 / 255.0;
			ColorB = 255 / 255.0;
			break;
			//  Select red color
		case 11:
			ColorR = 255 / 255.0;
			ColorG = 0 / 255.0;
			ColorB = 0 / 255.0;
			break;
			//  Select white color
		case 12:
			ColorR = 255 / 255.0;
			ColorG = 255 / 255.0;
			ColorB = 255 / 255.0;
			break;
			//  Select yellow color
		case 13:
			ColorR = 255 / 255.0;
			ColorG = 255 / 255.0;
			ColorB = 0 / 255.0;
			break;
		case 14:
			ColorR = 0 / 255.0;
			ColorG = 0 / 255.0;
			ColorB = 0 / 255.0;
			break;
		}
		break;
	case COLOR_LISTBOX2:
		switch (listbox_item_id_2){
			//  Select black color
		case 1:
			//ColorR = 0 / 255.0;
			//ColorG = 0 / 255.0;
			//ColorB = 0 / 255.0;
			break;
			//  Select blue color
		case 2:
			ColorRL = 0 / 255.0;
			ColorGL = 0 / 255.0;
			ColorBL = 255 / 255.0;
			break;
			//  Select cyan color
		case 3:
			ColorRL = 0 / 255.0;
			ColorGL = 255 / 255.0;
			ColorBL = 255 / 255.0;
			break;
			//  Select dark grey color
		case 4:
			ColorRL = 64 / 255.0;
			ColorGL = 64 / 255.0;
			ColorBL = 64 / 255.0;
			break;
			//  Select grey color
		case 5:
			ColorRL = 128 / 255.0;
			ColorGL = 128 / 255.0;
			ColorBL = 128 / 255.0;
			break;
			//  Select green color
		case 6:
			ColorRL = 0 / 255.0;
			ColorGL = 255 / 255.0;
			ColorBL = 0 / 255.0;
			break;
			//  Select light gray color
		case 7:
			ColorRL = 192 / 255.0;
			ColorGL = 192 / 255.0;
			ColorBL = 192 / 255.0;
			break;
			//  Select magenta color
		case 8:
			ColorRL = 192 / 255.0;
			ColorGL = 64 / 255.0;
			ColorBL = 192 / 255.0;
			break;
			//  Select orange color
		case 9:
			ColorRL = 255 / 255.0;
			ColorGL = 192 / 255.0;
			ColorBL = 64 / 255.0;
			break;
			//  Select pink color
		case 10:
			ColorRL = 255 / 255.0;
			ColorGL = 0 / 255.0;
			ColorBL = 255 / 255.0;
			break;
			//  Select red color
		case 11:
			ColorRL = 255 / 255.0;
			ColorGL = 0 / 255.0;
			ColorBL = 0 / 255.0;
			break;
			//  Select white color
		case 12:
			ColorRL = 255 / 255.0;
			ColorGL = 255 / 255.0;
			ColorBL = 255 / 255.0;
			break;
			//  Select yellow color
		case 13:
			ColorRL = 255 / 255.0;
			ColorGL = 255 / 255.0;
			ColorBL = 0 / 255.0;
			break;
		case 14:
			ColorRL = 0 / 255.0;
			ColorGL = 0 / 255.0;
			ColorBL = 0 / 255.0;
			break;
		}
		break;
	}
}