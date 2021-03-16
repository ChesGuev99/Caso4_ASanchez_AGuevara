#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cctype>
#include <time.h>
using namespace std;
//[[x1,y1,x2,y2,ancho],[x1,y1,x2,y2,ancho],...]

//recibe dos puntos y el ancho, retorna un arreglo
int * createLine(int px1, int py1, int px2, int py2, int pWidth){
    static int line[5]={px1, py1, px2, py2, pWidth};
    return line;
}

//recibe un arreglo y lo modifica para retornarlo de manera que se puedan dibujar líneas con los puntos dentro de cada sub-arreglo
void designFigure(int pWidth, int **pArray){
    srand (time(NULL));
    int **lineArray=pArray;
    int yAxis = 0, randSlope1, randSlope2, randYsum, iterator = 0;
    for (int xAxis = 0; xAxis < pWidth; xAxis += pWidth / 6){
        //Aquí guardar los puntos del cuadrado
        if (yAxis > pWidth){
            yAxis=0;
        }
        lineArray[iterator]=createLine(xAxis, yAxis, xAxis + pWidth / 6, yAxis, 5);
        iterator++;
        lineArray[iterator]=createLine(xAxis, yAxis, xAxis, yAxis + pWidth / 6, 5);
        iterator++;
        lineArray[iterator]=createLine(xAxis, yAxis + pWidth / 6, xAxis + pWidth / 6, yAxis + pWidth / 6, 5);
        iterator++;
        lineArray[iterator]=createLine(xAxis + pWidth / 6, yAxis, xAxis + pWidth / 6, yAxis + pWidth / 6, 5);
        iterator++;
        
        randYsum=rand() % 10 + 1;//->revisar que los valores estén bien 
        randSlope1=rand() % 21 - 10;//le puse menos 10 para que la pendiente pueda ser negativa 
        
        for (int internalYAxis = 0; internalYAxis< pWidth / 6; internalYAxis += randYsum){
            randSlope2=rand() % 7 - 3;
            
            //Ver final del cpp
        }
        yAxis += pWidth / 6;
        
    }
    return;
}

int main()
{
    //int* array[500][5];

    return 0;
}


//Verificaciones en el segundo for:
//1.Calcular la posición del segundo punto: listo en papel
//2.Que el punto no se salga del recuadro: listo en papel
