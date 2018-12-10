#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define INICIO -15
#define FIM 15
#define PASSO 6

float rotationX = 45.0, rotationY = 0.0;
float last_x = -14, last_y = -9;
int width = 640, height = 300;

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glEnable(GL_LIGHT0);                   
   glEnable(GL_COLOR_MATERIAL);           
   glColorMaterial(GL_FRONT, GL_DIFFUSE);

   glEnable(GL_LIGHTING);                
   glEnable(GL_DEPTH_TEST);               
   glEnable(GL_CULL_FACE);                
}


void idle ()
{
   glutPostRedisplay();
}

void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void keyPRESS(int key, int x, int y)
{
   switch(key)
   {
      case GLUT_KEY_RIGHT:
      break;
      case GLUT_KEY_LEFT:
      break;
   break;
   }
   glutPostRedisplay();
}

void desenharGrid () {
  for (int linha = INICIO; linha < FIM; linha += PASSO) {
      for (int coluna = INICIO; coluna < FIM; coluna += PASSO) {

         glPushMatrix();
            glBegin(GL_POLYGON);
               glVertex3f(linha, coluna - PASSO, 0);
               glVertex3f(linha + PASSO, coluna - PASSO, 0);
               glVertex3f(linha + PASSO, coluna, 0);
               glVertex3f(linha, coluna, 0);
            glEnd();
         glPopMatrix();

      }
   }
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (0.0, 15.0, 20.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glColor3f (1, 1, 1);

   desenharGrid();
   

   glColor3f (1, 0, 0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   
   glPushMatrix();
      glScalef(1.02, 1.01, 1.01);
      glTranslatef(last_x, last_y, 0);
      glutSolidCube(6);
   glPopMatrix();

   glutSwapBuffers();
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (100, 100); 
   glutCreateWindow("Projecoes e Transformacoes em 3D - Exercicio 1");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(keyPRESS);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}

