#pragma once

#include <gl/glut.h>
#include <math.h>

typedef struct tagPoint3f  
{
    float x;
    float y;
    float z;
} Point3f;

typedef struct tagQuad
{
    Point3f p[4];
    Point3f n[4];
} Quad;

const double PI = 4.0*atan(1.0);
const double PI2 = 8.0*atan(1.0);

class Geometry
{
public:
    Geometry(void);
    ~Geometry(void);

    // Calculate distance form A to B
    static inline float Distance(Point3f A, Point3f B)
    {
        Point3f C = GetVector(A.x-B.x, A.y - B.y, A.z-B.z);
        return sqrt(C.x*C.x+C.y*C.y+C.z*C.z);
    }

    // Calculate distance form A to B
    static inline float SQDistance(float x1, float y1, float z1, float x2, float y2, float z2)
    {
        float x = x1-x2; x *= x;
        float y = y1-y2; y *= y;
        float z = z1-z2; z *= z;
        return x+y+z;
    }

    // Векторное A-B
    static Point3f Difference(Point3f A, Point3f B)
    {
        return GetVector(A.x-B.x, A.y-B.y, A.z-B.z);
    }

    // Векторное A+B
    static Point3f Summ(Point3f A, Point3f B)
    {
        return GetVector(A.x+B.x, A.y+B.y, A.z+B.z);
    }

    // Получаем вектор по тройке(x,y,z)
    static Point3f GetVector(float x, float y, float z)
    {
        Point3f r;
        r.x = x;
        r.y = y;
        r.z = z;
        return r;
    }

    // Нормализация вектора
    static Point3f Normalize(Point3f V)
    {
        float r = Distance(GetVector(0,0,0), V);
        return GetVector(V.x/r, V.y/r, V.z/r);
    }


    // Векторное произведение
    //  | i    j    k   |
    //  | a.x  a.y  a.z | 
    //  | b.x. b.y  b.z |
    static Point3f Cross(Point3f A, Point3f B)
    {
        return GetVector(A.y*B.z-A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x);
    }

    // Вращение вектора вопкуг номали(по часовой стрелке)
    static Point3f Rotate(Point3f V, Point3f N, float angle)
    {
        float sinA = sin(angle);
        float cosA = cos(angle);

        float M[3][3] = {
            { cosA + (1-cosA)*N.x*N.x,   (1-cosA)*N.x*N.y-sinA*N.z, (1-cosA)*N.x*N.z+sinA*N.y },
            { (1-cosA)*N.x*N.y+sinA*N.z, cosA + (1-cosA)*N.y*N.y,   (1-cosA)*N.y*N.z-sinA*N.x },
            { (1-cosA)*N.x*N.z-sinA*N.y, (1-cosA)*N.y*N.z+sinA*N.x, cosA + (1-cosA)*N.z*N.z }
        };

        return GetVector( // M*V = V повернутый
            M[0][0]*V.x+M[0][1]*V.y+M[0][2]*V.z,
            M[1][0]*V.x+M[1][1]*V.y+M[1][2]*V.z,
            M[2][0]*V.x+M[2][1]*V.y+M[2][2]*V.z
            );
    }

    // Умнодение вектора на константу
    static Point3f Mult(Point3f V, float lambda)
    {
        return GetVector(V.x*lambda, V.y*lambda, V.z*lambda);
    }

    static void ReflectMatrix(
        GLfloat reflection_matrix[4][4], 
        GLfloat plane_point[3], 
        GLfloat plane_normal[3])
    {
        GLfloat* p = (GLfloat*)plane_point;
        GLfloat* v = (GLfloat*)plane_normal;
        float pv = p[0]*v[0]+p[1]*v[1]+p[2]*v[2];

        reflection_matrix[0][0] = 1 - 2 * v[0] * v[0];
        reflection_matrix[1][0] = - 2 * v[0] * v[1];
        reflection_matrix[2][0] = - 2 * v[0] * v[2];
        reflection_matrix[3][0] = 2 * pv * v[0];

        reflection_matrix[0][1] = - 2 * v[0] * v[1];
        reflection_matrix[1][1] = 1- 2 * v[1] * v[1];
        reflection_matrix[2][1] = - 2 * v[1] * v[2];
        reflection_matrix[3][1] = 2 * pv * v[1];

        reflection_matrix[0][2] = - 2 * v[0] * v[2];
        reflection_matrix[1][2] = - 2 * v[1] * v[2];
        reflection_matrix[2][2] = 1 - 2 * v[2] * v[2];
        reflection_matrix[3][2] = 2 * pv * v[2];

        reflection_matrix[0][3] = 0;
        reflection_matrix[1][3] = 0;
        reflection_matrix[2][3] = 0;
        reflection_matrix[3][3] = 1;
    }

};
