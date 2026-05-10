#pragma once
#include <stdlib.h>
#include "Geometry.h"

class ComplexObject
{
public:
    ComplexObject(void);
    virtual ~ComplexObject(void);
    // Квардатеги =)
    Quad * Quads;
    int QuadsCount;
    // Вершины
    Point3f * Points;
    Point3f * Normals;
    int PointsCount;

    Point3f Camera;
    // Создает обьект
    virtual void Generate(void);

    // Сортировка
    void Sort(float x, float y, float z)
    {
        Camera = Geometry::GetVector(x,y,z);
        QSort(0, QuadsCount - 1);
    }

    void QSort(int f, int l)
    {
        int i = f;
        int j = l;
        int mid = (f+l)/2;
        float p;
        Quad tmp;
        p = Geometry::SQDistance(
            Quads[mid].p[0].x,
            Quads[mid].p[0].y,
            Quads[mid].p[0].z, 
            Camera.x,
            Camera.y,
            Camera.z
            );
        do
        {
            while ( Geometry::SQDistance( 
                Quads[i].p[0].x,
                Quads[i].p[0].y,
                Quads[i].p[0].z, 
                Camera.x,
                Camera.y,
                Camera.z) > p ) i++;
            while ( Geometry::SQDistance( 
                Quads[j].p[0].x,
                Quads[j].p[0].y,
                Quads[j].p[0].z, 
                Camera.x,
                Camera.y,
                Camera.z) < p ) j--;
            if(i<=j)
            {
                tmp = Quads[i]; Quads[i] = Quads[j]; Quads[j] = tmp;
                i++;
                j--;
            }
        } while ( i <= j );

        if ( j > f ) QSort( f, j );
        if ( l > i ) QSort( i, l );
    }
};
