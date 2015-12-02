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

void generaPorRevolucion(solido *malla, int rotaciones, int tapas) {
    int verticesSinrotar = malla->n_v;
    int generados = verticesSinrotar;
    malla->n_v = verticesSinrotar*rotaciones;
    malla->ver = (vertices *) realloc(malla->ver, (malla->n_v + verticesSinrotar) * sizeof (struct vertices));
    GLfloat angulo = (2.0 / rotaciones) * M_PI;
    int num_c=0;
    int num_ver=(generados-1);
    int j=0;
    
    malla->car= (caras *)malloc(1000000*sizeof(caras));
    for (int i = 0; i < verticesSinrotar * rotaciones; i++) {
        
        GLfloat x = malla->ver[i].coord[0] * cos(angulo) + malla->ver[i].coord[2] * sin(angulo);
        GLfloat y = malla->ver[i].coord[1];
        GLfloat z = malla->ver[i].coord[0] * -sin(angulo) + malla->ver[i].coord[2] * cos(angulo);


        malla->ver[i + generados].coord[0] = x;
        malla->ver[i + generados].coord[1] = y;
        malla->ver[i + generados].coord[2] = z;       
        //        angulo+=angulo;
        
        num_ver+=1;
 
     if (i < verticesSinrotar * rotaciones - verticesSinrotar){
       if((num_ver % verticesSinrotar)==0){
            malla->car[j].ind_c[0]=i;
            malla->car[j].ind_c[1]=i+1;
            malla->car[j].ind_c[2]=num_ver;
            num_c+=1;
        }else{
            malla->car[j].ind_c[0]=num_ver -1;
            malla->car[j].ind_c[1]=i;
            malla->car[j].ind_c[2]=num_ver;
            if((num_ver % verticesSinrotar)!=1){
                j+=1;
                malla->car[j].ind_c[0]=i-1;
                malla->car[j].ind_c[1]=i;
                malla->car[j].ind_c[2]=num_ver -1;
                num_c+=1;
                        
            }
            num_c+=1;
        }
        j+=1;
                      
        }
    }

    //unir perfil final con inicial
    int p_inicial=0;
    for(int i=verticesSinrotar * rotaciones -verticesSinrotar; i < malla->n_v-1;i++){
      malla->car[num_c].ind_c[0]=i;malla->car[num_c].ind_c[1]=i+1;malla->car[num_c ].ind_c[2]=p_inicial;
      num_c+=1;
      p_inicial+=1; 
      malla->car[num_c].ind_c[0]=i+1;malla->car[num_c].ind_c[1]=p_inicial;malla->car[num_c ].ind_c[2]=p_inicial-1;
      num_c+=1;
    }
    
    if (tapas==1){
    //cerrar tapas arriba
     for (int i=0; i < rotaciones-2;i++){
         if(i!=rotaciones-3){
             malla->car[num_c].ind_c[0]=i*verticesSinrotar+verticesSinrotar-1;
             malla->car[num_c].ind_c[1]=2*verticesSinrotar+(i*verticesSinrotar)-1 ;
             malla->car[num_c ].ind_c[2]=verticesSinrotar*rotaciones -1;
             num_c+=1; 
         }else{
             malla->car[num_c].ind_c[0]=(i*verticesSinrotar+verticesSinrotar-1)%verticesSinrotar;
             malla->car[num_c].ind_c[1]=2*verticesSinrotar+(i*verticesSinrotar)-1 ;
             malla->car[num_c].ind_c[2]=verticesSinrotar*rotaciones -1;
             num_c+=1;       
         }      
     }
    //cerrar tapas de abajo
        for (int i=0; i < rotaciones-2;i++){
            malla->car[num_c].ind_c[0]=verticesSinrotar*rotaciones-verticesSinrotar;
            malla->car[num_c].ind_c[1]=verticesSinrotar+(i*verticesSinrotar);
            malla->car[num_c ].ind_c[2]=i*verticesSinrotar;
            num_c+=1; 
        }
    }  
           
  malla->n_c=num_c;
        
}
