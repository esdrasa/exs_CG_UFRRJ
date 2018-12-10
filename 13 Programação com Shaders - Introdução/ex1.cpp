#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "glcShader.h"

glcShader *shader = NULL;
GLuint vertexbuffer;
int shaderProgram;

GLint getUniLoc(GLuint program, const GLchar *name)
{
    GLint loc;

    loc = glGetUniformLocation(program, name);
    if (loc == -1) printf("No such uniform named \"%s\"\n", name);
    return loc;
}


void setTriangle()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
         -1.0f, -1.0f, 0.0f,
		 -1.0f, 1.0f, 1.0f,
          1.0,  -1.0f, 1.0f,
	};
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void drawTriangle()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  
        3,                  
        GL_FLOAT,          
        GL_FALSE,           
        0,                  
        (void*)0            
    );

    glDrawArrays(GL_TRIANGLES, 0, 3); 

    glDisableVertexAttribArray(0);
}

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glewInit();
    if (glewIsSupported("GL_VERSION_2_0"))
        printf("Ready for OpenGL 2.0\n");
    else
    {
        printf("OpenGL 2.0 not supported\n");
        exit(1);
    }

    shader = new glcShader("../shaders/simple.vert", "../shaders/simple.frag");
    shaderProgram = shader->GetProgram();

    setTriangle();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);

    glUniform3f(getUniLoc(shaderProgram, "userColor"), 0.4,0.4,0.8);

    if(shader) shader->Use();

    drawTriangle();

    glutSwapBuffers ();
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

void idle(void)
{
    glutPostRedisplay();
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutCreateWindow ("Programação com Shaders - Exercicio 1");
    init ();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
