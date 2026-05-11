#pragma once

#pragma region Includes
#include <stdlib.h>
#include "GLCompat.h"
#include <stdio.h>
#include <math.h>
#include "Torid.h"
#include "Geometry.h"
#include "ComplexObject.h"

#ifdef _MSC_VER
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#endif
#pragma endregion 

float length = 20;

#pragma region Углы и время
float angle = 0;

DWORD startTime;
DWORD currTime;
int FPS;
#pragma endregion

// For AntiAli
float scale = 0.03f;

#pragma region Camera
float   camera[9] = {   0, 0, -50, 
                        0, 0, 0, 
                        0, 1, 0};
Point3f p3camera;
#pragma endregion

#pragma region Lighting
int light_count = 0;
bool lights[10]={true,true,true,true,true,true,true,true,true,true};

GLfloat LightAmbient1[]=		{ 0.01f, 0.01f, 0.01f, 1.0f };
GLfloat LightDiffuse1[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition1[]=	    { 10.0f, 10.0f, 0.0f, 1.0f };

GLfloat LightAmbient2[]=		{ 0.f, 0.0f, 0.0f, 1.0f };
GLfloat LightDiffuse2[]=		{ 0.99f, 0.99f, 0.99f, 1.0f };
GLfloat LightPosition2[]=	    { -10.0f, 10.0f, 0.0f, 1.0f };
#pragma endregion

#pragma region Fog
GLfloat fogColor[4] = {0.5f, 0.5f, 0.5f, 1.0f}; // Цвет тумана
#pragma endregion

#pragma region Опции
bool lighting = true;
bool antiali = true;
bool fog     = true;
bool normals = false;
bool bland   = true;
#pragma endregion

const int TEXDIM = 256;