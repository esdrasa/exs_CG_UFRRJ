#include <stdio.h>
#include <string.h>
#include "rayTracer.h"

using namespace std;
char cenario[512] = {"../data/ex1_2_3_rayTracingScene01.txt"};


glraytracer *glProject = NULL;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glProject->draw();

    glutSwapBuffers();
}

void idleFunc()
{
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        exit(0);
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    if(argc>1)
    {
        strcpy(cenario, argv[1]);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glProject = new glraytracer();
    glProject->readDatabase(cenario);

    int *w = glProject->getReader()->getWindowDimensions();

    glutInitWindowSize(w[0], w[1]);

    int window = glutCreateWindow("GL Raytracer");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w[0], 0, w[1]);

    glProject->setWindow(window);
    glProject->raytrace();

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyPRESS);
    glutMouseFunc(mouseButton);
    glutDisplayFunc(display);
    glutIdleFunc(idleFunc);

    glutMainLoop();
    return (0);
}