#include "freeglut.h"
//#include "glut.h"
#include <stdio.h>
#include <math.h>

// Inicijalizacija funkcije
void drawRect(GLfloat, GLfloat, int, int, float, float, float);
void update();

// Dimenzije prozora
const int Width = 1000;
const int Height = 500;

// Dimenzije bloka
#define paddleHeight 10
#define paddleWidth 80

float p1 = 500; // Pocetna pozicija bloka po x-osi

const float pspeed = 10; // Brzina pomeranja bloka

int score[1];

#define bsize 10 // Velicina lopte
GLdouble bpos[2] = {235,235}; // Pocetna pozicija lopte
GLfloat bvx = 1; // Vektor kretanja lopte (levo-desno)
GLfloat bvy = 1; // Vektor kretanja lopte (gore-dole)
float bspeed = 0.5; // Brzina lopte

// Tekstualna promenljiva
static char str[100];
void * font = GLUT_BITMAP_9_BY_15;

void renderScene(void)
{    
     update();
     glClear(GL_COLOR_BUFFER_BIT);
    
	 sprintf(str, "Broj poena: %d", score[0]);
     glRasterPos2f(10, 10);
     glutBitmapString(font,(unsigned char*)str);

     // Crtanje bloka i lopte
     drawRect(p1, 0.0, paddleHeight, paddleWidth, 0, 0, 1); // Plavi blok
	
	 drawRect(bpos[0], bpos[1], bsize, bsize, 1, 1, 0); // Zuta lopta
	
     glutSwapBuffers(); // Crtanje novog frejma
}

void update()
{
     // Ponasanje lopte kada je u interakciji sa prozorom
     if(bpos[1] > 500-bsize)
		  bvy = -1;
	 
	 else if (bpos[1] < 0)
	 {
		 bvy = -1;
		 score[0] = 0;
		 
	 } 
     if(bpos[0] > 1000-bsize)
          bvx = -1;
		 
	 else if (bpos[0] < 0)
          bvx = 1;
	     
     // Ponasanje lopte kada je u interakciji sa blokom
     if(bpos[1] <= paddleHeight && bpos[0] >= p1 && bpos[0] + bsize <= p1 + paddleWidth)
     {		  
          bvy *= -1;
		  score[0]++;
		  bspeed *= 1.01;
     }
     
     // Nova pozicija lopte zavisno od brzine
     bpos[0] += bspeed * bvx;
     bpos[1] += bspeed * bvy;
}

// Crtanje novog bloka pri pomeranju
void drawRect(GLfloat x, GLfloat y, int height, int width, float R, float G, float B)
{
     glColor3f(R,G,B);
     
     glBegin(GL_QUADS);
          glVertex2f( x, y);						// Gore levo
		  glVertex2f( x, height + y);				// Dole levo
          glVertex2f( x + width, y + height);		// Dole desno
          glVertex2f( x + width, y);				// Gore desno
	 glEnd();
}

// Tasteri za upravljanje blokom
void specialKeyPress(int key, int x, int y)
{
     switch (key) 
     {
            case GLUT_KEY_RIGHT:
                 if(920>=p1+pspeed)
                      {p1 += pspeed;}
                 break;
            case GLUT_KEY_LEFT:
                 if(0<=p1-pspeed)
                      {p1 -= pspeed;}
                 break;
     }
}

void EscPress(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case '\033': // oktalni kod tastature za taster Esc
		exit(0);
	 break;
	}
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); 
    gluOrtho2D(0,1000,0,500);      
    
// Pocetno stanje poena 
    score[0] = 0;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Ping Pong");
    glutDisplayFunc(renderScene);    
    glutSpecialFunc(specialKeyPress);
	glutKeyboardFunc(EscPress);
    glutIdleFunc(renderScene);
    init();
    glutMainLoop();
    return 0;
}