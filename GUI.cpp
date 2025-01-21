#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
using namespace std;

struct Movement
{
 float rotate;
} ice, cube, octahedron;
bool isMoving = true;
bool is2DMode = false;
float lightPos[] = {10.0f, 10.0f, 10.0f, 1.0f};
int windowWidth = 800, windowHeight = 600;

void init4D();
void display();
void iceCream();
void object2D();
void createMenu();
void update(int value);
void processMenu(int option);
void drawText(float x, float y, float z, string text, int fontSize);


int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(800, 600);
 glutInitWindowPosition(100, 100);
 glutCreateWindow("GUI [Ice Cream & 2D Object]");
 init3D();
 glutDisplayFunc(display);
 createMenu();
 glutTimerFunc(1000 / 60, update, 0);
 glutMainLoop();
 return 0;
}
void iceCream()
{
 glLineWidth(5);
 glPushMatrix();
 glRotated(ice.rotate, 0.0, 1.0, 0.0);
 drawText(-25.0, 15.0, 0.0, "Ice Cream", 15);

 
 glRotated(80, 1, 0, 0);
 glColor3ub(229, 214, 150);
 glutSolidCone(7.5, 25.0, 10, 10);
 glColor3ub(208, 190, 157);
 glutWireCone(7.75, 25.0, 10, 10);

 
 glTranslated(0.0, 0.0, -6.0);
 glColor3ub(253, 245, 201);
 glutSolidSphere(10.0, 10, 10);
 glTranslated(0.0, 0.0, -12.0);
 glColor3ub(255, 197, 217);
 glutSolidSphere(8.0, 10, 10);

 
 glPushMatrix();
 glLineWidth(1);
 glTranslated(15.0, 0.0, 0.0);
 glRotated(cube.rotate, 1.0, 1.0, 1.0);
 glColor3ub(162, 148, 249);
 glutSolidCube(3.0);
 glutWireCube(3.5);
 glPopMatrix();

 
 glPushMatrix();
 glLineWidth(1);
 glTranslated(-15.0, 0.0, 10.0);
 glRotated(octahedron.rotate, 1.0, 1.0, 1.0);
 glColor3ub(242, 107, 15);
 glScaled(2, 2, 2);
 glutSolidOctahedron();
 glScaled(1.2, 1.2, 1.2);
 glutWireOctahedron();
 glPopMatrix();
 glPopMatrix();
}

void object2D(){
    glColor3f(0.2, 0.6, 0.8);
    glBegin(GL_QUADS);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (is2DMode)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        
        object2D();
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        iceCream();
    }
    glutSwapBuffers();
}

void init3D(){


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);



    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPos[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 1.0, 100.0);
    gluLookAt(30.0, 30.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void processMenu(int option)
{
    switch (option)
    {
    case 1:
        is2DMode = false;
        init3D();
        break;
    case 2:
        is2DMode = true;
        break;
    case 3:
        isMoving = !isMoving;
        break;
    case 4:
        exit(0);
    }
    glutPostRedisplay();
}

void createMenu(){
    glutCreateMenu(processMenu);
    glutAddMenuEntry("ice cream", 1);
    glutAddMenuEntry("objek 2D", 2);
    glutAddMenuEntry("Berhenti Bergerak", 3);
    glutAddMenuEntry("Keluar", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void update(int value){
    if (is2DMode)
    {
        if (isMoving)
        {
            ice.rotate += 0.15;
            cube.rotate += 1.2;
            octahedron.rotate += 1.8;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(1000 / 60, update, 0);
}

void drawText(float x, float y,float z, string text,int fontSize){
    glColor3ub(0, 255, 255);
    glPushMatrix();
    glTranslatef(x, y, z);

    glScalef(fontSize / 8.0f, fontSize / 13.0f, 1.0f);

    glRasterPos2f(0, 0);

    glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char *)text.c_str());
    glPopMatrix();
    glEnd();
}
