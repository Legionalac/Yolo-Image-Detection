#ifndef AUGMENTATIONUTIL_H
#define AUGMENTATIONUTIL_H
#include <QDebug>
void RGBtoHSL(int R,int G,int B,double &h,double &s,double &l);
void HSLtoRGB(double h, double s, double l, int& r, int& g, int& b);
void hue(const uchar input[], int x_size, int y_size, uchar output[], double increment);
void GenerateDCTmatrix(double* DCTKernel, int order);
void DCT(const uchar input[], short output[], int N, double* DCTKernel);
void IDCT(const short input[], uchar output[], int N, double* DCTKernel);
void extendBorders(const uchar* input, int xSize, int ySize, int N, uchar** p_output, int* newXSize, int* newYSize);
void cropImage(uchar* input, int xSize, int ySize, uchar* output, int newXSize, int newYSize);
void doZigZag(short block[], int N, int B);
void performDCTandIDCT(uchar* input, int xSize, int ySize, int N , int B);
void imageRotate(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double angle);
void generateBlock(uchar input[],int xSize , int ySize,int number);
#endif // AUGMENTATIONUTIL_H
