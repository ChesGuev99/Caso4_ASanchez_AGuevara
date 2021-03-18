#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cctype>
#include <time.h>
using namespace std;
//Formato del string modificado: [[x1,y1,x2,y2,ancho],[x1,y1,x2,y2,ancho],...]

//recibe dos puntos y el ancho, retorna un arreglo
/*int * createLine(int px1, int py1, int px2, int py2, int pWidth){
    static int line[5]={px1, py1, px2, py2, pWidth};
    return line;
}
*/
//recibe un arreglo y lo modifica de manera que se puedan dibujar líneas con los puntos dentro de cada sub-arreglo
int designFigure(int pWidth, int lineArray[400][5]){//->agregar alto
    srand (time(NULL));
    //int* lineArray=*pArray;
    int counter=0, yAxis = 0, randSlope1, randSlope2, YDistance, iterator = 0, yStart, yEnd, xStart, xEnd, hTriangle1, hTriangle2;
    for (int xAxis = 0; yAxis < pWidth; xAxis += pWidth / 6){//->revisar condicion de parada
        //Aquí guardar los puntos del cuadrado
        if (xAxis >= pWidth){//->reiniciar x aquí
            xAxis=0;
            yAxis+= pWidth/6;
        }
        
        YDistance=rand() % 20 + 5;
        randSlope1=rand() % 7 - 6;//le puse menos 30 para que la pendiente pueda ser negativa 

        yStart=yAxis;
        yEnd=yAxis;
        xStart=xAxis;
        xEnd=xAxis+pWidth/6;
        //Si la pendiente es negativa
        if (randSlope1<0){
            for (int internalYAxis = yAxis; yStart < yAxis + pWidth / 6; internalYAxis += YDistance){
                counter++;
                randSlope2=rand() % 3 - 1;
                yStart = internalYAxis + randSlope1;
                yEnd = internalYAxis;
                //se calcula la intersección con el borde del cuadrado por medio de triángulos (no sé cómo se llama el teorema pero es como dibujar un triángulo rectángulo dentro del otro, divido la altura del pequeño entre al del grande y lo multiplico por la base del grande para obtenetr la base del pequeño)
                if (yStart < yAxis){
                    hTriangle1=yEnd-yStart;
                    hTriangle2=yEnd-yAxis;
                    cout << "sale por arriba start: " << yStart << endl;
                    yStart= yAxis;
                    xStart = xEnd - (pWidth / 6) * (hTriangle2 / hTriangle1);
                }
                else if (yEnd > yAxis + pWidth / 6){
                    hTriangle1=yEnd-yStart;
                    hTriangle2=(yAxis+pWidth/6)-yStart;
                    cout << "sale por abajo end: " << yEnd << endl;
                    yEnd=yAxis + pWidth / 6;
                    xEnd=xStart+ (pWidth / 6) * (hTriangle2 / hTriangle1);
                }
                
                //cout << "checkpoint ystart: " << yStart << endl;
                //cout << "checkpoint yend: " << yEnd << endl;
                //int line[5] = {xStart, yStart, xEnd, yEnd, 5};
                lineArray[iterator][0]=xStart;
                lineArray[iterator][1]=yStart;
                lineArray[iterator][2]=xEnd;
                lineArray[iterator][3]=yEnd;
                lineArray[iterator][4]=5;

                iterator++;
            }

        }
        //Si la pendiente es positiva o 0
        else{
            for (int internalYAxis = yAxis; yEnd < yAxis + pWidth / 6; internalYAxis += YDistance){
                counter++;
                randSlope2=rand() % 3 - 1;
                yEnd = internalYAxis - randSlope1;
                yStart = internalYAxis;
                if (randSlope1!=0){
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
                        xStart += (pWidth/6) * (hTriangle2/hTriangle1);  // Divisiones /0 
                    }
                }
                      // 3 tiempos + 5 vs 5 tiempos? la cosa es que gasta menos tiempos
                                                                    // .... y no logré arreglar un bug en la funcion
                lineArray[iterator][0]=xStart;
                lineArray[iterator][1]=yStart;
                lineArray[iterator][2]=xEnd;
                lineArray[iterator][3]=yEnd;
                lineArray[iterator][4]=5;
                iterator++;
            }
        }
        
    } 
    return counter;
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


//Verificaciones en el segundo for:
//1.Calcular la posición del segundo punto: listo en papel
//2.Que el punto no se salga del recuadro: listo en papel

//Nota: Hacer que los límites de los randoms cambien con el pWidth