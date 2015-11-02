#include "user_code.h"
#include "file_ply_stl.h"

#include <iostream>

void construir_piramide(float tam, float al, solido *piramide, int desplazamiento) {
    //funciones de visualización
    piramide->n_v = 5;
    piramide->n_c = 6;
    piramide->ver = (vertices *) malloc(5 * sizeof (vertices));
    piramide->car = (caras *) malloc(6 * sizeof (caras));

    //asignar puntos y caras
    //puntos
    piramide->ver[0].coord[0] = -tam;
    piramide->ver[0].coord[1] = (0 + desplazamiento);
    piramide->ver[0].coord[2] = tam;
    piramide->ver[1].coord[0] = tam;
    piramide->ver[1].coord[1] = (0 + desplazamiento);
    piramide->ver[1].coord[2] = tam;
    piramide->ver[2].coord[0] = tam;
    piramide->ver[2].coord[1] = (0 + desplazamiento);
    piramide->ver[2].coord[2] = -tam;
    piramide->ver[3].coord[0] = -tam;
    piramide->ver[3].coord[1] = (0 + desplazamiento);
    piramide->ver[3].coord[2] = -tam;
    piramide->ver[4].coord[0] = 0;
    piramide->ver[4].coord[1] = (al + desplazamiento);
    piramide->ver[4].coord[2] = 0;
    //caras
    piramide->car[0].ind_c[0] = 0;
    piramide->car[0].ind_c[1] = 1;
    piramide->car[0].ind_c[2] = 4;
    piramide->car[1].ind_c[0] = 1;
    piramide->car[1].ind_c[1] = 2;
    piramide->car[1].ind_c[2] = 4;
    piramide->car[2].ind_c[0] = 2;
    piramide->car[2].ind_c[1] = 4;
    piramide->car[2].ind_c[2] = 3;
    piramide->car[3].ind_c[0] = 3;
    piramide->car[3].ind_c[1] = 4;
    piramide->car[3].ind_c[2] = 0;
    piramide->car[4].ind_c[0] = 3;
    piramide->car[4].ind_c[1] = 0;
    piramide->car[4].ind_c[2] = 2;
    piramide->car[5].ind_c[0] = 1;
    piramide->car[5].ind_c[1] = 2;
    piramide->car[5].ind_c[2] = 0;
}

void construir_cubo(float tam, solido *cubo) {
    cubo->n_v = 8;
    cubo->n_c = 12;
    cubo->ver = (vertices *) malloc(8 * sizeof (vertices));
    cubo->car = (caras *) malloc(12 * sizeof (caras));

    //puntos
    cubo->ver[0].coord[0] = -tam;
    cubo->ver[0].coord[1] = 0;
    cubo->ver[0].coord[2] = tam;
    cubo->ver[1].coord[0] = tam;
    cubo->ver[1].coord[1] = 0;
    cubo->ver[1].coord[2] = tam;
    cubo->ver[2].coord[0] = tam;
    cubo->ver[2].coord[1] = tam;
    cubo->ver[2].coord[2] = tam;
    cubo->ver[3].coord[0] = -tam;
    cubo->ver[3].coord[1] = tam;
    cubo->ver[3].coord[2] = tam;
    cubo->ver[4].coord[0] = -tam;
    cubo->ver[4].coord[1] = 0;
    cubo->ver[4].coord[2] = -tam;
    cubo->ver[5].coord[0] = tam;
    cubo->ver[5].coord[1] = 0;
    cubo->ver[5].coord[2] = -tam;
    cubo->ver[6].coord[0] = tam;
    cubo->ver[6].coord[1] = tam;
    cubo->ver[6].coord[2] = -tam;
    cubo->ver[7].coord[0] = -tam;
    cubo->ver[7].coord[1] = tam;
    cubo->ver[7].coord[2] = -tam;

    //caras
    cubo->car[0].ind_c[0] = 3;
    cubo->car[0].ind_c[1] = 0;
    cubo->car[0].ind_c[2] = 1;
    cubo->car[1].ind_c[0] = 2;
    cubo->car[1].ind_c[1] = 3;
    cubo->car[1].ind_c[2] = 1;
    cubo->car[2].ind_c[0] = 2;
    cubo->car[2].ind_c[1] = 1;
    cubo->car[2].ind_c[2] = 6;
    cubo->car[3].ind_c[0] = 6;
    cubo->car[3].ind_c[1] = 1;
    cubo->car[3].ind_c[2] = 5;
    cubo->car[4].ind_c[0] = 6;
    cubo->car[4].ind_c[1] = 5;
    cubo->car[4].ind_c[2] = 4;
    cubo->car[5].ind_c[0] = 7;
    cubo->car[5].ind_c[1] = 6;
    cubo->car[5].ind_c[2] = 4;
    cubo->car[6].ind_c[0] = 7;
    cubo->car[6].ind_c[1] = 3;
    cubo->car[6].ind_c[2] = 2;
    cubo->car[7].ind_c[0] = 6;
    cubo->car[7].ind_c[1] = 7;
    cubo->car[7].ind_c[2] = 2;
    cubo->car[8].ind_c[0] = 7;
    cubo->car[8].ind_c[1] = 3;
    cubo->car[8].ind_c[2] = 4;
    cubo->car[9].ind_c[0] = 3;
    cubo->car[9].ind_c[1] = 0;
    cubo->car[9].ind_c[2] = 4;
    cubo->car[10].ind_c[0] = 4;
    cubo->car[10].ind_c[1] = 0;
    cubo->car[10].ind_c[2] = 1;
    cubo->car[11].ind_c[0] = 5;
    cubo->car[11].ind_c[1] = 4;
    cubo->car[11].ind_c[2] = 1;
}

void draw_puntos(vertices* ver, int n_v, int grosor) {
    glColor3f(1, 0, 0);
    glPointSize(grosor);
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glBegin(GL_POINTS);
    for (int i = 0; i < n_v; i++) {
        glVertex3fv((GLfloat *) & ver[i]);
    }
    glEnd();
}

void draw_arista_solido(solido *malla, float r, float g, float b, int modo, int grosor) {
    glColor3f(r, g, b);
    glLineWidth(grosor);

    if (modo == 0) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if (modo == 1) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < malla->n_c; i++) {
        glVertex3fv((GLfloat *) & malla->ver[malla->car[i].ind_c[0]]);
        glVertex3fv((GLfloat *) & malla->ver[malla->car[i].ind_c[1]]);
        glVertex3fv((GLfloat *) & malla->ver[malla->car[i].ind_c[2]]);
    }
    glEnd();
}

void draw_solido_ajedrez(solido *malla, float r1, float g1, float b1, float r2, float g2, float b2) {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < malla->n_c; i++) {
        if (i % 2 == 0) {
            glColor3f(r1, g1, b1);
        } else {
            glColor3f(r2, g2, b2);
        }
        glVertex3fv((GLfloat *) & malla->ver[malla->car[i].ind_c[0]]);
        glVertex3fv((GLfloat *) & malla->ver[malla->car[i].ind_c[1]]);
        glVertex3fv((GLfloat *) & malla->ver[malla->car[i].ind_c[2]]);
    }
    glEnd();

}

void generaPorRevolucion(solido *malla, int rotaciones) {
    int verticesSinrotar = malla->n_v;
    int generados = verticesSinrotar;
    malla->n_v = verticesSinrotar*rotaciones;
    //malla->n_v=(malla->n_v*rotaciones);
    malla->ver = (vertices *) realloc(malla->ver, (malla->n_v + verticesSinrotar) * sizeof (struct vertices));
    GLfloat angulo = (2.0 / rotaciones) * M_PI;
    
    for (int i = 0; i < verticesSinrotar * rotaciones - 1; i++) {
        //        for(int j=0; j<verticesSinrotar;j++){
        GLfloat x = malla->ver[i].coord[0] * cos(angulo) + malla->ver[i].coord[2] * sin(angulo);
        GLfloat y = malla->ver[i].coord[1];
        GLfloat z = malla->ver[i].coord[0]* -sin(angulo) + malla->ver[i].coord[2] * cos(angulo);


        malla->ver[i + generados].coord[0] = x;
        malla->ver[i + generados].coord[1] = y;
        malla->ver[i + generados].coord[2] = z;
        //            generados++;
        cout << malla->ver[i+generados].coord[0] << ",";
        cout << malla->ver[i+generados].coord[1] << ",";
        cout << malla->ver[i+generados].coord[2] << endl;
        //        }  
        //        angulo+=angulo;
    }
}
//solidoply->ver =  (vertices*) malloc(solidoply->n_v*sizeof(vertices));


//copia vertices
//void copiaVertices_ply(vector<float> v_ply, solido *ply){
//    for(int i=0;i<v_ply.size();i++){
//        ply->ver[i]=v_ply.at(i);
//    }
//}

//copia caras
//void copiaCaras_ply(vector<int> c_ply, solido *ply){
//    for(int i=0;i<c_ply.size();i++){
//        ply->car[i]=c_ply.at(i);
//    }
//}