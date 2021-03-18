#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cctype>
#include <time.h>
using namespace std;


//n = (altura/6) /YDistance , para cada subcuadro

int designFigure(int pWidth, int pArray[50][5]){
    srand (time(NULL));  //seed del random      4 tiempos
    int* lineArray=pArray[0];       //lista de lineas en primera pos   1 tiempo
    int counter=0, yAxis = 0, randSlope1, randSlope2, YDistance, iterator = 0, yStart, yEnd, xStart, xEnd, hTriangle1, hTriangle2; // 12 tiempos !!!!
        // 1 + ((4+ )6) , donde for 1 = 6  y for 2 = 6
    for (int xAxis = 0; yAxis < pWidth; xAxis += pWidth / 6) {//->revisar condicion de parada // Aumento horizontal, condición de parada vertical
        //Aquí guardar los puntos del cuadrado
        if (xAxis >= pWidth){//->reiniciar x aquí // Cuando llegue al final de la fila, reiniciar x, aumentar y
            xAxis=0;
            yAxis+= pWidth/6;
        }  // 5 tiempos
        // random distancia entre lineas, random pendiente
        YDistance=rand() % 20 + 5; // distancia entre lineas
        randSlope1=rand() % 13 - 6;//le puse menos 30 para que la pendiente pueda ser negativa //pendiente

        // 4 tiempos
        yStart=yAxis;
        yEnd=yAxis;
        xStart=xAxis;
        xEnd=xAxis+pWidth/6;
        //Si la pendiente es negativa  // 1+
        if (randSlope1<0){
            // 1 + ((5+ 9 + 19 + (9 o 10)!!!!!  )n ) el for se n , donde n es (altura/6) /YDistance
            // f (1 + (32 o 33)n!!!!!  )  O(n)
            for (int internalYAxis = yAxis; yStart < yAxis + pWidth / 6; internalYAxis += YDistance) {
                // + 9 tiempos
                counter++;       // 2 tiempos
                randSlope2 = rand() % 3 - 1;              // 4 tiempos
                yStart = internalYAxis + randSlope1;    // 2 tiempos
                yEnd = internalYAxis;                   // 1 tiempo
                //se calcula la intersección con el borde del cuadrado por medio de triángulos
                // (no sé cómo se llama el teorema pero es como dibujar un triángulo rectángulo dentro del otro,
                // divido la altura del pequeño entre al del grande y lo multiplico por la base del grande para
                // obtenetr la base del pequeño)
                if (randSlope1 != 0) {                     // 2 tiempos + 17 -> 19 tiempos tiempos en peor de los casos
                    if (yStart < yAxis) {                // 11 tiempos
                        hTriangle1 = yEnd - yStart;
                        hTriangle2 = yEnd - yAxis;

                        yStart = yAxis;
                        xStart = xEnd - (pWidth / 6) * (hTriangle2 / hTriangle1); // 5
                    } else if (yEnd > yAxis + pWidth / 6) {                        // 3 + 14 = 17 tiempos
                        hTriangle1 = yEnd - yStart;                                 //2
                        hTriangle2 = (yAxis + pWidth / 6) - yStart;                     //4
                        yEnd = yAxis + pWidth / 6;                                //3
                        xEnd = xStart + (pWidth / 6) * (hTriangle2 / hTriangle1); // 5
                    }
                }
                // 9 o 10 tiempos
                int line[5] = {xStart, yStart, xEnd, yEnd, 5}; // 5
                lineArray[iterator] = *line;                      // 1 + 1 +     1??? * !!!!!!!!
                iterator++;                                     // 2
            }
        }
        //Si la pendiente es positiva o 0
        else{
            // f (1 + (48)n!!!!!  )  O(n)
            for (int internalYAxis = yAxis; yEnd < yAxis + pWidth / 6; internalYAxis += YDistance){
                //9 tiempos
                counter++;
                randSlope2=rand() % 3 - 1;
                yEnd = internalYAxis - randSlope1;
                yStart = internalYAxis;

                // 2+ 17 -> 19 tiempos
                if (randSlope1!=0){
                    if (yEnd<yAxis){        // 11 tiempos
                        hTriangle1=yStart-yEnd;
                        hTriangle2=yStart-yAxis;

                        yEnd = yAxis;
                        xEnd -= (pWidth / 6) * (hTriangle2 / hTriangle1);
                    }
                    else if (yStart > yAxis + pWidth / 6){      // 17 tiempos
                        hTriangle1=yStart - yEnd;
                        hTriangle2=(yAxis + pWidth / 6) - yEnd;

                        yStart=(yAxis + pWidth / 6);
                        xStart += (pWidth/6) * (hTriangle2/hTriangle1);
                    }
                }
                // 10 tiempos?
                int line[5] = {xStart, yStart, xEnd, yEnd, 5};      // 3 tiempos + 5 vs 5 tiempos? la cosa es que gasta menos tiempos
                // .... y no logré arreglar un bug en la funcion
                lineArray[iterator]=*line;
                iterator++;
            }
        }

    }
    return counter; //+1
}

int main()
{
    int arrayP[400][5];
    int count = designFigure(600,arrayP);
    //cout << arrayP[0][0];
    for (int i=0; i<count; i++ ){
        cout << "[" <<arrayP[i][0] << "," << arrayP[i][1] << "," << arrayP[i][2]<< "," << arrayP[i][3]<< "," << arrayP[i][4] << "]"<<endl;
    }
    cout << "LineCount:"<< count << endl;
    return 0;
}