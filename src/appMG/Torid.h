#pragma once
#include <math.h>

#include "ComplexObject.h"
#include "Geometry.h"

class Torid :
    public ComplexObject
{
public:
    int DetaleU;
    int DetaleV;
    float K;
    float R;

    Torid(int detaleU, int detateV, float k, float r);
    Torid(const Torid&) = delete;
    Torid& operator=(const Torid&) = delete;
    ~Torid(void) override;
    void Generate(void) override;
private:
    Point3f GetC(int U)
    {
        Point3f c;

        float ang = PI2 * U / DetaleU;
        float ang1 = ang*2;
        float ang2 = ang*7;

        float tmp = (float) ( K + cos(ang2)*K/4);

        c.y = (float) ( sin( ang2 ) * K/4 );

        c.x = (float) ( cos( ang1 ) * tmp );
        c.z = (float) ( sin( ang1 ) * tmp );

        return c;
    }
};
