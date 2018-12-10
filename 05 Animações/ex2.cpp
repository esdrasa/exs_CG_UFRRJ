#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "extras.h"
#include <math.h>

int width  = 1000, height = 500;
float rotationX = 0.0, rotationY = 0.0, sphereSize = 30.0, passoX = 6, passoY = -1;
float last_x = 20, last_y = 400, desiredFPS = 15, last_y_aux = 20, alturaMaxima = 400;


void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void keyPRESS(int key, int x, int y)
{
   printf("%d\n", key);
   switch(key)
   {
      case GLUT_KEY_UP:
         if (passoX != 0) passoX += 1;
      break;
      case GLUT_KEY_DOWN:
         if (passoX != 0) passoX = passoX - 1 < 1 ? 1 : passoX - 1;
        break;
      default:
         printf("\nPressiona apenas as setas para cima ou para baixo!");
   break;
   }
   glutPostRedisplay();
}


void atualizarPosicaoEsfera () {
   if (last_x >= 980 || last_x < 20) 
      passoX *= -1;
   last_x += passoX;

   if (passoY < 0) {
      if (last_y_aux > 4) {
         last_y_aux += passoY;
         last_y = pow(last_y_aux, 2);
      } else {
         passoY *= -1;
         alturaMaxima *= 0.75;
      }
   } else if (passoY > 0) {
      last_y_aux += passoY;
      float aux = pow(last_y_aux, 2);
      if (aux <= alturaMaxima) {
         last_y = aux;
      } else {
         passoY *= -1;
      }
   } 
}

void idle()
{
   float t, desiredFrameTime, frameTime;
   static float tLast = 0.0;

   t = glutGet(GLUT_ELAPSED_TIME);
   t /= 1000.0;

   frameTime = t - tLast;
   desiredFrameTime = 1.0 / (float) (desiredFPS);

   if( frameTime <= desiredFrameTime)
     return;

   atualizarPosicaoEsfera();

   tLast = t;
   glutPostRedisplay();
}

void init(void)
{
   glClearColor (0.0,0.0,0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);               
    initLight(width, height);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(0.0, width, 0.0, height, -sphereSize, sphereSize);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   setMaterial();

   glPushMatrix();
      glTranslatef(last_x, last_y, 0.0); 
      glutSolidSphere(20.0, 100, 100);
    glPopMatrix();

   glutSwapBuffers();
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Animacoes - Exercicio 2");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(keyPRESS);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}
