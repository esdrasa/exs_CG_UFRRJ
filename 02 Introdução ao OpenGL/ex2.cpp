#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

/*void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);
void keyPRESS(int key, int x, int y);*/

int partes = 0;

void display(void){

   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_LINES);
      glVertex3f (0.0, -2.0, 0.0);
      glVertex3f (0.0, 2.0, 0.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f (-10.0, 0.0, 0.0);
      glVertex3f (390.0, 0.0, 0.0);
   glEnd();

   glColor3f (0.0, 255.0, 0.0);

   const float volta = 360.0;
   float discretizacao;

   glBegin(GL_LINE_STRIP);

   if (partes == 0) discretizacao = volta / 6.0;   
   else if (partes == 1) discretizacao = volta / 12.0;
   else discretizacao = volta / 180.0;

   float fatorConversao = M_PI / 180.0;

   for (float i = 0.0; i <= volta; i += discretizacao) {
      glVertex3f(i, sin(i * fatorConversao), 0.0);
   }

   glEnd();

   glutSwapBuffers ();
}


void init (void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glMatrixMode(GL_PROJECTION);              
   glLoadIdentity();
   glOrtho(-10.0, 390, -2, 2, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW); 
   glLoadIdentity();           
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 27:
         exit(0);
         break;
   }
}

void keyPRESS(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			partes = partes + 1 > 2 ? 0 : partes + 1;
		break;
		case GLUT_KEY_DOWN:
			partes = partes - 1 < 0 ? 2 : partes - 1;
        break;
		default:
			printf("\nPressiona apenas as setas para cima ou para baixo!");
	break;
	}
	glutPostRedisplay();
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (450, 390);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Introducao ao OpenGL - Exercício 2");
   init();
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(keyPRESS);
   glutMainLoop();

   return 0;
}