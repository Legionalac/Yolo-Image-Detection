#include <QRect>
#include <QImage>
#include "Augmentations.h"
#include <math.h>
#include "AugmentationUtil.h"
void myAugmentation0(uchar input[],int xSize, int ySize, int N, int B) {

    performDCTandIDCT(input,xSize,ySize,N,B);
}


void myAugmentation1(const uchar input[], int x_size, int y_size, uchar output[], double increment) {
    hue(input,x_size,y_size,output,increment);
}
void myAugmentation2(const uchar input[],uchar output[],double angle , int xSize , int ySize){
   imageRotate(input,xSize,ySize,output,xSize/2,ySize/2,angle);
}
void myAugmentation3(uchar input[],int xSize,int ySize,int number){

   generateBlock(input,xSize,ySize,number);

}



