void initLight(int width, int height)
{
   glEnable(GL_LIGHTING);                 
   glEnable(GL_LIGHT0);                  

   GLfloat cor_luz[]     = { 1.0, 1.0, 1.0, 1.0};
   GLfloat posicao_luz[] = { (float) width, (float)height, 1000.0, 1.0};

   glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
   glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
}

void setMaterial(void)
{
   GLfloat objeto_ambient[]   = { .1745, .01175, .01175, 1.0 };
   GLfloat objeto_difusa[]    = { .61424, .04136, .04136, 1.0 };
   GLfloat objeto_especular[] = { .727811, .626959, .626959, 1.0 };
   GLfloat objeto_brilho[]    = { 90.0f };

   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}