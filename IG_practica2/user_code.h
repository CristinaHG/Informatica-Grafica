//**************************************************************************
// Práctica 1
//**********************************************************************

#include <GL/gl.h>
#include "stdlib.h"
#include <stdio.h>
#include <math.h>

//#define PI (3.141592653589793)

//**************************************************************************
// estructuras de datos para los modelos
//**************************************************************************
using namespace std;

struct vertices
{
float coord[3];
};


struct caras
{
int ind_c[3];
};

struct solido{
int n_v;
int n_c;
vertices *ver;
caras    *car;
};


//**************************************************************************
// funciones para construir modelos sólidos poligonales
//**************************************************************************

void construir_cubo(float tam, solido *cubo);
void construir_piramide(float tam, float al, solido *piramide,int desplazamiento);

//**************************************************************************
// funciones de visualización
//**************************************************************************

void draw_puntos(vertices *ver, int n_v, int grosor); 
void draw_arista_solido(solido *malla, float r, float g, float b, int modo, int grosor);
void draw_solido_ajedrez(solido *malla, float r1, float g1, float b1, float r2, float g2, float b2);
void generaPorRevolucion(solido *malla, int rotaciones);
//void copiaVertices_ply(std::vector<float> v_ply,solido *ply);
//void copiaCaras_ply(std::vector<int> c_ply,solido *ply);

