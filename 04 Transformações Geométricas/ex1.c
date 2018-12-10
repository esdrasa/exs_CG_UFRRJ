#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float shoulder = 0.0f, elbow = 0.0f, arm = 0.0f, claw = 0.0f;

int selected = 1;

void init(void)
{
	printf("Pressione as setas direita e esquerda para mover o braco.\n");
	printf("Selecione as teclas 1 e 2 para escolher o segmento a ser movido.\n");
	printf("Pressione ESC para sair.\n");

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glEnable(GL_LIGHT0);                  
   glEnable(GL_COLOR_MATERIAL);           
   glColorMaterial(GL_FRONT, GL_DIFFUSE);

   glEnable(GL_LIGHTING);                 
   glEnable(GL_DEPTH_TEST);               
   glEnable(GL_CULL_FACE);                
}



void keyboard (unsigned char key, int x, int y)
{
   switch (key)
   {
   case '1':
      selected = 1;
   break;
   case '2':
      selected = 2;
   break;
   case '3':
      selected = 3;
   break;
   case 27:
      exit(0);
      break;
   default:
      break;
   }
}

void drawAxis()
{
	glDisable(GL_LIGHTING);
   glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 10.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 10.0f);
   glEnd();
	glEnable(GL_LIGHTING);
}



void reshape (int w, int h)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (6.0, 6.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void definirBraco () {
   glRotatef (arm, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0); 
   glPushMatrix();
      glScalef (2.0, 0.5, 0.5);
      glutSolidCube (1.0);
   glPopMatrix();

   glTranslatef (1.0, 0.0, 0.0); 
   glRotatef (shoulder, 0.0, 0.0, 1.0); 
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
      glScalef (2.0, 0.5, 0.5);
      glutSolidCube (1.0);
   glPopMatrix();

   glTranslatef (1.0, 0.0, 0.0); 
   glRotatef (elbow, 0.0, 0.0, 1.0); 
   glTranslatef (1.0, 0.0, 0.0); 
   glPushMatrix();
      glScalef (2.0, 0.5, 0.5);
      glutSolidCube (1.0);
   glPopMatrix();
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   drawAxis();
	glColor3f(1.0f, 1.0f, 0.0f);

   glPushMatrix();
      definirBraco();
   glPopMatrix();
   glutSwapBuffers();
}


void keyPRESS(int key, int x, int y)
{
   switch(key)
   {
      case GLUT_KEY_LEFT:
         if(selected == 1) arm = ((int) arm + 5) % 360;
			if(selected == 2) shoulder = ((int) shoulder + 5) % 360;
			if(selected == 3) elbow = ((int) elbow + 5) % 360;
      break;
      case GLUT_KEY_RIGHT:
         if(selected == 1) arm = ((int) arm - 5) % 360;
			if(selected == 2) shoulder = ((int) shoulder - 5) % 360;
			if(selected == 3) elbow = ((int) elbow - 5) % 360;
      break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (640, 640);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Transformacao geometrica - Exercício 1.2");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(keyPRESS);
   glutMainLoop();
   return 0;
}
