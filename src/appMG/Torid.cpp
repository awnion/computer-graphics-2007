#include "Torid.h"

Torid::Torid(int detaleU, int detaleV, float k, float r)
{
    DetaleU = detaleU;
    DetaleV = detaleV;
    K = k;
    R = r;

    Quads   = new Quad[DetaleU*DetaleV];
    Points  = new Point3f[DetaleU*DetaleV];
    Normals = new Point3f[DetaleU*DetaleV];

    QuadsCount = DetaleU*DetaleV;
    PointsCount = 0;
}

Torid::~Torid(void)
{
    delete Quads;
    delete Points;
}

void Torid::Generate(void)
{
    PointsCount = 0;
    #pragma region Задаем точки, нормали и квадры 
    //Обход по первому параметру
    for (int U = 0; U < DetaleU ; U ++ )
    {
        // Вектор промежуточного центра
        Point3f c = GetC( U );

        // Вектор поворота
        Point3f n = Geometry::Normalize(Geometry::Difference(
            GetC( U+1 ), 
            GetC( U-1 )));

        for (int V = 0; V < DetaleV; V++ )
        {
            #pragma region Расширение до трубы

            Point3f v;

            float ang = PI2*V/DetaleV;

            v = Geometry::Cross(c, n);
            v = Geometry::Normalize(v);
            v = Geometry::Rotate(v, n, ang);

            // В v лежит нормаль, причем нормализованная
            Normals[PointsCount] = Geometry::Normalize(v);

            v = Geometry::Summ(Geometry::Mult(v, R), c);

            Points[PointsCount] = v;
            #pragma endregion

            #pragma region Зполняем квадры, чоответствующие данной точке
            //    ^------|------^
            //    | Наш  |Придыд|
            //    |------O------|
            //    | предыд-линия|
            //    ^------|------^

            int tmpCount = PointsCount;
            
            // Наш квадрат
            Quads[tmpCount].p[0] = Points[PointsCount];
            Quads[tmpCount].n[0] = Normals[PointsCount];

            // Предыдущий квадрат
            tmpCount = PointsCount - 1;
            if ( V == 0 ) tmpCount += DetaleV;

            Quads[tmpCount].p[1] = Points[PointsCount];
            Quads[tmpCount].n[1] = Normals[PointsCount];

            // Предыдущая линия, предыд квадр
            tmpCount -= DetaleV;
            if ( U == 0 ) tmpCount = (tmpCount+DetaleV)%DetaleV + DetaleV*(DetaleU-1);
            Quads[tmpCount].p[2] = Points[PointsCount];
            Quads[tmpCount].n[2] = Normals[PointsCount];

            // Предыдущая линия, смежный с нашим квадр
            tmpCount += 1;
            if ( V == 0 ) tmpCount -= DetaleV;
            Quads[tmpCount].p[3] = Points[PointsCount];
            Quads[tmpCount].n[3] = Normals[PointsCount];

            #pragma endregion
            PointsCount++;
        }
    }
    #pragma endregion
}
