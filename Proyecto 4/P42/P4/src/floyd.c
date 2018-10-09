#include<stdlib.h>
#include<stdio.h>
#define INF 32767

void floyd(int nodos){
	//Inicializar dos matrices nodos*nodos llenas de infinitos para algoritmo y respuesta
	int** mFloyd;
	int** mRespuesta;
	mFloyd = malloc(nodos*sizeof(int*));
	mRespuesta = malloc(nodos*sizeof(int*));
	for(int m=0;m<nodos;m++){
		mFloyd[m] = malloc(nodos * sizeof(int));
		mRespuesta[m] = malloc(nodos * sizeof(int));
		for(int n=0;n<nodos;n++){
			mFloyd[m][n] = INF;
			mRespuesta[m][n] = INF;
		}
	}

	//Rellenar matriz con datos de usuario
	
	//Floyd
	for(int k=0;k<nodos;k++){
		for(int i=0;i<nodos;i++){
			for(int j=0;j<nodos;j++){
				int temp = mFloyd[i][k] + mFloyd[k][j];
				if(mFloyd[i][j] > temp){
					mFloyd[i][j] = temp;
					mRespuesta[i][j] = k;
				}
			}
		}
	}	
}
