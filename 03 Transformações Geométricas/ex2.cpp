#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float angle = 0, angleParcial = 0, scale = 1.0, scaleParcial = 1.0;
float xtrans = 0, ytrans = 0, ztrans = 0;
float xtransParcial = 0, ytransParcial = 0;
int desiredFPS = 30;


void showMenu()
{
   int op;
   printf("\n=== MENU ===");
   printf("\n1 - Translacao");
   printf("\n2 - Rotacao");
   printf("\n3 - Escala");
   printf("\n4 - Sair");
   printf("\nOpcao: ");

   scanf("%d", &op);
   switch(op)
   {
      case 1:
         printf("\n\nInforme o vetor de translacao (entre -100.0 e 100.0)");
         printf("\nX : ");
         scanf("%f", &xtrans);
         printf("Y : ");
         scanf("%f", &ytrans);
      break;
      case 2:
         printf("\n\nInforme o angulo de rotacao (em graus): ");
         scanf("%f", &angle);
      break;
      case 3:
         printf("\n\nInforme o fator de escala: ");
         scanf("%f", &scale);
      break;
      case 4:
         exit(1);
      break;
      default:
         printf("\n\nOpcao invalida\n\n");
      break;
   }
}

void drawAxis()
{
   glColor3f (0.0, 1.0, 0.0);
   glBegin(GL_LINES);
      glVertex2f (0.0, -100.0);
      glVertex2f (0.0, 100.0);
      glVertex2f (-100.0, 0.0);
      glVertex2f (100.0, 0.0);
   glEnd();
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); 
   drawAxis();

   glColor3f (1.0, 0.0, 0.0);

   glPushMatrix();
      glTranslatef(xtransParcial, ytransParcial, 0.0);
      glRotatef(angleParcial, 0.0, 0.0, 1.0);
      glScalef(scaleParcial, scaleParcial, scaleParcial);
      glutWireCube(10);
   glPopMatrix();

   glutSwapBuffers ();

   if(xtrans == xtransParcial && angle == angleParcial && scale == scaleParcial) showMenu();
}

void init (void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void attQuadrado () {
    if (xtransParcial < xtrans)
      xtransParcial += 1;
    else if (xtransParcial > xtrans)
      xtransParcial -= 1;

    if (ytransParcial < ytrans)
      ytransParcial += 1;
    else if (ytransParcial > ytrans)
      ytransParcial -= 1;

    if (angleParcial < angle)
      angleParcial += 1;
    else if (angleParcial > angle)
      angleParcial -= 1;

   if (scaleParcial < scale)
      scaleParcial += 0.25;
    else if (scaleParcial > scale)
      scaleParcial -= 0.25;
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

  
     attQuadrado();
    tLast = t;

    glutPostRedisplay();

}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Transformacao geometrica - Exercício 2");
   glutIdleFunc( idle);
   init ();
   glutDisplayFunc(display);
   glutMainLoop();

   return 0;
}

