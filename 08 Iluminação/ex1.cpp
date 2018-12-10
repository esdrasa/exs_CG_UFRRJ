#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int width  = 700;
int height = 700;

int anguloRotacao = 0;
float kc = 0.1f;
float kl = 0.04f;
float kq = 0.0005f;

int luzVerde = 1, luzAzul = 1, luzVermelha = 1;

GLfloat base_ambient[]   = { 0.1, 0.1, 0.1, 1.0 };
GLfloat base_difusa[]    = { 0.8, 0.0, 0.0, 1.0 };
GLfloat base_especular[] = { 0.8, 0.0, 0.0, 1.0 };
GLfloat base_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat base_brilho[]    = { 128.0 };

GLfloat object_ambient[]   = { 0.25725, 0.1995, 0.0745, 1.0 };
GLfloat object_difusa[]    = { 0.80164, 0.60648, 0.22648, 1.0 };
GLfloat object_especular[] = { 0.828281, 0.555802, 0.366065, 1.0 };
GLfloat object_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat object_brilho[]    = { 160.0 };

GLfloat cor_luz_amb[]	= { 0.02, 0.02, 0.02, 0.02};
GLfloat cor_emissao[]	= { 0.2, 0.2, 0.0, 1.0 };

GLfloat posicao_luz_verde[] = { -10.0f, 7.0f, 3.5, 1.0};
GLfloat cor_luz_verde[] = { 0.0, 1.0, 0.0, 1.0};

GLfloat posicao_luz_vermelha[] = { 10.0f, 7.0f, 3.5, 1.0};
GLfloat cor_luz_vermelha[] = { 1.0, 0.0, 0.0, 1.0};

GLfloat posicao_luz_azul[] = { -10.0f, 7.0f, 3.5, 1.0};
GLfloat cor_luz_azul[] = { 0.0, 0.0, 1.0, 1.0};

GLfloat bar_ambient[]   = { 0.5, 0.5, 0.5, 1.0 };
GLfloat bar_difusa[]    = { 0.5, 0.5, 0.5, 1.0 };
GLfloat bar_especular[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat bar_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat bar_brilho[]    = { 128.0 };

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);               
   glEnable(GL_LIGHTING);                 
   glEnable(GL_LIGHT0);                  
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT2);

   GLfloat cor_verde[] = { 0, 1, 0, 1.0};
   GLfloat cor_luz_vermelha[] = { 1, 0, 0, 1.0};
   GLfloat cor_luz_azul[] = { 0, 0, 1, 1.0};


   glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz_amb);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz_verde);
   glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz_verde);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz_verde);
 
   glLightfv(GL_LIGHT1, GL_AMBIENT, cor_luz_amb);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, cor_luz_vermelha);
   glLightfv(GL_LIGHT1, GL_SPECULAR, cor_luz_vermelha);
   glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz_vermelha);

   glLightfv(GL_LIGHT2, GL_AMBIENT, cor_luz_amb);
   glLightfv(GL_LIGHT2, GL_DIFFUSE, cor_luz_azul);
   glLightfv(GL_LIGHT2, GL_SPECULAR, cor_luz_azul);
   glLightfv(GL_LIGHT2, GL_POSITION, posicao_luz_azul);

   printf("\nMenu");
   printf("\n====\n\n");
   printf("  'a', 'b', 'c' para ligar/desligar as luzes.\n");
   printf("  'r', 't' para rotacionar o bule.\n");
   printf("  Setas direita e esquerda movem a luz verde.\n");
   printf("  Setas cima e baixo movem a luz vermelha.\n");
   printf("  'PageUp' e 'PageDown' movem a luz azul.\n");
}

void keyboard (unsigned char key, int x, int y)
{
   switch (tolower(key))
   {
      case 'r':
         anguloRotacao = (anguloRotacao + 1) % 360;
         break;
      case 't':
         anguloRotacao = (anguloRotacao - 1) % 360;
         break;
      case 'a':
         luzVerde = !luzVerde;
         break;
      case 'b':
         luzVermelha = !luzVermelha;
         break;
      case 'c':
         luzAzul = !luzAzul;
         break;
      case 27:    exit(0);
         break;
   }

   if (luzVerde) glEnable(GL_LIGHT0);
   else glDisable(GL_LIGHT0);

   if (luzVermelha) glEnable(GL_LIGHT1);
   else glDisable(GL_LIGHT1);

   if (luzAzul) glEnable(GL_LIGHT2);
   else glDisable(GL_LIGHT2);

   glutPostRedisplay();
}

void setMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular,
					  GLfloat *brilho, GLfloat *emissao )
{
   glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, brilho);
   glMaterialfv(GL_FRONT, GL_EMISSION, emissao);
}


void definirConstantesAtenuacao () {

   glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, kc);
   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, kl);
   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, kq);

   glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, kc);
   glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, kl);
   glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, kq);

   glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, kc);
   glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, kl);
   glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, kq);

}

void desenharLinhas () {
   setMaterial(bar_ambient, bar_difusa, bar_especular, bar_brilho, bar_emissao);
   glLineWidth(4); 
   
   glBegin(GL_LINES); 
      glVertex3f(10.0f, 7.0f, 3.5);
      glVertex3f(10.0f, -2.5f, 10.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f(-10.0f, 7.0f, 3.5);
      glVertex3f(-10.0f, -2.5f, 10.0);
   glEnd();

   glBegin(GL_LINES); 
      glVertex3f(-10.0f, 7.0f, 3.5);
      glVertex3f(10.0f, 7.0f, 3.5);
   glEnd();

   glBegin(GL_LINES); 
      glVertex3f(9.0f, 7.5f, -10.0);
      glVertex3f(10.0f, -2.5f, -10.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f(-9.0f, 7.5f, -10.0);
      glVertex3f(-10.0f, -2.5f, -10.0);
   glEnd();

   glBegin(GL_LINES); 
      glVertex3f(10.0f, 7.0f, 3.5);
      glVertex3f(10.0f, 7.0f, -13.0);
   glEnd();

   glBegin(GL_LINES);
      glVertex3f(-10.0f, 7.0f, 3.5);
      glVertex3f(-10.0f, 7.0f, -13.0);
   glEnd();
}

void desenharEsferas () {

   glPushMatrix();
      glTranslatef(posicao_luz_verde[0],posicao_luz_verde[1],posicao_luz_verde[2]);
      glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz_verde);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_luz_verde);
      glMaterialfv(GL_FRONT, GL_EMISSION, cor_emissao);
      glutSolidSphere(0.2,30,30);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(posicao_luz_vermelha[0],posicao_luz_vermelha[1],posicao_luz_vermelha[2]);
      glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz_vermelha);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_luz_vermelha);
      glMaterialfv(GL_FRONT, GL_EMISSION, cor_emissao);
      glutSolidSphere(0.2,30,30);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(posicao_luz_azul[0],posicao_luz_azul[1],posicao_luz_azul[2]);
      glLightfv(GL_LIGHT2, GL_POSITION, posicao_luz_azul);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_luz_azul);
      glMaterialfv(GL_FRONT, GL_EMISSION, cor_emissao);
      glutSolidSphere(0.2,30,30);
   glPopMatrix();

}


void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (0.0, 15.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   desenharEsferas();
   definirConstantesAtenuacao();

   glPushMatrix();
      setMaterial(object_ambient,object_difusa,object_especular,object_brilho,object_emissao);
      glRotatef(anguloRotacao, 0.0, 1.0, 0.0);
      glutSolidTeapot(5.0);
   glPopMatrix();

	setMaterial(base_ambient,base_difusa,base_especular,base_brilho,base_emissao);
   glBegin(GL_POLYGON);
      glNormal3f(0.0f, 1.0f, 0.0f);
      glVertex3f(-10.0f, -2.5f, -10.0);
      glVertex3f( 10.0f, -2.5f, -10.0);
      glVertex3f( 10.0f, -2.5f,  10.0);
      glVertex3f(-10.0f, -2.5f,  10.0);
   glEnd();

   desenharLinhas();

   glutSwapBuffers();
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

void special(int key, int x, int y)
{
   switch (key)
   {
      case GLUT_KEY_LEFT:
         posicao_luz_verde[0] = posicao_luz_verde[0] - 0.2 > -10.0 ? posicao_luz_verde[0] - 0.2 : posicao_luz_verde[0];
      break;
      case GLUT_KEY_RIGHT:
         posicao_luz_verde[0] = posicao_luz_verde[0] - 0.2 < 10.0 ? posicao_luz_verde[0] + 0.2 : posicao_luz_verde[0];
      break;
      case GLUT_KEY_UP:
         posicao_luz_vermelha[2] = posicao_luz_vermelha[2] + 0.2 < 3.5 ? posicao_luz_vermelha[2] + 0.2 : posicao_luz_vermelha[2];
      break;
      case GLUT_KEY_DOWN:
         posicao_luz_vermelha[2] = posicao_luz_vermelha[2] - 0.2 > -13.0 ? posicao_luz_vermelha[2] - 0.2 : posicao_luz_vermelha[2];
      break;
      case GLUT_KEY_PAGE_DOWN:
         posicao_luz_azul[2] = posicao_luz_azul[2] + 0.2 < 3.5 ? posicao_luz_azul[2] + 0.2 : posicao_luz_azul[2];;
      break;
      case GLUT_KEY_PAGE_UP:
         posicao_luz_azul[2] = posicao_luz_azul[2] - 0.2 > -13.0 ? posicao_luz_azul[2] - 0.2 : posicao_luz_azul[2];
      break;
   }
   glutPostRedisplay();
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Iluminacao - Exercicio 1");
   init ();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(special);
   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
