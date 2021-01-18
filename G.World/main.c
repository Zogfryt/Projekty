#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#define ROZ_X 1000
#define ROZ_Y 1000
static double powierz[ROZ_X][ROZ_Y] = {0};
static int czworo[ROZ_X][ROZ_Y] = {0};
static int cube[ROZ_X][ROZ_Y] = {0};
static int pira[ROZ_X][ROZ_Y] = {0};
GLfloat KAT=0, PI=3.14, PX=-ROZ_X/2,PY=-5,PZ=-ROZ_Y/2,KAT2=0;
int window_height = 1080,window_width = 1920;

void init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3,3,-3,3,2,150);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}
void mount(int px, int py, int r1, int r2, int wys)
{
    for(int i=-r1/2;i<r1/2;i++)
        for(int j=-r1/2;j<r1/2;j++)
            if(2*sqrt(i*i+j*j)<r1)
                if(wys<(r1-2*sqrt(i*i+j*j))*wys/(r1-r2))
                   powierz[(i+px+ROZ_X)%ROZ_X][(j+py+ROZ_Y)%ROZ_Y] += wys;
                else
                    powierz[(i+px+ROZ_X)%ROZ_X][(j+py+ROZ_Y)%ROZ_Y] += (r1-2*sqrt(i*i+j*j))*wys/(r1-r2);
}
void init_board(int C_mount, int M_rad, int M_Height)
{
    srand(time(NULL)+4);
    int r1,r2,px,py,wys;
    for(int a=0; a<C_mount;a++)
    {
        r1 = rand()*M_rad/RAND_MAX;
        r2 = rand()*(r1/2)/RAND_MAX;
        wys= rand()*M_Height/RAND_MAX;
        px=rand()*ROZ_X/RAND_MAX;
        py = rand()*ROZ_Y/RAND_MAX;
        mount(px,py,r1,r2,wys);
    }
}

void init_czworoboki(int C_czworo)
{
    srand(time(NULL)+3);
    int px,py;
    for(int a=0; a<C_czworo; a++) {
        px = rand() * ROZ_X / RAND_MAX;
        py = rand() * ROZ_Y / RAND_MAX;
        czworo[px % ROZ_X][py % ROZ_Y]++;
    }
}

void init_cubes(int C_czworo)
{
    srand(time(NULL)+2);
    int px,py;
    for(int a=0; a<C_czworo; a++) {
        px = rand() * ROZ_X / RAND_MAX;
        py = rand() * ROZ_Y / RAND_MAX;
        cube[px % ROZ_X][py % ROZ_Y]++;
    }
}

void init_pira(int C_czworo)
{
    srand(time(NULL));
    int px,py;
    for(int a=0; a<C_czworo; a++) {
        px = rand() * ROZ_X / RAND_MAX;
        py = rand() * ROZ_Y / RAND_MAX;
        pira[px % ROZ_X][py % ROZ_Y]++;
    }
}
void init_img()
{
    unsigned char buf[256*256*3];
    long i;
    FILE *ws;
    if((ws=fopen("grass.bmp","rb"))==NULL) {printf("blad otwarcia"); return;}
    fseek(ws,-256*256*3, SEEK_END);
    for(i=0;i<256*256*3;i+=3) {
        buf[i + 2] = getc(ws);
        buf[i + 1] = getc(ws);
        buf[i] = getc(ws);
    }
    fclose(ws);

    glTexImage2D(GL_TEXTURE_2D,0,3,256,256,0,GL_RGB,GL_UNSIGNED_BYTE,buf);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glEnable(GL_TEXTURE_2D);
}

void display(void)
{
    glLoadIdentity();
    glRotatef(-KAT,0,1,0);
    PY=-powierz[(int)(-PX)][(int)(-PZ)]-6;
    glTranslatef(PX,PY,PZ);
    glClearColor(0.2,0.2,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glColor3f(0,0,0);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for(int x=0;x<ROZ_X-1;x++)
        for(int y=0;y<ROZ_Y-1;y++)
        {
            glTexCoord2f(0,0);  glVertex3f(x, powierz[x][y],y);
            glTexCoord2f(0,1);  glVertex3f(x, powierz[x][y+1],y+1);
            glTexCoord2f(1,1);  glVertex3f(x+1, powierz[x+1][y+1],y+1);
            glTexCoord2f(1,0);  glVertex3f(x+1,powierz[x+1][y],y);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,0.0f);
    glBegin(GL_QUADS);
    for(int x=0;x<ROZ_X-1;x++)
        for(int y=0;y<ROZ_Y-1;y++)
        if(czworo[x][y]==1)
        {
            glVertex3f(x,powierz[x][y],y);
            glVertex3f(x+1,powierz[x][y],y);
            glVertex3f(x+1,powierz[x][y],y+1);
            glVertex3f(x,powierz[x][y],y+1);

            glVertex3f(x,powierz[x][y],y);
            glVertex3f(x+1,powierz[x][y],y);
            glVertex3f(x+1,powierz[x][y]+1,y);
            glVertex3f(x,powierz[x][y]+1,y);


            glVertex3f(x+1,powierz[x][y],y);
            glVertex3f(x+1,powierz[x][y]+1,y);
            glVertex3f(x+1,powierz[x][y]+1,y+1);
            glVertex3f(x+1,powierz[x][y],y+1);


            glVertex3f(x+1,powierz[x][y]+1,y+1);
            glVertex3f(x+1,powierz[x][y],y+1);
            glVertex3f(x,powierz[x][y],y+1);
            glVertex3f(x,powierz[x][y]+1,y+1);


            glVertex3f(x,powierz[x][y],y);
            glVertex3f(x+1,powierz[x][y]+1,y);
            glVertex3f(x,powierz[x][y]+1,y+1);
            glVertex3f(x,powierz[x][y],y+1);


            glVertex3f(x,powierz[x][y]+1,y);
            glVertex3f(x+1,powierz[x][y]+1,y);
            glVertex3f(x+1,powierz[x][y]+1,y+1);
            glVertex3f(x,powierz[x][y]+1,y+1);

        }
    glEnd();
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_QUADS);
    for(int x=0;x<ROZ_X-1;x++)
        for(int y=0;y<ROZ_Y-1;y++)
            if(cube[x][y]==1)
            {
                glVertex3f(x,powierz[x][y],y);
                glVertex3f(x+1,powierz[x][y],y);
                glVertex3f(x+1,powierz[x][y],y+1);
                glVertex3f(x,powierz[x][y],y+1);

                glVertex3f(x,powierz[x][y],y);
                glVertex3f(x+1,powierz[x][y],y);
                glVertex3f(x+1,powierz[x][y]+10,y);
                glVertex3f(x,powierz[x][y]+10,y);


                glVertex3f(x+1,powierz[x][y],y);
                glVertex3f(x+1,powierz[x][y]+10,y);
                glVertex3f(x+1,powierz[x][y]+10,y+1);
                glVertex3f(x+1,powierz[x][y],y+1);


                glVertex3f(x+1,powierz[x][y]+10,y+1);
                glVertex3f(x+1,powierz[x][y],y+1);
                glVertex3f(x,powierz[x][y],y+1);
                glVertex3f(x,powierz[x][y]+10,y+1);


                glVertex3f(x,powierz[x][y],y);
                glVertex3f(x+1,powierz[x][y]+10,y);
                glVertex3f(x,powierz[x][y]+10,y+1);
                glVertex3f(x,powierz[x][y],y+1);


                glVertex3f(x,powierz[x][y]+10,y);
                glVertex3f(x+1,powierz[x][y]+1,y);
                glVertex3f(x+1,powierz[x][y]+1,y+1);
                glVertex3f(x,powierz[x][y]+10,y+1);

            }
    glEnd();
    glColor3f(1.0f,0.0f,1.0f);
    glBegin(GL_TRIANGLES);
    for(int x=0;x<ROZ_X-1;x++)
        for(int y=0;y<ROZ_Y-1;y++)
            if(pira[x][y]==1)
            {
                glVertex3f(x-2,powierz[x][y]+4,y);
                glVertex3f(x+2,powierz[x][y]+4,y);
                glVertex3f(x,powierz[x][y]+4,y+2);

                glVertex3f(x-2,powierz[x][y]+4,y);
                glVertex3f(x+2,powierz[x][y]+4,y);
                glVertex3f(x,powierz[x][y],y);


                glVertex3f(x-2,powierz[x][y]+4,y);
                glVertex3f(x,powierz[x][y]+4,y+2);
                glVertex3f(x,powierz[x][y],y);


                glVertex3f(x+2,powierz[x][y]+4,y+1);
                glVertex3f(x,powierz[x][y]+4,y+2);
                glVertex3f(x,powierz[x][y],y);

            }
    glEnd();
    glColor3f(0.25f,0.075f,0.038f);
    glBegin(GL_QUADS);

    glVertex3d(600,powierz[600][600]-10,600);
    glVertex3d(615,powierz[600][600]-10,600);
    glVertex3d(615,powierz[600][600]+10,600);
    glVertex3d(600,powierz[600][600]+10,600);

    glVertex3d(615,powierz[600][600]-10,600);
    glVertex3d(615,powierz[600][600]-10,615);
    glVertex3d(615,powierz[600][600]+10,615);
    glVertex3d(615,powierz[600][600]+10,600);

    glVertex3d(600,powierz[600][600]-10,615);
    glVertex3d(615,powierz[600][600]-10,615);
    glVertex3d(615,powierz[600][600]+10,615);
    glVertex3d(600,powierz[600][600]+10,615);

    glVertex3d(600,powierz[600][600]-10,615);
    glVertex3d(600,powierz[600][600]-10,610);
    glVertex3d(600,powierz[600][600]+10,610);
    glVertex3d(600,powierz[600][600]+10,615);

    glVertex3d(600,powierz[600][600]+8,610);
    glVertex3d(600,powierz[600][600]+8,605);
    glVertex3d(600,powierz[600][600]+10,605);
    glVertex3d(600,powierz[600][600]+10,610);

    glVertex3d(600,powierz[600][600]-10,605);
    glVertex3d(600,powierz[600][600]-10,600);
    glVertex3d(600,powierz[600][600]+10,600);
    glVertex3d(600,powierz[600][600]+10,605);

    glColor3f(0.0f,0.0f,0.0f);
    glVertex3d(607.5f,powierz[600][600]+11,608.5f);
    glVertex3d(607.5f,powierz[600][600]+11,609.5f);
    glVertex3d(607.5f,powierz[600][600]+17,609.5f);
    glVertex3d(607.5f,powierz[600][600]+17,608.5f);

    glVertex3d(607.5f,powierz[600][600]+11,609.5f);
    glVertex3d(608.5f,powierz[600][600]+11,609.5f);
    glVertex3d(608.5f,powierz[600][600]+17,609.5f);
    glVertex3d(607.5f,powierz[600][600]+17,609.5f);

    glVertex3d(608.5f,powierz[600][600]+11,609.5f);
    glVertex3d(608.5f,powierz[600][600]+11,608.5f);
    glVertex3d(608.5f,powierz[600][600]+17,608.5f);
    glVertex3d(608.5f,powierz[600][600]+17,609.5f);

    glVertex3d(608.5f,powierz[600][600]+11,608.5f);
    glVertex3d(607.5f,powierz[600][600]+11,608.5f);
    glVertex3d(607.5f,powierz[600][600]+17,608.5f);
    glVertex3d(608.5f,powierz[600][600]+17,608.5f);


    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(600.0f,(GLfloat)powierz[600][600]+15,607.5f);
    glVertex3f(615.0f,(GLfloat)powierz[600][600]+15,607.5f);
    glVertex3f(615.0f,(GLfloat)powierz[600][600]+10,600.0f);
    glVertex3f(600.0f,(GLfloat)powierz[600][600]+10,600.0f);

    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(600.0f,(GLfloat)powierz[600][600]+15,607.5f);
    glVertex3f(615.0f,(GLfloat)powierz[600][600]+15,607.5f);
    glVertex3f(615.0f,(GLfloat)powierz[600][600]+10,615.0f);
    glVertex3f(600.0f,(GLfloat)powierz[600][600]+10,615.0f);

    glColor3f(0.0f,0.0f,0.0f);
    glVertex3d(600,powierz[600][600]+10,600);
    glVertex3d(600,powierz[600][600]+10,615);
    glVertex3d(615,powierz[600][600]+10,615);
    glVertex3d(615,powierz[600][600]+10,600);

    glEnd();
    glColor3f(0.349f,0.349f,0.349f);
    glBegin(GL_TRIANGLES);

    glVertex3f(600.0f,(GLfloat)powierz[600][600]+10,615.0f);
    glVertex3f(600.0f,(GLfloat)powierz[600][600]+10,600.0f);
    glVertex3f(600.0f,(GLfloat)powierz[600][600]+15,607.5f);

    glVertex3f(615.0f,(GLfloat)powierz[600][600]+10,615.0f);
    glVertex3f(615.0f,(GLfloat)powierz[600][600]+10,600.0f);
    glVertex3f(615.0f,(GLfloat)powierz[600][600]+15,607.5f);

    glEnd();
    glutSwapBuffers();
}

void keyboard (unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'a':
            KAT+=4;
            if(KAT>360)
                KAT-=360;
            glutPostRedisplay();
            break;
        case 'd':
            KAT-=4;
            if(KAT<0)
                KAT+=360;
            glutPostRedisplay();
            break;
        case 'w':
            PX +=sin(PI*KAT/180);
            PZ +=cos(PI*KAT/180);
            glutPostRedisplay();
            break;
        case 's':
            PX-=sin(PI*KAT/180);
            PZ-=cos(PI*KAT/180);
            glutPostRedisplay();
            break;
        default:
            glutPostRedisplay();
            break;
    }
}

void reshape (int w, int h) {
    window_width = w;
    window_height = h;

    glViewport(0, 0, window_width, window_height);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize (window_width, window_height);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("asdf world");
    init ();
    init_img();
    init_board(500,90,10);
    init_czworoboki(100);
    init_cubes(100);
    init_pira(50);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}