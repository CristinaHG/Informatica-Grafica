/* 
 * File:   main.cpp
 * Author: cris
 *
 * Created on 30 November 2015, 20:51
 */

//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <math.h>


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

///* Variables to control the spped of rotation/translation/zoom */
//#define DEGREES_PER_PIXEL	0.6f
//#define UNITS_PER_PIXEL		0.1f
//#define ZOOM_FACTOR		0.04f

/* Enumeration of body parts */
enum {
  TORSO,
  LUA,
  LLA,
  RUA,
  RLA,
  LUL,
  PEL,
  //LLL,
  RUL,
 // RLL,
  QUIT
};

/* Variables to control the size of the robot */
#define HEAD_HEIGHT 3.0
//#define HEAD_RADIUS 1.0

#define TORSO_HEIGHT 3.0
//#define TORSO_RADIUS 1.5

#define UPPER_ARM_HEIGHT 2.0
#define LOWER_ARM_HEIGHT 1.0
//#define UPPER_ARM_RADIUS  0.5
//#define LOWER_ARM_RADIUS  0.5 
#define UPPER_LEG_HEIGHT 2.0
#define PELVIS 1.0
//#define LOWER_LEG_HEIGHT 2.0
//#define UPPER_LEG_RADIUS  0.5
//#define LOWER_LEG_RADIUS  0.5

/* Scene rotation angles to alter interactively */
float xRotate = 0, yRotate = 0;

/* Camera position and orientation -- used by gluLookAt */
GLfloat eye[] = { 0, 0, 20 };
GLfloat at[] = { 0, 0, 0 };

GLUquadricObj *t, *h, /* torso and head */
*lua, *lla, *rua, *rla, /* arms */
*lul, *lll, *rul, *rll, *pelvis;

/* initial joint angles */
static GLfloat theta[QUIT] = { 0, 0, 0, 0, 0,0, 0.0, 0.0 };
/* torso position */
static GLfloat center[3] = { 0, 0, 0 };
/* joint angle to alter interactively */
//static GLint angle = 0; /* initially, TORSO */


//**************************************************************************
// Funcion que dibuja los objetos
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

void Poligono_Solido(float v[][3], int n){
int i;
	glPolygonMode(GL_FRONT, GL_FILL);
		glBegin(GL_POLYGON);
			for(i=0;i<n;i++)  
				glVertex3f(v[i][0],v[i][1],v[i][2]);
	glEnd();
}


void head() {
  glPushMatrix();

  glScalef(HEAD_HEIGHT/2, HEAD_HEIGHT/3,HEAD_HEIGHT/2);
  //gluSphere(h, 1.0, 10, 10);
  glutSolidCube(HEAD_HEIGHT);
  glPopMatrix();
}
void right_eye(){
    glPushMatrix();
glutSolidSphere(0.34,10,10);
    glColor3f(1,1,1);
     glPopMatrix();

}
void letf_eye(){
    glPushMatrix();
glutSolidSphere(0.21,10,10);
    glColor3f(1,1,1);
     glPopMatrix();
}
void nose(){
    glPushMatrix();
//    glColor3f(1.0,0.0,0.0);
    glScalef(0.25,0.25,1);
    float nariz[3][3]={{-1,0,3},{1,0,3},{0,1,3}};
    glBegin(GL_TRIANGLES);   
    Poligono_Solido(nariz,3);
    glEnd();
    glPopMatrix();
}
void torso() {
  glPushMatrix();
  glTranslatef(0, -1.5, 0);
  glutSolidCube(TORSO_HEIGHT);
  glPopMatrix();
}

void left_upper_arm() {
  glPushMatrix();
//  glRotatef(90, 0, 1, 0);
  glScalef(3,0.5,0.5);
//  gluCylinder(lua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10,
//              10);
  glutSolidCube(UPPER_ARM_HEIGHT);
  glPopMatrix();
}

void left_lower_arm() {
  glPushMatrix();
//  glRotatef(-90, 0, 1, 0);
//  glScalef(1,1,1);
//  gluCylinder(lla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10,
//              10);
  glutSolidCube(LOWER_ARM_HEIGHT);
  glPopMatrix();
}

void right_upper_arm() {
  glPushMatrix();
//  glRotatef(-90, 0, 1, 0);
  glScalef(3,0.5,0.5);
  
//  gluCylinder(rua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10,
//              10);
  glutSolidCube(UPPER_ARM_HEIGHT); 
  glPopMatrix();
}

void right_lower_arm() {
  glPushMatrix();
 // glRotatef(-90, 0, 1, 0);
 // glScalef(1,1,1);
//  gluCylinder(lla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10,
//              10);
  glutSolidCube(LOWER_ARM_HEIGHT);
  glPopMatrix();
}

void left_upper_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glScalef(0.6,0.5,1.5);
//  gluCylinder(lul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10,
 //             10);
  glutSolidCube(UPPER_LEG_HEIGHT);
  glPopMatrix();
}

void right_upper_leg() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glScalef(0.6,0.5,1.5);
  //gluCylinder(rul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 20,
   //           20);
  glutSolidCube(UPPER_LEG_HEIGHT);
  glPopMatrix();
}

void build_pelvis() {
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glScalef(3.3,0.5,1.5);
  glutSolidCube(PELVIS);
  glPopMatrix();
}



void DrawRobot(float x, float y, float z, float lua, float lla, float rua,
               float rla, float lul, float rul,float pelvis) {
    glColor3f(0.87,0.68,0.32);
  torso();
  glPushMatrix();
    glTranslatef(0, HEAD_HEIGHT / 2, 0);
    head();
    glTranslatef(1,0,2);
    glColor3f(0,0,0);
    right_eye();
    glTranslatef(-1.7,-0.1,2);
    glColor3f(0,0,0);
    letf_eye();
    glTranslatef(0.68,-1,2);
    glColor3f(0,0,0);
    nose();
    glColor3f(0.87,0.68,0.32);
    //glColor3f(0.87,0.68,0.32);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(TORSO_HEIGHT/2, 0, 0);
    glRotatef(lua, 0, 0, 1);
    left_upper_arm();
    glTranslatef(UPPER_ARM_HEIGHT+1.5, 0, 0);
    glRotatef(lla, 0, 0, 1);
    left_lower_arm();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-TORSO_HEIGHT/2, 0, 0);
    glRotatef(rua, 0, 0, 1);
    right_upper_arm();
    glTranslatef(-UPPER_ARM_HEIGHT-1.5, 0, 0);
    glRotatef(rla, 0, 0, 1);
    right_lower_arm();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0, -TORSO_HEIGHT-PELVIS, 0);
    glRotatef(pelvis, 0, 0, 1);
    build_pelvis();

     glPushMatrix();
  glTranslatef(TORSO_HEIGHT/3, -TORSO_HEIGHT+PELVIS*2, 0);
    glRotatef(lul, 1, 0, 0);
    left_upper_leg();
    glPopMatrix();
 
     glPushMatrix();
    glTranslatef(-TORSO_HEIGHT/3,-TORSO_HEIGHT+PELVIS*2, 0);
    glRotatef(rul, 1, 0, 0);
    right_upper_leg();
    glPopMatrix();

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

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
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
   DrawRobot(center[0], center[1], center[2], theta[LUA], theta[LLA], theta[RUA],
            theta[RLA], theta[LUL], theta[RUL],theta[PEL]);
    
//    DrawRobot(center[0], center[1], center[2], theta[LUA], theta[LLA], theta[RUA],
//            theta[RLA], theta[LUL], theta[LLL], theta[RUL], theta[RLL]);

//
//glColor3f(0.0,0.0,0.0); // copa
//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//glBegin(GL_POLYGON);
//	glVertex3f(1,7,0);
//	glVertex3f(1,5,0);
//	glVertex3f(-1,5,0);
//	glVertex3f(-1,7,0);
//glEnd();
//
//
//glBegin(GL_POLYGON); // ala
//	glVertex3f(1.5,5,0);
//	glVertex3f(1.5,4,0);
//	glVertex3f(-1.5,4,0);
//	glVertex3f(-1.5,5,0);
//	
//	
//glEnd();
//
//glColor3f(1.0,0.8,0.6); // cara
//glBegin(GL_POLYGON);
//	glVertex3f(1,4,0);
//	glVertex3f(1,0,0);
//	glVertex3f(-1,0,0);
//	glVertex3f(-1,4,0);	
//glEnd();
//
//glColor3f(0.0,0.0,0.0);    // borde de cara
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//glLineWidth(2);
//glBegin(GL_POLYGON);
//	glVertex3f(1,4,0);
//	glVertex3f(1,0,0);
//	glVertex3f(-1,0,0);
//	glVertex3f(-1,4,0);	
//glEnd();
//
//glColor3f(1.0,0.8,0.6); // oreja izq
//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//glBegin(GL_POLYGON);
//	glVertex3f(-1,3,0);
//	glVertex3f(-1,2,0);
//	glVertex3f(-1.5,2,0);
//	glVertex3f(-1.5,3,0);
//glEnd();
//
//glColor3f(1.0,0.8,0.6); // oreja der
//glBegin(GL_POLYGON);
//	glVertex3f(1.5,3,0);
//	glVertex3f(1.5,2,0);
//	glVertex3f(1,2,0);
//	glVertex3f(1,3,0);
//glEnd();
//
//glColor3f(0.0,0.0,0.0);    // borde oreja izq
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//glLineWidth(2);
//glBegin(GL_POLYGON);
//	glVertex3f(-1,3,0);
//	glVertex3f(-1,2,0);
//	glVertex3f(-1.5,2,0);
//	glVertex3f(-1.5,3,0);
//glEnd();
//
//
//glColor3f(0.0,0.0,0.0);    // borde oreja der
////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//glLineWidth(2);
//glBegin(GL_POLYGON);
//	glVertex3f(1,3,0);
//	glVertex3f(1,2,0);
//	glVertex3f(1.5,2,0);
//	glVertex3f(1.5,3,0);
//glEnd();
//
//
//glColor3f(0,0.0,1.0);
//Circle(0.3,0.4,2.8,10,GL_FILL);
//
////glColor3f(0,0.0,1.0);
//Circle(0.3,-0.4,2.8,10,GL_FILL);
//
//glColor3f(1.0,0.0,0.0);
//float nariz[3][3]={{0.28,1.5,0},{-0.28,1.5,0.01},{0.0,2,0.01}};
//Poligono_Solido(nariz,3);
//
//
//glColor3f(1.0,0.5,0.0);
//Circle(0.15,-0.39,1,10,GL_FILL);
//Circle(0.15,0.39,1,10,GL_FILL);
//
//float boca[4][3]={{0.39,1.2,0.1},{0.39,0.8,0.01},{-0.39,0.8,0.01},{-0.39,1.2,0.01}};
//Poligono_Solido(boca,4);


//Circle (GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo)




}
//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
//change_observer();
//draw_axis();

 /* (Re)position the camera */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], 0, 1, 0);

  /* Rotate the scene in the x and y directions */
  glRotatef(xRotate, 0, 1, 0);
  glRotatef(yRotate, 1, 0, 0);

  draw_objects();
  
  /* Before returning, flush the graphics buffer
   * so all graphics appear in the window */
  glFlush();
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


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y){

//if (toupper(Tecla1)=='Q') exit(0);
  switch (Tecla1) {
    case 'q':
      theta[LUA] += 5;
      break;
    case 'w':
      theta[LUA] -= 5;
      break;
    case 'e':
      theta[LLA] += 5;
      break;
    case 'r':
      theta[LLA] -= 5;
      break;
    case 'a':
      theta[RUA] += 5;
      break;
    case 's':
      theta[RUA] -= 5;
      break;
    case 'd':
      theta[RLA] += 5;
      break;
    case 'f':
      theta[RLA] -= 5;
      break;
    case 't':
      theta[LUL] += 5;
      break;
    case 'y':
      theta[LUL] -= 5;
      break;
    case 'k':
          theta[PEL] += 5;
      break;
    case 'l':
        theta[PEL] -=5;
      break;
          
//    case 'u':
//      theta[LLL] += 5;
//      break;
//    case 'i':
//      theta[LLL] -= 5;
//      break;
    case 'g':
      theta[RUL] += 5;
      break;
    case 'h':
      theta[RUL] -= 5;
      break;
//    case 'j':
//      theta[RLL] += 5;
//      break;
//    case 'k':
//      theta[RLL] -= 5;
//      break;
//    case 'b':
//      dance = !dance;
//      genDirec();
//      break;
    case 'p':
      exit(0);
  }
  glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
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



//***************************************************************************
// Funcion de incializacion
//***************************************************************************
/* Allocate quadrics with filled drawing style */
void InitQuadrics() {
  t = gluNewQuadric();
  gluQuadricDrawStyle(t, GLU_FILL);
  lua = gluNewQuadric();
  gluQuadricDrawStyle(lua, GLU_FILL);
  h = gluNewQuadric();
  gluQuadricDrawStyle(h, GLU_FILL);
  lla = gluNewQuadric();
  gluQuadricDrawStyle(lla, GLU_FILL);
  rua = gluNewQuadric();
  gluQuadricDrawStyle(rua, GLU_FILL);
  lul = gluNewQuadric();
  gluQuadricDrawStyle(lul, GLU_FILL);
  lll = gluNewQuadric();
  gluQuadricDrawStyle(lll, GLU_FILL);
  rul = gluNewQuadric();
  gluQuadricDrawStyle(rul, GLU_FILL);
  rll = gluNewQuadric();
  gluQuadricDrawStyle(rll, GLU_FILL);
  pelvis=gluNewQuadric();
  gluQuadricDrawStyle(pelvis, GLU_FILL);  
}

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
//Window_width=5;
//Window_height=5;
//Front_plane=10;
//Back_plane=1000;

// se inicia la posicion del observador, en el eje z
//Observer_distance=2*Front_plane;
//Observer_angle_x=0;
//Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
    
glClearColor(1,1,1,1);

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/* Set up perspective projection */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, 1.0f, 10.0f, -10.0f);

  /* Initialize the camera position */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], 0, 1, 0);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
//change_projection();


 /* allocate quadrics with filled drawing style */
  InitQuadrics();
//glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
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
glutCreateWindow("Practica 3");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
//glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}