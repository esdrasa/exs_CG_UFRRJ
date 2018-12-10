#include <GL/glut.h>
#include <GL/glext.h>
#include <iostream>
#include <math.h>
#include "glcTexture.h"
using namespace std;

GLUquadric* qobj;

// Aqui é criada a referência ao objeto que gerenciará as texturas
glcTexture *textureManager;
int selected = 0;
int object = 1;
float width, height;
float zoom = 1.8f;
float pan[2]  = {0.0f, 0.0f};
bool fullScreen = false;
float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;
int window;

bool wrappingMode = 1;
bool magMode = 1;
bool minMode = 1;
int colorMode = 0;
float tiles = 1.0;

// Como as imagens são lidas a partir do canto superior direito, temos que inverter as coordenadas 'u' e 'v'
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, width/height, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(pan[0], pan[1], zoom, pan[0], pan[1], 0.0, 0.0, 1.0, 0.0);
    // Seleciona a textura corrente
    textureManager->Bind(selected);
    float aspectRatio = textureManager->GetAspectRatio(selected);

    // Calculo abaixo funciona apenas se textura estiver centralizada na origem
    float h = 1.0f;
    float w = 1.0f;

    if( aspectRatio > 1.0f) h  = h/aspectRatio;
    else                    w  = w*aspectRatio;

    glPushMatrix();
    glRotatef( rotationY, 0.0, 1.0, 0.0 );
    glRotatef( rotationX, 1.0, 0.0, 0.0 );

    if(object == 1)
    {
        const double PI = 3.14159;
        double i, resolution  = 0.1;
        double height = 1;
        double radius = 0.5;

        glPushMatrix();
        glTranslatef(0, -0.5, 0);

        textureManager->Bind(1);

        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f( 0.5, 0.5 );
            glVertex3f(0, height, 0);  /* center */
            for (i = 2 * PI; i >= 0; i -= resolution)

            {
                glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
                glVertex3f(radius * cos(i), height, radius * sin(i));
            }
            /* close the loop back to 0 degrees */
            glTexCoord2f( 0.5, 0.5 );
            glVertex3f(radius, height, 0);
        glEnd();

        /* bottom triangle: note: for is in reverse order */
        textureManager->Bind(1);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f( 0.5, 0.5 );
            glVertex3f(0, 0, 0);  /* center */
            for (i = 0; i <= 2 * PI; i += resolution)
            {
                glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
                glVertex3f(radius * cos(i), 0, radius * sin(i));
            }
        glEnd();

        textureManager->Bind(0);

        /* middle tube */
        glBegin(GL_QUAD_STRIP);
            for (i = 0; i <= 2 * PI; i += resolution)
            {
                const float tc = ( i / (float)( 2 * PI ) );
                glTexCoord2f( tc, 0.0 );
                glVertex3f(radius * cos(i), 0, radius * sin(i));
                glTexCoord2f( tc, 1.0 );
                glVertex3f(radius * cos(i), height, radius * sin(i));
            }
            /* close the loop back to zero degrees */
            glTexCoord2f( 0.0, 0.0 );
            glVertex3f(radius, 0, 0);
            glTexCoord2f( 0.0, 1.0 );
            glVertex3f(radius, height, 0);
        glEnd();

        glPopMatrix();
    }
    glPopMatrix();

    glutSwapBuffers();

    // Desabilita o uso de texturas
    textureManager->Disable();
}

void resizeWindow(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
}

void changeWindowTitle(char* name)
{
    glutSetWindow(window); // Set main window as current
    glutSetWindowTitle(name); // change title
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case '+':
        if(zoom>=0.3)  zoom-=0.1f;
        break;
    case '-':
        if(zoom<=20.0) zoom+=0.1f;
        break;
    case 't': // Increase Texture Tiles
        tiles++;
        break;
    case 'T': // Decrease Texture Tiles
        if(tiles>1.0f) tiles--;
        break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
    float f = 0.05;
    switch(key)
    {
    case GLUT_KEY_UP:
        pan[1]+=f;
        break;
    case GLUT_KEY_DOWN:
        pan[1]-=f;
        break;
    case GLUT_KEY_LEFT:
        pan[0]-=f;
        break;
    case GLUT_KEY_RIGHT:
        pan[0]+=f;
        break;
    case GLUT_KEY_F11:
        (!fullScreen) ? glutFullScreen() : glutReshapeWindow(800, 600);
        fullScreen = !fullScreen;
        break;
    }
    glutPostRedisplay();
}


void init(void)
{
    glClearColor (0.5, 0.5, 0.5, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
    glEnable(GL_LIGHTING);                 // Habilita luz
    glEnable(GL_LIGHT0);                   // habilita luz 0

    glEnable(GL_ALPHA_TEST);      // O alpha test descarta fragmentos dependendo de uma comparação (abaixo)
    glAlphaFunc(GL_GREATER, 0.1); // Info: https://www.opengl.org/sdk/docs/man2/xhtml/glAlphaFunc.xml

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // https://www.opengl.org/sdk/docs/man/html/glBlendFunc.xhtml

    // Cor da fonte de luz (RGBA)
    GLfloat cor_luz[]     = { 1.0, 1.0, 1.0, 1.0};
    GLfloat posicao_luz[] = { 0.0, 0.0, 10.0, 1.0};

    // Define parametros da luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
    glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);


    // Essa é a principal parte deste exemplo
    textureManager = new glcTexture();            // Criação do arquivo que irá gerenciar as texturas
    textureManager->SetNumberOfTextures(1);       // Estabelece o número de texturas que será utilizado
    textureManager->CreateTexture("../data/wood.png", 0);
    textureManager->CreateTexture("../data/woodtop.png", 1);

    qobj = gluNewQuadric();
}

// Motion callback//glcTexture *texture;
void motion(int x, int y )
{
    rotationX += (float) (y - last_y);
    rotationY += (float) (x - last_x);

    last_x = x;
    last_y = y;
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        last_x = x;
        last_y = y;
    }
    if(button == 3) // Scroll up
    {
        if(zoom>=0.3)  zoom-=0.04f;
    }
    if(button==4)   // Scroll down
    {
        if(zoom<=20.0) zoom+=0.04f;
    }
}

void idle ()
{
    glutPostRedisplay();
}


void printOpenGLVersion()
{
    cout << "\nDados do OpenGL instalado neste sistema operacional:" << endl;
    char *vendor  = (char * ) glGetString(GL_VENDOR);
    char *version = (char * ) glGetString(GL_VERSION);
    char *render  = (char * ) glGetString(GL_RENDERER);
    cout << "   Vendor:   " << vendor   << endl;
    cout << "   Version:  " << version  << endl;
    cout << "   Renderer: " << render   << endl;
    if(version[0] == '1')
    {
        cout << "\nAviso: A biblioteca pode nao funcionar corretamente (versao antiga do OpenGL).";
        cout << "\n       Maiores detalhes nas notas do arquivo \"README_FIRST.txt\".\n";
    }
    cout << endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow(argv[0]);

    init();
    printOpenGLVersion();
    cout << "\n------------------------------------------------------------\n" << endl;
    cout << "Instrucoes: " << endl;
    cout << " * Teclas '+' e '-' fazem zoom;" << endl;
    cout << " * Teclas 't' ou 'T' para aumentar/diminuir o tamanho da coordenada de textura (em 2D);" << endl;
    cout << " * Direcionais do teclado movem a camera (pan);" << endl;
    cout << " * Mouse rotaciona o objeto;" << endl;
    cout << " * Pressione F11 para ligar e desligar modo FullScreen;" << endl;

    glutDisplayFunc(display);
    glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc( specialKeys );
    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
