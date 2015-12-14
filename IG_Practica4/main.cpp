/* 
 * File:   main.cpp
 * Author: cris
 *
 * Created on 30 November 2015, 20:51
 */

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include "SOIL.h"
//#include <GL/glew.h>
//#include <GL/glew.h>

using namespace std;


// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//GL_GLEXT_PROTOTYPES=0;
//GLuint texturaTierra= SOIL_load_OGL_texture("IG_Practica4/Earth.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

//glEnable(GL_TEXTURE_2D);
//glBindTexture(GL_TEXTURE_2D,texturaTierra);
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
//    glBindTexture( GL_TEXTURE_2D, 0 );




//piezas móviles
enum {
  TIERRA,
  QUIT
};

//variables de tamaño
#define CABEZA 3.0
#define TORSO 3.0
#define BRAZO 2.0
#define MANO 1.0
#define PIERNA 2.0
#define PELVIS_SIZE 1.0


//GLUquadricObj *t, *h, *brazoIzq, *manoIzq, *brazoDer, *manoDer,*piernaIzq, *piernaDer, *pelvis;

//angulo inicial
static GLfloat theta[QUIT] = {0 };

//GLuint g_SphereDisplayList = glGenLists(1);
//GLUquadric* pSphereQuadric;
GLUquadricObj *tierra;
//
//pSphereQuadric=gluNewQuadric();
//gluQuadricDrawStyle( pSphereQuadric, GLU_FILL );



//**************************************************************************
// Funcion que dibuja circulos
//***************************************************************************

void Circle (GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo){
int i;
	if (modo==GL_LINE) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (modo==GL_FILL) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else 
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
glBegin( GL_POLYGON );
for (i=0;i<n;i++) 
	glVertex3f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n),0.01);
glEnd();
}
//**************************************************************************
// Funcion que dibuja poligonos
//***************************************************************************

void Poligono_Solido(float v[][3], int n){
int i;
	glPolygonMode(GL_FRONT, GL_FILL);
		glBegin(GL_POLYGON);
			for(i=0;i<n;i++)  
				glVertex3f(v[i][0],v[i][1],v[i][2]);
	glEnd();
}




GLuint LoadTexture( const char* texture )
{
    glEnable( GL_TEXTURE_2D );
    GLuint textureID = SOIL_load_OGL_texture( texture, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS );
    glBindTexture( GL_TEXTURE_2D, textureID );
 //   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
 //   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  //  glBindTexture( GL_TEXTURE_2D, 0 );
 
    return textureID;
}



void drawEarth(){
    GLuint texturaTierra=LoadTexture("tc-earth_daymap.jpg");
    cout<<"textura vale"<<texturaTierra;
    glBindTexture( GL_TEXTURE_2D, texturaTierra );
    //gluQuadricOrientation( pSphereQuadric, GLU_OUTSIDE );
    gluQuadricTexture( tierra, GL_TRUE );
    gluQuadricNormals( tierra, GLU_SMOOTH ); 
    glColor3f(1,1,1);
    glRotatef( 200.0f, 90.0f, 200.0f, 200.0f );
    gluSphere( tierra, 1.0, 360, 180 );

}





void RenderScene()
{
    glEnable( GL_NORMALIZE );
   

    


//glNewList( g_SphereDisplayList, GL_COMPILE );
//{

  // glutSolidSphere(2,360,180);
//}
//glEndList();
//gluDeleteQuadric( pSphereQuadric );
    
    
    
//  glMatrixMode( GL_MODELVIEW );   
//    glLoadIdentity();                                                      
 
   // glTranslatef( 0.0f, 0.0f, -80.0f );
     glPushMatrix();
 
    glRotatef(10, 0.0f, 0.0f, -1.0f ); // Rotate the earth around it's axis
   // glScalef( 12.756f, 12.756f, 12.756f );  // The earth's diameter is about 12,756 Km
    drawEarth();
 //   glEnable( GL_TEXTURE_2D );
   // glBindTexture( GL_TEXTURE_2D, textureID );
    //g_EarthMaterial.Apply();
glPopMatrix();
    
}
//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}



void draw_objects()
{

   //DrawRobot(0,0,0, theta[BRAZOIZQ], theta[MANOIZQ], theta[BRAZODER],theta[MANODER], theta[PIERNAIZQ], theta[PIERNADER],theta[PELVIS],theta[TIERRA],textureID);
    RenderScene();
}
//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


void normal_keys(unsigned char Tecla1,int x,int y){

//if (toupper(Tecla1)=='Q') exit(0);
    
  switch (Tecla1) {
//    case 'q':
//      theta[BRAZOIZQ] += 5;
//      break;
//    case 'w':
//      theta[BRAZOIZQ] -= 5;
//      break;
//    case 'e':
//      theta[MANOIZQ] += 5;
//      break;
//    case 'r':
//      theta[MANOIZQ] -= 5;
//      break;
//    case 'a':
//      theta[BRAZODER] += 5;
//      break;
//    case 's':
//      theta[BRAZODER] -= 5;
//      break;
//    case 'd':
//      theta[MANODER] += 5;
//      break;
//    case 'f':
//      theta[MANODER] -= 5;
//      break;
//    case 't':
//      theta[PIERNAIZQ] += 5;
//      break;
//    case 'y':
//      theta[PIERNAIZQ] -= 5;
//      break;
//    case 'k':
//          theta[PELVIS] += 5;
//      break;
//    case 'l':
//        theta[PELVIS] -=5;
//      break;
//          
//    case 'g':
//      theta[PIERNADER] += 5;
//      break;
//    case 'h':
//      theta[PIERNADER] -= 5;
//      break;
    case 'p':
      exit(0);
  }
  glutPostRedisplay();
}

//***************************************************************************
// Funcion manoIzqmada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}

//**********************************************/
// función que inicializa las cuádricas       
//                                            
//tomada de Alejandro Alcalde y modificada    
//**********************************************/
void InitQuadrics() {
  tierra=gluNewQuadric();
  gluQuadricDrawStyle(tierra,GLU_FILL);
//  t = gluNewQuadric();
//  gluQuadricDrawStyle(t, GLU_FILL);
//  brazoIzq = gluNewQuadric();
//  gluQuadricDrawStyle(brazoIzq, GLU_FILL);
//  h = gluNewQuadric();
//  gluQuadricDrawStyle(h, GLU_FILL);
//  manoIzq = gluNewQuadric();
//  gluQuadricDrawStyle(manoIzq, GLU_FILL);
//  brazoDer = gluNewQuadric();
//  gluQuadricDrawStyle(brazoDer, GLU_FILL);
//  piernaIzq = gluNewQuadric();
//  gluQuadricDrawStyle(piernaIzq, GLU_FILL);
//  piernaDer = gluNewQuadric();
//  gluQuadricDrawStyle(piernaDer, GLU_FILL);
//  pelvis=gluNewQuadric();
//  gluQuadricDrawStyle(pelvis, GLU_FILL);  
}
//***************************************************************************
// Funcion de incializacion
// por Domingo Martín Perandrés
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
    
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();

 /* allocate quadrics with filled drawing style */
  InitQuadrics();
glViewport(0,0,UI_window_width,UI_window_height);
}




//***************************************************************************
// Programa principal - por Domingo Martín Perandrés
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Practica 4");



// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

glEnable( GL_NORMALIZE );
// inicio del bucle de eventos
glutMainLoop();
return 0;
}