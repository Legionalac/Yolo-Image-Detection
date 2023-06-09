#include <math.h>
#include <random>
#include <QRect>
#include <QImage>
#include <iostream>
#include "AugmentationUtil.h"

#define _USE_MATH_DEFINES
void RGBtoHSL(
    int R,
    int G,
    int B,
    double &h,
    double &s,
    double &l
) {
    double r, g, b;

    r = R/255.0;
    g = G/255.0;
    b = B/255.0;

    double max = qMax(qMax(r, b), g);
    double min = qMin(qMin(r, b), g);
    double delta = max - min;

    l = (max + min) / 2;

    if(delta == 0)
        s = 0;
    else{
        if(l <= 0.5)
            s = (max - min) / (max + min);
        else
            s = (max - min) / (2.0 - max - min);
    }

    if(delta == 0){
        h = 0;
    }else if(max == r){
        h = 60 * (g - b)/delta;
    }else if(max == g){
        h = 60 * (2.0 + (b - r)/delta);
    }else if(max == b){
        h = 60 * (4.0 + (r - g)/delta);
    }

    if(h < 0)
        h += 360;

}

/////

void HSLtoRGB(double h, double s, double l, int& r, int& g, int& b) {

    double C = (1 - abs(2*l - 1)) * s;
    double H = h/60;
    double X = C * (1 - abs(fmod(H, 2) - 1));

    double R = 0;
    double G = 0;
    double B = 0;

    if(H >= 0 && H < 1){
        R = C;
        B = X;
        G = 0;
    }else if(H >= 1 && H < 2){
        R = X;
        B = C;
        G = 0;
    }else if(H >= 2 && H < 3){
        R = 0;
        B = C;
        G = X;
    }else if(H >= 3 && H < 4){
        R = 0;
        B = X;
        G = C;
    }else if(H >= 4 && H < 5){
        R = X;
        B = 0;
        G = C;
    }else if(H >= 5 && H <= 6){
        R = C;
        B = 0;
        G = X;
    }

    double m = l - (C/2);

    r = ceil((R + m) * 255);
    g = ceil((G + m) * 255);
    b = ceil((B + m) * 255);

}

#define PI 3.14159265359

void hue(const uchar input[], int x_size, int y_size, uchar output[], double increment){
    for(int y = 0; y < y_size; y++){
        for(int x = 0; x < x_size; x++){
            int r = input[(y * x_size + x)*3 + 0];
            int g = input[(y * x_size + x)*3 + 1];
            int b = input[(y * x_size + x)*3 + 2];


            double h, s, l;
            RGBtoHSL(r, g, b, h, s, l);


            h += increment;
            if(h >= 360){
                h -= 360;
            }

            //convert pixel back to rgb
            HSLtoRGB(h, s, l, r, g, b);
            //output = new uchar[x_size*y_size];
            //then compose a new output
            output[(y * x_size + x)*3 + 0] = r;
            output[(y * x_size + x)*3 + 1] = g;
            output[(y * x_size + x)*3 + 2] = b;

        }
    }
}
void GenerateDCTmatrix(double* DCTKernel, int order)
{
    int i, j;
    int N;
    N = order;
    double alpha;
    double denominator;
    for (j = 0; j <= N - 1; j++)
    {
        DCTKernel[0, j] = sqrt(1 / (double)N);
    }
    alpha = sqrt(2 / (double)N);
    denominator = (double)2 * N;
    for (j = 0; j <= N - 1; j++)
        for (i = 1; i <= N - 1; i++)
        {
            DCTKernel[i*N + j] = alpha * cos(((2 * j + 1) * i * PI) / denominator);
        }
}

void DCT(const uchar input[], short output[], int N, double* DCTKernel)
{
    double* temp = new double[N*N];
    double* DCTCoefficients = new double[N*N];

    double sum;
    for (int i = 0; i <= N - 1; i++)
    {
        for (int j = 0; j <= N - 1; j++)
        {
            sum = 0;
            for (int k = 0; k <= N - 1; k++)
            {
                sum = sum + DCTKernel[i*N+k] * (input[k*N+j]-128.0);
            }
            temp[i*N + j] = sum;
        }
    }

    for (int i = 0; i <= N - 1; i++)
    {
        for (int j = 0; j <= N - 1; j++)
        {
            sum = 0;
            for (int k = 0; k <= N - 1; k++)
            {
                sum = sum + temp[i*N+k] * DCTKernel[j*N+k];
            }
            DCTCoefficients[i*N+j] = sum;
        }
    }

    for(int i = 0; i < N*N; i++)
    {
        output[i] = floor(DCTCoefficients[i]+0.5);
    }

    delete[] temp;
    delete[] DCTCoefficients;

    return;
}

void IDCT(const short input[], uchar output[], int N, double* DCTKernel)
{
    /* TO DO */
    double* temp = new double[N*N];
    double* DCTCoefficients = new double[N*N];

    double sum;
    for (int i = 0; i <= N - 1; i++)
    {
        for (int j = 0; j <= N - 1; j++)
        {
            sum = 0;
            for (int k = 0; k <= N - 1; k++)
            {
                sum = sum + DCTKernel[k*N+i] * (input[k*N+j]);
            }
            temp[i*N + j] = sum;
        }
    }

    for (int i = 0; i <= N - 1; i++)
    {
        for (int j = 0; j <= N - 1; j++)
        {
            sum = 0;
            for (int k = 0; k <= N - 1; k++)
            {
                sum = sum + temp[i*N+k] * DCTKernel[k*N+j];
            }
            DCTCoefficients[i*N+j] = sum;
        }
    }

    for(int i = 0; i < N*N; i++)
    {
        output[i] = floor(DCTCoefficients[i]+0.5)+128;
    }

    delete[] temp;
    delete[] DCTCoefficients;

    return;
}

void extendBorders(const uchar* input, int xSize, int ySize, int N, uchar** p_output, int* newXSize, int* newYSize)
{
    int deltaX = N-xSize%N;
    int deltaY = N-ySize%N;

    *newXSize = xSize+deltaX;
    *newYSize = ySize+deltaY;

    uchar* output = new uchar[(xSize+deltaX)*(ySize+deltaY)];

    for (int i=0; i<ySize; i++)
    {
        memcpy(&output[i*(xSize+deltaX)], &input[i*(xSize)], xSize);
        if(deltaX != 0)
        {
            memset(&output[i*(xSize+deltaX)+xSize], output[i*(xSize+deltaX)+xSize - 1], deltaX);
        }
    }

    for (int i=0; i<deltaY; i++)
    {
        memcpy(&output[(i + ySize)*(xSize+deltaX)], &output[(ySize)*(xSize+deltaX)], xSize+deltaX);
    }

    *p_output = output;
}

void cropImage(uchar* input, int xSize, int ySize, uchar* output, int newXSize, int newYSize)
{
    for (int i=0; i<newYSize; i++)
    {
        memcpy(&output[i*(newXSize)], &input[i*(xSize)], newXSize);
    }
}
void doZigZag(short block[], int N, int B)
{
    /* TO DO */
    int currNum = 0;
    int currDiagonalWidth = 1;
    int i;
    int row;
    int col;

    while (currDiagonalWidth<N)
    {
        for (i = 0; i<currDiagonalWidth; i++)
        {
            if (currDiagonalWidth % 2 == 1)
            {
                row = currDiagonalWidth - i - 1;
                col = i;
            }
            else
            {
                row = i;
                col = currDiagonalWidth - i - 1;
            }
            // OBRADA PIKSELA SA KOORDINATAMA row I col
            if(currNum > B)
                block[row*N + col] = 0;

            currNum++;
        }
        currDiagonalWidth++;
    }
    while (currDiagonalWidth> 0)
    {
        for (i = currDiagonalWidth; i> 0; i--)
        {
            if (currDiagonalWidth % 2 == 1){
                row = N - currDiagonalWidth + i - 1;
                col = N - i;
            }
            else
            {
                row = N - i;
                col = N - currDiagonalWidth + i - 1;
            }
            // OBRADA PIKSELA SA KOORDINATAMA row I col
            if(currNum > B)
                block[row*N + col] = 0;
            currNum++;
        }

        currDiagonalWidth--;
    }

}

void performDCTandIDCT(uchar* input, int xSize, int ySize, int N , int B)
{
    /* Create NxN buffer for one input block */
    uchar* inBlock = new uchar[N*N];

    /* Generate DCT kernel */
    double* DCTKernel = new double[N*N];
    GenerateDCTmatrix(DCTKernel, N);

    /* Create buffer for DCT coefficients */
    short* dctCoeffs = new short[N*N];

    /* Extend image borders */
    int xSize2, ySize2;
    uchar* input2;
    extendBorders(input, xSize , ySize, N, &input2, &xSize2, &ySize2);

    for (int y = 0; y < ySize2/N; y++)
    {
        for (int x = 0; x < xSize2/N; x++)
        {

            /* Fill input block buffer */
            for (int j=0; j<N; j++)
            {
                for (int i=0; i<N; i++)
                {
                    inBlock[j*N+i] = input2[(N*y+j)*(xSize2)+N*x+i];
                }
            }

            /* Invoke DCT */
            DCT(inBlock, dctCoeffs, N, DCTKernel);

            doZigZag(dctCoeffs,N,B);

            /* Invoke IDCT */
            IDCT(dctCoeffs, inBlock, N, DCTKernel);

            /* Write output values to output image */
            for (int j=0; j<N; j++)
            {
                for (int i=0; i<N; i++)
                {
                    input2[(N*y+j)*(xSize2)+N*x+i] = inBlock[j*N+i];
                }
            }
        }
    }

    cropImage(input2, xSize2, ySize2, input, xSize, ySize);

    /* Delete used memory buffers coefficients */
    delete[] dctCoeffs;
    delete[] inBlock;
    delete[] DCTKernel;
    delete[] input2;
}
void imageRotate(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double angle)
{
    /* TO DO */
    for(int i = 0; i < xSize; i++)
    {
        for(int j = 0; j < ySize; j++)
        {
            int Xp = floor(i * cos(angle) - j * sin(angle) - m * cos(angle) + n * sin(angle) + m);
            int Yp = floor(j * cos(angle) + i * sin(angle) - m * sin(angle) - n * cos(angle) + n);


            if(Xp > xSize || Xp < 0 || Yp < 0 || Yp > ySize)
            {
                output[j * 3 * xSize + i * 3] = 255;
                output[j * 3 * xSize + i * 3 + 1] = 255;
                output[j * 3 * xSize + i * 3 + 2] = 255;
            } else
            {
                output[j * 3 * xSize + i * 3] =  input[Yp * 3 * xSize + Xp * 3];
                output[j * 3 * xSize + i * 3 + 1] = input[Yp * 3 * xSize + Xp * 3 + 1];
                output[j * 3 * xSize + i * 3 + 2] = input[Yp * 3 * xSize + Xp * 3 + 2];
            }

        }
    }

}
void generateBlock(uchar input[],int xSize , int ySize,int number){
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distributionX(0,xSize - 40);
    std::uniform_int_distribution<int> distributionY(0,ySize - 40);
    int blockPositionX;
    int blockPositionY;



    for(int i=0;i<number;i++){
        blockPositionX = distributionX(generator);
        blockPositionY = distributionY(generator);


        qDebug() << blockPositionX;
        qDebug() << blockPositionY;

        for(int x = blockPositionX;x < blockPositionX + 40;x++){
            for(int y = blockPositionY; y < blockPositionY + 40;y++){
                input[(y*xSize + x) * 3 ] = 0;
                input[(y*xSize + x) * 3 + 1] = 0;
                input[(y*xSize + x) * 3 + 2] = 0;
            }
        }
    }
}
