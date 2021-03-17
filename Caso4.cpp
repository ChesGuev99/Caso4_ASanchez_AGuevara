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

//recibe un arreglo y lo modifica de manera que se puedan dibujar líneas con los puntos dentro de cada sub-arreglo
void designFigure(int pWidth, int **pArray){
    srand (time(NULL));
    int **lineArray=pArray;
    int yAxis = 0, randSlope1, randSlope2, YDistance, iterator = 0, yStart, yEnd, xStart, xEnd, hTriangle1, hTriangle2;
    for (int xAxis = 0; xAxis < pWidth; xAxis += pWidth / 6){
        //Aquí guardar los puntos del cuadrado
        if (yAxis >= pWidth){
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
        
        YDistance=rand() % 90 + 1;
        randSlope1=rand() % 41 - 20;//le puse menos 30 para que la pendiente pueda ser negativa 
        
        //Si la pendiente es negativa
        if (randSlope1<0){
            for (int internalYAxis = yAxis; yStart < yAxis + pWidth / 6; internalYAxis += YDistance){
                randSlope2=rand() % 3 - 1;
                xStart = xAxis;
                yStart = internalYAxis+randSlope1;
                yEnd = internalYAxis;
                xEnd = xAxis + pWidth / 6;

                //se calcula la intersección con el borde del cuadrado por medio de triángulos (no sé cómo se llama el teorema pero es como dibujar un triángulo rectángulo dentro del otro, divido la altura del pequeño entre al del grande y lo multiplico por la base del grande para obtenetr la base del pequeño)
                if (yStart < yAxis){
                    hTriangle1=yEnd-yStart;
                    hTriangle2=yEnd-yAxis;

                    yStart= yAxis;
                    xStart = xEnd - (pWidth / 6) * (hTriangle2 / hTriangle1);
                }
                else if (yEnd > yAxis + pWidth / 6){
                    hTriangle1=yEnd-yStart;
                    hTriangle2=(yAxis+pWidth/6)-yStart;
                    
                    yEnd=yAxis + pWidth / 6;
                    xEnd=xStart+ (pWidth / 6) * (hTriangle2 / hTriangle1);
                }

                lineArray[iterator]=createLine(xStart, yStart, xEnd, yEnd, 5);
                iterator++;

            }

        }
        //Si la pendiente es positiva o 0
        else{
            for (int internalYAxis = 0; yStart < yEnd + pWidth / 6; internalYAxis += YDistance){
                randSlope2=rand() % 3 - 1;
                xStart = xAxis;
                yStart = internalYAxis;
                yEnd = internalYAxis-randSlope1;
                xEnd = xAxis + pWidth / 6;
                if (yEnd<yAxis){
                    hTriangle1=yStart-yEnd;
                    hTriangle2=yStart-yAxis;
                    yEnd = yAxis;
                    xEnd -= (pWidth / 6) * (hTriangle2 / hTriangle1);
                }
                else if (yStart > yAxis + pWidth / 6){
                    hTriangle1=yStart - yEnd;
                    hTriangle2=(yAxis + pWidth / 6) - yEnd;

                    yStart=(yAxis + pWidth / 6);
                    xStart += (pWidth/6) * (hTriangle2/hTriangle1);  
                }
                lineArray[iterator]=createLine(xStart, yStart, xEnd, yEnd, 5);
                iterator++;
            }
        }
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

//Nota: Hacer que los límites de los randoms cambien con el pWidth