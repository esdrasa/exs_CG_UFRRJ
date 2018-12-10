#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define INICIO -3
#define FIM 3
#define SIZE 80

int desiredFPS = 30;

float xtrans = -2.5, ytrans = -2.5, xtransParcial = xtrans, ytransParcial = ytrans;


void init (void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(INICIO, FIM, INICIO, FIM, INICIO, FIM);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void drawBoard () {
  for (int linha = INICIO; linha < FIM; linha++) {
      for (int coluna = INICIO; coluna < FIM; coluna ++) {
        
        if (linha % 2 == 0) {
          if (coluna % 2 == 0) glColor3f (255.0, 255.0, 255.0);
          else glColor3f (0.0, 0.0, 0.0);
        } else {
          if (coluna % 2 == 0) glColor3f (0.0, 0.0, 0.0);
          else glColor3f (255.0, 255.0, 255.0);
        }

        glBegin(GL_POLYGON);
          glVertex3f(linha, coluna, 0);
          glVertex3f(linha + 1, coluna, 0);
          glVertex3f(linha + 1, coluna + 1, 0);
          glVertex3f(linha, coluna + 1, 0);
        glEnd();
      }
   }
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); 

   drawBoard();

   glPushMatrix();
      glColor3f(255.0, 0.0, 0.0);
      glTranslatef(xtransParcial, ytransParcial, 0.0);
      glutSolidSphere(0.5, 20, 20);
   glPopMatrix();

   glutSwapBuffers ();
}

void attPosicaoCirculo () {
    if (xtransParcial < xtrans)
      xtransParcial += 0.25;
    else if (xtransParcial > xtrans)
      xtransParcial -= 0.25;

    if (ytransParcial < ytrans)
      ytransParcial += 0.25;
    else if (ytransParcial > ytrans)
      ytransParcial -= 0.25;
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
     

     attPosicaoCirculo();

    tLast = t;

    glutPostRedisplay();

}

float coordenada (int p) {
  if (p == 0) return - 2.5;
  else if (p == 1) return - 1.5;
  else if (p == 2) return - 0.5;
  else if (p == 3) return 0.5;
  else if (p == 4) return 1.5;
  else return 2.5;
}

void mouse(int button, int state, int x, int y)
{
  if (xtrans == xtransParcial && ytrans == ytransParcial) {
    int posX = x / SIZE, posY = (480 - y) / SIZE;
    xtrans = coordenada(posX);
    ytrans = coordenada(posY);
  }

}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (480, 480);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Transformacao geometrica - Exercício 3");
   glutIdleFunc( idle);
   glutMouseFunc( mouse );
   init ();
   glutDisplayFunc(display);
   glutMainLoop();

   return 0;
}
