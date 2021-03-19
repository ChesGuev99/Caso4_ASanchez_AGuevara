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
int designFigure(int pWidth,int pHeight, int plineArray[800][5]){

    // Samilla para generar randoms
    srand (time(NULL));

    int counter=0, yAxis = 0, thickness, randSlope1, randSlope2, YDistance, iterator = 0, yStart, yEnd, xStart, xEnd, hTriangle1, hTriangle2;

    //recorre los "subcuadros" a travez del ancho dado para dibujar
    for (int xAxis = 0; yAxis < pHeight; xAxis += pWidth / 6){

        //Al llegar al final del ancho reinicia el valor de x a 0 y aumenta el y (dado por altura)
        // para pasar a la siguiente fila de "subcuadros"
        if (xAxis >= pWidth){//->reiniciar x aquí
            xAxis=0;
            yAxis+= pHeight/6;
        }

        // en caso de que la altura sea igual a la altura dada por el usuario, detiene el for
        if (yAxis >= pHeight){
            break;
        }

        // La distancia entre las lineas, la pendiente de estas y el ancho de las lineas se da a partir de un random,
        // todos dados en base a la altura dada
        YDistance=rand() % ((pHeight/6)/6) + ((pHeight/6)/24);
        randSlope1=rand() % ((pHeight/6)/5) - ((pHeight/6)/10);
        thickness=rand() % ((pHeight/6)/35)+1;

        // Asignacion inicial de los puntos de la linea
        yStart=yAxis;
        yEnd=yAxis;
        xStart=xAxis;
        xEnd=xAxis+pWidth/6;

        // en caso de que la pendiente sea negativa
        if (randSlope1<0){

            //recorre los "subcuadros" a travez del alto dado para dibujar cada linea
            for (int internalYAxis = yAxis; yStart < yAxis + pHeight / 6; internalYAxis += YDistance){

                //counter va a ser el total de lineas dibujadas, mientras que
                // randslope2 va a ser la pendiente individual de cada linea
                counter++;
                randSlope2=rand() % ((pHeight/6)/35)+1;

                //se calcula la intersección con el borde del cuadrado por medio de la formula de semejanza de triángulos rectangulos
                // se divide la altura del pequeño entre el grande y se multiplica por la base del grande para obtenetr la base del pequeño

                // realiza las operaciones tomando en consideración si la linea se sale del cuadro por arriba o abajo
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

                //Arreglo que contiene los puntos de la linea, [x1,y1,x2,y2,grueso]
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
        // en caso de que la pendiente sea positiva
        else{
            //recorre los "subcuadros" a travez del alto dado para dibujar cada linea
            for (int internalYAxis = yAxis; yEnd < yAxis + pHeight / 6; internalYAxis += YDistance){

                //counter va a ser el total de lineas dibujadas, mientras que
                // randslope2 va a ser la pendiente individual de cada linea
                counter++;
                randSlope2=rand() % ((pHeight/6)/35)+1;

                // en caso de que la pendiente sea de 0, no hace ningun calculo extra
                if (randSlope1!=0){
                    // realiza las operaciones tomando en consideración si la linea se sale del cuadro por arriba o abajo
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
                //Arreglo que contiene los puntos de la linea, [x1,y1,x2,y2,grueso]
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

    // Dado que las líneas se generan de forma aleatoria, solo es necesario correr el
    // código nuevamente para generar un nuevo patrón, no predecible, para comprobar el
    // código solo es necesario copiar el arreglo imprimido dentro de la lista en el programa linesforList.pde

    // Prueba 1
    int arrayP[600][5];
    int count = designFigure(600,600,arrayP);
    for (int i=0; i<count; i++ ){
        cout << "{" <<arrayP[i][0] << "," << arrayP[i][1] << "," << arrayP[i][2]<< "," << arrayP[i][3]<< "," << arrayP[i][4] << "}" << ","<<endl;
    }
    // cantidad de lineas generadas
    cout << "LineCount:"<< count << endl << endl;

    // Prueba 2
    /*
    int arrayP2[600][5];
    int count2 = designFigure(600,600,arrayP2);
    for (int i=0; i<count2; i++ ){
        cout << "{" <<arrayP2[i][0] << "," << arrayP2[i][1] << "," << arrayP2[i][2]<< "," << arrayP2[i][3]<< "," << arrayP2[i][4] << "}" << ","<<endl;
    }
    // cantidad de lineas generadas
    cout << "LineCount:"<< count2 << endl; */

    return 0;

}


//Verificaciones en el segundo for:
//1.Calcular la posición del segundo punto: listo en papel
//2.Que el punto no se salga del recuadro: listo en papel

//Nota: Hacer que los límites de los randoms cambien con el pWidth