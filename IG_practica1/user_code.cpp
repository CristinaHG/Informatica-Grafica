#include "user_code.h"


void construir_piramide(float tam, float al, solido *piramide){
//funciones de visualización
    piramide->n_v=5;
    piramide->n_c=6;
    piramide->ver=(vertices *)malloc(5*sizeof(vertices));
    piramide->car=(caras *)malloc(6*sizeof(caras));

    //asignar puntos y caras
    //puntos
    piramide->ver[0].coord[0]=-tam;piramide->ver[0].coord[1]=0; piramide->ver[0].coord[2]=tam;
    piramide->ver[1].coord[0]=tam;piramide->ver[1].coord[1]=0;piramide->ver[1].coord[2]=tam;
    piramide->ver[2].coord[0]=tam;piramide->ver[2].coord[1]=0;piramide->ver[2].coord[2]=-tam;
    piramide->ver[3].coord[0]=-tam;piramide->ver[3].coord[1]=0;piramide->ver[3].coord[2]=-tam;
    piramide->ver[4].coord[0]=0;piramide->ver[4].coord[1]=al;piramide->ver[4].coord[2]=0;
    //caras
    piramide->car[0].ind_c[0]=0;piramide->car[0].ind_c[1]=1;piramide->car[0].ind_c[2]=4;
    piramide->car[1].ind_c[0]=1;piramide->car[1].ind_c[1]=2;piramide->car[1].ind_c[2]=4;
    piramide->car[2].ind_c[0]=2;piramide->car[2].ind_c[1]=3;piramide->car[2].ind_c[2]=4;
    piramide->car[3].ind_c[0]=3;piramide->car[3].ind_c[1]=0;piramide->car[3].ind_c[2]=4;
    piramide->car[4].ind_c[0]=3;piramide->car[4].ind_c[1]=0;piramide->car[4].ind_c[2]=1;
    piramide->car[5].ind_c[0]=1;piramide->car[5].ind_c[1]=2;piramide->car[5].ind_c[2]=3;
}
/*
void construir_cubo(float tam, solido *cubo){
    cubo->n_v=8;
    cubo->n_c=12;
    cubo->ver(vertices *)malloc(8*sizeof(vertices));
    cubo->car(caras *)malloc(12*sizeof(caras));

    //puntos
    cubo[0]->ver->coord[0]=-tam;cubo[0]->ver->coord[1]=0;cubo[0]->ver->coord[2]=tam;
    cubo[1]->ver->coord[0]=tam;cubo[1]->ver->coord[1]=0;cubo[1]->ver->coord[2]=tam;
    cubo[2]->ver->coord[0]=tam;cubo[2]->ver->coord[1]=tam;cubo[2]->ver->coord[2]=tam;
    cubo[3]->ver->coord[0]=-tam;cubo[3]->ver->coord[1]=tam;cubo[3]->ver->coord[2]=tam;
    cubo[4]->ver->coord[0]=-tam;cubo[4]->ver->coord[1]=0;cubo[4]->ver->coord[2]=-tam;
    cubo[5]->ver->coord[0]=tam;cubo[5]->ver->coord[1]=0;cubo[5]->ver->coord[2]=-tam;
    cubo[6]->ver->coord[0]=tam;cubo[6]->ver->coord[1]=tam;cubo[6]->ver->coord[2]=-tam;
    cubo[7]->ver->coord[0]=-tam;cubo[7]->ver->coord[1]=tam;cubo[7]->ver->coord[2]=-tam;
    
    //caras
    cubo->car[0].ind_c[0]=3;cubo->car[0].ind_c[1]=0;cubo->car[0].ind_c[2]=1;
    cubo->car[1].ind_c[0]=2;cubo->car[1].ind_c[1]=3;cubo->car[1].ind_c[2]=1;
    cubo->car[2].ind_c[0]=2;cubo->car[2].ind_c[1]=1;cubo->car[2].ind_c[2]=6;
    cubo->car[3].ind_c[0]=6;cubo->car[3].ind_c[1]=1;cubo->car[3].ind_c[2]=5;
    cubo->car[4].ind_c[0]=6;cubo->car[4].ind_c[1]=5;cubo->car[4].ind_c[2]=4;
    cubo->car[5].ind_c[0]=7;cubo->car[5].ind_c[1]=6;cubo->car[5].ind_c[2]=4;
    cubo->car[6].ind_c[0]=7;cubo->car[6].ind_c[1]=3;cubo->car[6].ind_c[2]=2;
    cubo->car[7].ind_c[0]=6;cubo->car[7].ind_c[1]=7;cubo->car[7].ind_c[2]=2;
    cubo->car[8].ind_c[0]=7;cubo->car[8].ind_c[1]=3;cubo->car[8].ind_c[2]=4;
    cubo->car[9].ind_c[0]=3;cubo->car[9].ind_c[1]=0;cubo->car[9].ind_c[2]=4;
    cubo->car[10].ind_c[0]=4;cubo->car[10].ind_c[1]=0;cubo->car[10].ind_c[2]=1;
    cubo->car[11].ind_c[0]=5;cubo->car[11].ind_c[1]=4;cubo->car[11].ind_c[2]=1;   
}
*/
void draw_puntos(vertices* ver, int n_v, int grosor){
    glColor3f(1,0,0);
    glPointSize(grosor);
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glBegin(GL_POINTS);
	for (int i=0;i<n_v;i++){
            glVertex3fv((GLfloat *) &ver[i]);
	}
    glEnd();
}