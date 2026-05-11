#include "main.h"

Torid T(100, 32, 5, 1);

// Генерим по адской формуле текстурку
GLfloat * make_texture(int maxs, int maxt)
{
    int s, t;
    static GLfloat *texture;

    texture = (GLfloat *) malloc(maxs * maxt * sizeof(GLfloat));
    for (t = 0; t < maxt; t++) {
        for (s = 0; s < maxs; s++) {
            texture[s + maxs * t] = ((s/(t+1) >> 4) & 0x1) ^ ((t*(s+1) >> 4) & 0x1);
        }
    }
    return texture;
}

void SourceOfLighting(const GLfloat * LightAmbient, 
                      const GLfloat * LightDiffuse, 
                      const GLfloat * LightPosition)
{
    if (!lighting)return;
    int lnum = GL_LIGHT0+light_count;
    glLightfv(lnum, GL_AMBIENT,  LightAmbient);		// Setup The Ambient Light
    glLightfv(lnum, GL_DIFFUSE,  LightDiffuse);		// Setup The Diffuse Light
    glLightfv(lnum, GL_POSITION, LightPosition);	    // Position The Light

    if (lights[light_count])
    {
        glDisable(GL_LIGHTING);
        glPushMatrix();
        glTranslatef( LightPosition[0], LightPosition[1], LightPosition[2] );
        glColor3f(1.0, 0.8, 0);
        glutSolidSphere(0.5, 20, 20);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }

    if (lights[light_count]){
        glEnable(lnum);
    }
    else
    {
        glDisable(lnum);
    }
    light_count++;
}



void RenderMirrorObject()
{
    glBegin(GL_QUADS);

    glNormal3f( 0, 0, 1 );
    glVertex3f( -length, -10, 0);
    glVertex3f( length, -10, 0);
    glVertex3f( length, 10, 0);
    glVertex3f( -length, 10, 0);

    glEnd();
}
void DrawT()
{
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glColor4f(0.1f,0.2f,0.1f, 1.f);

    if (bland)
    {
        glEnable(GL_BLEND);
        //glDisable(GL_DEPTH_TEST);
    }

    glBegin(GL_QUADS);
    for( int i = 0 ; i < T.QuadsCount ; i++ )
    {
        for( int j = 0 ; j < 4 ; j++ )
        {
            glNormal3f( T.Quads[i].n[j].x, T.Quads[i].n[j].y, T.Quads[i].n[j].z );
            glVertex3f( T.Quads[i].p[j].x, T.Quads[i].p[j].y, T.Quads[i].p[j].z );
        }
    }
    glEnd();

    glDisable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
}

void DrawTSkilet()
{
    glColor4f(1,0,0,1);
    glBegin(GL_LINES);
    for( int i = 0 ; i < T.QuadsCount ; i++ )
    {
        int j = 0;
        glNormal3f( T.Quads[i].n[j].x, T.Quads[i].n[j].y, T.Quads[i].n[j].z );
        glVertex3f( T.Quads[i].p[j].x, T.Quads[i].p[j].y, T.Quads[i].p[j].z );
        j++;
        glVertex3f( T.Quads[i].p[j].x, T.Quads[i].p[j].y, T.Quads[i].p[j].z );
        glVertex3f( T.Quads[i].p[j].x, T.Quads[i].p[j].y, T.Quads[i].p[j].z );
        j++;
        glVertex3f( T.Quads[i].p[j].x, T.Quads[i].p[j].y, T.Quads[i].p[j].z );
    }
    glEnd();    
}
void DrawTNormals()
{
    //if (lighting) glDisable(GL_LIGHTING);
    glColor4f(1,0,0,1);
    glBegin(GL_LINES);
    for( int i = 0 ; i < T.QuadsCount ; i++ )
    {
        Point3f p = T.Quads[i].p[0];
        Point3f n = T.Quads[i].n[0];
        glNormal3f( n.x, n.y, n.z );
        glVertex3f( p.x, p.y, p.z );
        p = Geometry::Summ(Geometry::Mult(n, 0.1f), p);
        glVertex3f( p.x, p.y, p.z );
    }
    glEnd();   
    //if (lighting) glEnable(GL_LIGHTING);
}
void DrawFlor( void )
{
    glBegin(GL_QUADS);

    glNormal3f(0,1,0);
    glVertex3f(-length, 0, -length);
    glVertex3f(length, 0, -length);
    glVertex3f(length, 0, length);
    glVertex3f(-length, 0, length);

    glEnd();
}

void DrawWallChess()
{
    glEnable(GL_TEXTURE_2D); 
    glBegin(GL_QUADS);

    glNormal3f( 1, 0, 0 );
    glColor3f( 1, 1, 1 );

    glTexCoord2i(0, 0);
    glVertex3f( 0, -10, -length);

    glTexCoord2i(1, 0);
    glVertex3f( 0, -10, length);

    glTexCoord2i(1, 1);
    glVertex3f( 0, 10, length);

    glTexCoord2i(0, 1);
    glVertex3f( 0, 10, -length);

    glEnd();
    glDisable(GL_TEXTURE_2D); 
}
void DrawAll( bool is_mirracle ) 
{
    
    glPushMatrix();
    glColor3f(0.1, 0.1, 0.3);
    glutSolidSphere(400, 20, 20);
    glPopMatrix();
    
    // Пол
    glPushMatrix();
    glTranslatef( 0.0f, -10.0f, -10.0f);
    glColor3f(0.0, 0.0, 0.0);
    DrawFlor();
    glPopMatrix();

    // Шахматная стенка
    glPushMatrix();
    glTranslatef( -length, -0.0f, -10.0f);
    glColor3f(0.1, 0.1, 0.3);
    DrawWallChess();
    glPopMatrix();

    // Lighting
    float R = 10;
    // 1
    GLfloat lp[] = {
        LightPosition1[0],//+R*sin(angle),
        LightPosition1[1],
        LightPosition1[2],//+R*cos(angle),
        LightPosition1[3]
    };
    SourceOfLighting( LightAmbient1, LightDiffuse1, lp);
    
    // 2
    lp[0] = LightPosition2[0];
    lp[1] = LightPosition2[1]+R*sin(angle);
    lp[2] = LightPosition2[2]+R*cos(angle);
    lp[3] = LightPosition2[3];
    SourceOfLighting( LightAmbient2, LightDiffuse2, lp );

    // Фигура
    if(bland&&!is_mirracle) T.Sort(camera[0], camera[1], camera[2] );
    if(bland&&is_mirracle) T.Sort(camera[0], camera[1], -20 - camera[2] );
    glPushMatrix();
    glTranslatef( 0.0f, 0.0f, 0.0f);
    DrawT();    
    //glCallList(T_LIST);
    glPopMatrix();

    if(normals){
        // Нормали, если надо
        glPushMatrix();
        glTranslatef( 0.0f, 0.0f, 0.0f);
        DrawTNormals();    
        glPopMatrix();
    }

}

void InitGL ( GLvoid )     // Create Some Everyday Functions
{
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glEnable ( GL_COLOR_MATERIAL );
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glCullFace(GL_BACK);
    // Делаем текстуру
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GLfloat * tex = make_texture(TEXDIM, TEXDIM);
    glTexImage2D(GL_TEXTURE_2D, 0, 1, TEXDIM, TEXDIM, 0, GL_RED, GL_FLOAT, tex);
    free(tex);


    glMaterialf( GL_FRONT_AND_BACK, GL_DIFFUSE, 1.0f );

    glEnable(GL_LIGHTING);

    startTime = GetTickCount();

    glEnable(GL_FOG);                       // Включает туман (GL_FOG)
    glFogi(GL_FOG_MODE, GL_LINEAR);         // Выбираем тип тумана
    glFogfv(GL_FOG_COLOR, fogColor);        // Устанавливаем цвет тумана
    glFogf(GL_FOG_DENSITY, 0.35f);          // Насколько густым будет туман
    glHint(GL_FOG_HINT, GL_DONT_CARE);      // Вспомогательная установка тумана
    glFogf(GL_FOG_START, 40.0f);            // Глубина, с которой начинается туман
    glFogf(GL_FOG_END, 100.0f);             // Глубина, где туман заканчивается.
}
void Render(float dx, float dy)
{
    // Обнуляем счетчик источников света
    light_count = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
    glLoadIdentity();

    gluLookAt(  
        camera[0]+dx,camera[1]+dy,camera[2]+dx*dy,
        camera[3]+dx,camera[4]+dy,camera[5],
        camera[6],camera[7],camera[8]);

    glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS,2,2);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);

    glDisable(GL_DEPTH_TEST);

    // Draw Mirror
    glPushMatrix();
    glTranslatef( 0.0f, 0.0f, 10.0f);
    glColor4f(0.1, 0.1, 0.9, 0.3);
    RenderMirrorObject();
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    glStencilFunc(GL_EQUAL,2,2);
    glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);

    glPushMatrix();
    //glScaled(1,1,1);
    GLfloat reflection_matrix[4][4], plane_point[3]={0,0,10}, plane_normal[3]={0,0,-1};
    Geometry::ReflectMatrix(reflection_matrix, plane_point, plane_normal);
    glMultMatrixf((float *)reflection_matrix);
    DrawAll(true);
    glPopMatrix();

    glDisable(GL_STENCIL_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    // Draw Mirror
    glPushMatrix();
    glTranslatef( 0.0f, 0.0f, 10.0f);
    glColor4f(0.1, 0.1, 0.9, 0.2);
    RenderMirrorObject();
    glPopMatrix();

    glDisable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
    glPopMatrix();

    DrawAll(false);

}
void display ( void )   // Create The Display Function
{
    // следим за веременем
    currTime = GetTickCount();
    FPS = 1000 / (currTime - startTime +1);
    printf("%d\n", FPS);
    angle += (float)(currTime - startTime) / 1000;
    startTime = currTime;

    if(antiali)
    {
        scale = Geometry::Distance(
                    Geometry::GetVector( camera[0], camera[1],  camera[2] ),
                    Geometry::GetVector( camera[3], camera[4],  camera[5] )
                    ) / 1000;
        glClear(GL_ACCUM_BUFFER_BIT);
        // Antialiasing 4x 
        Render( +scale, 0.0f   );
        glAccum(GL_ACCUM, 1.f/4);

        Render( -scale, 0.0f   );
        glAccum(GL_ACCUM, 1.f/4);

        Render(  0.0f , -scale );
        glAccum(GL_ACCUM, 1.f/4);

        Render(  0.0f , +scale );
        glAccum(GL_ACCUM, 1.f/4);

        glAccum(GL_RETURN, 1.f);
    }
    else
    {
        Render(0,0);
    }

    glutSwapBuffers ( );
    // Swap The Buffers To Not Be Left With A Clear Screen
}

void reshape ( int width , int height )   // Create The Reshape Function (the viewport)
{
    if (height==0)										// Prevent A Divide By Zero By
    {
        height=1;										// Making Height Equal One
    }

    glViewport(0,0,width,height);						// Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,700.0f);
    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix

}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
    int i = key-'1';
    switch ( key ) {
        case 'b':
        case 'B':
            bland =! bland;
            break;
        case '1':
        case '2':
        case '3':
        case '4':
            if (light_count > i)
            {
                lights[i] = !lights[i];
            }
            break;
        case 'n':
        case 'N':
            normals = !normals;
            break;
        case 'F':
        case 'f':
            fog = !fog;
            if (fog)
            {
                glEnable(GL_FOG);
            } 
            else
            {
                glDisable(GL_FOG);
            }
            break;
        case 'A':
        case 'a':
            antiali = !antiali;
            break;
        case 'L':
        case 'l':
            if(lighting){
                glDisable(GL_LIGHTING);
            }
            else{
                glEnable(GL_LIGHTING);
            }
            lighting = !lighting;
            break;
        /*case 'w':
        case 'W':
            camera[2] += 5;
            break;
        case 's':
        case 'S':
            camera[2] -= 5;
            break;*/
        case 27:            // When Escape Is Pressed...
            exit ( 0 );     // Exit The Program
            break;          // Ready For Next Case
        default:            // Now Wrap It Up
            break;
    }
}

void arrow_keys ( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{
    switch ( a_keys ) {
    case GLUT_KEY_UP:                   // When Up Arrow Is Pressed...
        camera[1] += 5;
        break;
    case GLUT_KEY_DOWN:                 // When Down Arrow Is Pressed...
        camera[1] -= 5;
        break;
    case GLUT_KEY_LEFT:
        camera[0] -= 5;
        break;
    case GLUT_KEY_RIGHT:
        camera[0] += 5;
        break;

    default:
        break;
    }
}



int main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{
    T.Generate();
    glutInit            ( &argc, argv ); // Erm Just Write It =)
    glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ACCUM | GLUT_STENCIL ); // Display Mode
    glutInitWindowSize  ( 800, 600 ); // If glutFullScreen wasn't called this is the window size
    glutCreateWindow    ( "WindowMode" ); // Window Title (argv[0] for current directory as title)
    glutFullScreen      ( );          // Put Into Full Screen
    InitGL ();
    glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
    glutReshapeFunc     ( reshape );
    glutKeyboardFunc    ( keyboard );
    glutSpecialFunc     ( arrow_keys );
    glutIdleFunc		( display );
    glutMainLoop        ( );          // Initialize The Main Loop
    return 0;
}
