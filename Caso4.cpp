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
int designFigure(int pWidth,int pHeight, int plineArray[400][5]){//->agregar alto
    srand (time(NULL));

    int counter=0, yAxis = 0, thickness, randSlope1, randSlope2, YDistance, iterator = 0, yStart, yEnd, xStart, xEnd, hTriangle1, hTriangle2;
    for (int xAxis = 0; yAxis < pHeight; xAxis += pWidth / 6){//->revisar condicion de parada
        //Aquí guardar los puntos del cuadrado
        if (xAxis >= pWidth){//->reiniciar x aquí
            xAxis=0;
            yAxis+= pHeight/6;
        }
        
        if (yAxis >= pHeight){
            break;
        }
        
        //YDistance=rand() % 20 + 5;
        //randSlope1=rand() % 13 - 6;//le puse menos 30 para que la pendiente pueda ser negativa 
        YDistance=rand() % ((pHeight/6)/6) + ((pHeight/6)/12);
        randSlope1=rand() % ((pHeight/6)/12) - ((pHeight/6)/24);
        thickness=rand() % ((pHeight/6)/35)+1;

        yStart=yAxis;
        yEnd=yAxis;
        xStart=xAxis;
        xEnd=xAxis+pWidth/6;
        
        if (randSlope1<0){
            for (int internalYAxis = yAxis; yStart < yAxis + pHeight / 6; internalYAxis += YDistance){
                counter++;
                randSlope2=rand() % ((pHeight/6)/35)+1;
                //se calcula la intersección con el borde del cuadrado por medio de triángulos (no sé cómo se llama el teorema pero es como dibujar un triángulo rectángulo dentro del otro, divido la altura del pequeño entre al del grande y lo multiplico por la base del grande para obtenetr la base del pequeño)
                if (yStart < yAxis){
                    hTriangle1=yEnd-yStart;
                    hTriangle2=yEnd-yAxis;

                    yStart= yAxis;
                    xStart = xEnd - (pWidth / 6) * (hTriangle2 / hTriangle1);
                }
                else if (yEnd > yAxis + pHeight / 6){
                    hTriangle1=yEnd-yStart;
                    hTriangle2=(yAxis+pHeight/6)-yStart;
                    
                    yEnd=yAxis + pHeight / 6;
                    xEnd=xStart+ (pWidth / 6) * (hTriangle2 / hTriangle1);
                }
                
                plineArray[iterator][0]=xStart;
                plineArray[iterator][1]=yStart;
                plineArray[iterator][2]=xEnd;
                plineArray[iterator][3]=yEnd;
                plineArray[iterator][4]=thickness;

                xStart=xAxis;
                iterator++;
                yStart = internalYAxis + randSlope1+ randSlope2;
                yEnd = internalYAxis;
            }

        }
        else{
            for (int internalYAxis = yAxis; yEnd < yAxis + pHeight / 6; internalYAxis += YDistance){
                counter++;
                randSlope2=rand() % ((pHeight/6)/35)+1;
                
                if (randSlope1!=0){
                    if (yEnd<yAxis){
                        hTriangle1=yStart-yEnd;
                        hTriangle2=yStart-yAxis;
                        
                        yEnd = yAxis;
                        xEnd -= (pWidth / 6) * (hTriangle2 / hTriangle1);
                    }
                    else if (yStart > yAxis + pHeight / 6){
                        hTriangle1=yStart - yEnd;
                        hTriangle2=(yAxis + pHeight / 6) - yEnd;

                        yStart=(yAxis + pHeight / 6);
                        xStart += (pWidth/6) * (hTriangle2/hTriangle1);  // Divisiones /0 
                    }
                }
                
                plineArray[iterator][0]=xStart;
                plineArray[iterator][1]=yStart;
                plineArray[iterator][2]=xEnd;
                plineArray[iterator][3]=yEnd;
                plineArray[iterator][4]=thickness;
                iterator++;
                yEnd = internalYAxis - randSlope1 + randSlope2;
                yStart = internalYAxis;
            }
        }
        
    } 
    return counter;
}

int main()
{
    int arrayP[400][5];
    int count = designFigure(600,600,arrayP);
    for (int i=0; i<count; i++ ){
        cout << "{" <<arrayP[i][0] << "," << arrayP[i][1] << "," << arrayP[i][2]<< "," << arrayP[i][3]<< "," << arrayP[i][4] << "}" << ","<<endl;
    }
    cout << "LineCount:"<< count << endl;
    return 0;

}


//Verificaciones en el segundo for:
//1.Calcular la posición del segundo punto: listo en papel
//2.Que el punto no se salga del recuadro: listo en papel

//Nota: Hacer que los límites de los randoms cambien con el pWidth