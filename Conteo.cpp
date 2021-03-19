int designFigure(int pWidth,int pHeight, int plineArray[800][5]){ // 6 + 1441 + 2268n -> f(1447 + 2268n) -> O(n)

    srand (time(NULL));//->3 tiempos

    int counter=0, yAxis = 0, thickness, randSlope1, randSlope2, YDistance, iterator = 0, yStart, yEnd, xStart, xEnd, hTriangle1, hTriangle2;//3 tiempos

    // 1 + ( (7+ 3 + 28 + 2 + 63n) * 36) -> 1 + ((40 + 63n) * 36)  ->  1 + (1440 + 2268n)
    for (int xAxis = 0; yAxis < pHeight; xAxis += pWidth / 6){//->4 tiempos, este for se repite 36 veces (6 x 6)

        if (xAxis >= pWidth){//->2+1+4=7 tiempos
            xAxis=0;//->1 tiempo
            yAxis+= pHeight/6;//->3 tiempos
        }

        if (yAxis >= pHeight){//->2+1=3 tiempos
            break;//->1 tiempo
        }

        //28 tiempos
        YDistance=rand() % ((pHeight/6)/6) + ((pHeight/6)/24);//->8 tiempos
        randSlope1=rand() % ((pHeight/6)/5) - ((pHeight/6)/10);//->8 tiempos
        thickness=rand() % ((pHeight/6)/35) + 1;//->6 tiempos

        yStart=yAxis;//->1 tiempo
        yEnd=yAxis;//->1 tiempo
        xStart=xAxis;//->1 tiempo
        xEnd=xAxis+pWidth/6;//->3 tiempos

        // 2 + 63n -> se toma como el peor caso
        if (randSlope1<0){//-> 1 tiempo
            // 1 + ((5 + 2 + 6 + 11 + 17 + 22)n) , es decir f(1 + 63n)
            //donde n esta dado por (pHeight/6) / yDistance, y van a ser la cantidad de líneas
            for (int internalYAxis = yAxis; yStart < yAxis + pHeight / 6; internalYAxis += YDistance){//-> 5 + 2 + 6 + 11 + 17 + 22

                counter++;//->2 tiempos
                randSlope2=rand() % ((pHeight/6)/35)+1;//->6 tiempos

                if (yStart < yAxis){//->1+10=11 tiempos
                    hTriangle1=yEnd-yStart;//->2 tiempos
                    hTriangle2=yEnd-yAxis;//->2 tiempos

                    yStart= yAxis;//->1 tiempos
                    xStart = xEnd - (pWidth / 6) * (hTriangle2 / hTriangle1);//->5 tiempos
                }

                else if (yEnd > yAxis + pHeight / 6){//->3+14=17 tiempos
                    hTriangle1=yEnd-yStart;//->2 tiempos
                    hTriangle2=(yAxis+pHeight/6)-yStart;//->4 tiempos

                    yEnd=yAxis + pHeight / 6;//->3 tiempos
                    xEnd=xStart+ (pWidth / 6) * (hTriangle2 / hTriangle1);//->5 tiempos
                }

                //->22 tiempos
                plineArray[iterator][0]=xStart;
                plineArray[iterator][1]=yStart;
                plineArray[iterator][2]=xEnd;
                plineArray[iterator][3]=yEnd;
                plineArray[iterator][4]=thickness;//->15 tiempos

                xStart=xAxis;//->1 tiempo
                iterator++;//->2 tiempos
                yStart = internalYAxis + randSlope1+ randSlope2;//->3 tiempos
                yEnd = internalYAxis;//->1 tiempo
            }

        }
        else{
            // 1 + ((5 + 8 + 19 + 15) n) , es decir f(1 + 27n)
            //donde n esta dado por (pHeight/6) / yDistance, y van a ser la cantidad de líneas
            for (int internalYAxis = yAxis; yEnd < yAxis + pHeight / 6; internalYAxis += YDistance){

                // 8 tiempos
                counter++;
                randSlope2=rand() % ((pHeight/6)/35)+1;

                // 2 + 17 tiempos
                if (randSlope1!=0){
                    // 11 tiempos
                    if (yEnd<yAxis){
                        hTriangle1=yStart-yEnd;
                        hTriangle2=yStart-yAxis;

                        yEnd = yAxis;
                        xEnd -= (pWidth / 6) * (hTriangle2 / hTriangle1);
                    }
                        // 17 tiempos -> Se toma este para el peor caso
                    else if (yStart > yAxis + pHeight / 6){
                        hTriangle1=yStart - yEnd;
                        hTriangle2=(yAxis + pHeight / 6) - yEnd;

                        yStart=(yAxis + pHeight / 6);
                        xStart += (pWidth/6) * (hTriangle2/hTriangle1);
                    }
                }
                // 15 tiempos
                plineArray[iterator][0]=xStart;
                plineArray[iterator][1]=yStart;
                plineArray[iterator][2]=xEnd;
                plineArray[iterator][3]=yEnd;
                plineArray[iterator][4]=thickness;

                // 6 tiempos
                iterator++;
                yEnd = internalYAxis - randSlope1 + randSlope2;
                yStart = internalYAxis;
            }
        }

    }
    // 1 tiempo
    return counter;
}