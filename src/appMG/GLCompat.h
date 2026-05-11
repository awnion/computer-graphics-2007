#pragma once

#ifdef _WIN32
#include <windows.h>
#include <GL/glut.h>
#else
#ifdef __APPLE__
#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

typedef unsigned int DWORD;

static inline DWORD GetTickCount(void)
{
    return (DWORD)glutGet(GLUT_ELAPSED_TIME);
}
#endif
