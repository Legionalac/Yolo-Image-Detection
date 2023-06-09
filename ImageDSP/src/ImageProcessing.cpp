
#include "ImageProcessing.h"
#include "ColorSpaces.h"
#include "Augmentations.h"

#include <QDebug>

void imageProcessingFun(
	const QString& prog_name,
	QImage& out_img,
	const QImage& in_img,
	const QVector<double>& params
) {
	int x_size = in_img.width();
	int y_size = in_img.height();

	if(prog_name == "Augmentation 0"){
		// Create empty output image.
        out_img = QImage(x_size,y_size,in_img.format());
        QImage temp_img = QImage(x_size,y_size,in_img.format());
        temp_img = in_img.copy(0,0,x_size,y_size);
        int B = params[0];
        uchar* Y = new uchar[x_size*y_size];
        char* U = new char[x_size*y_size/4];
        char* V = new char[x_size*y_size/4];
        RGBtoYUV420(temp_img.bits(),x_size,y_size,Y,U,V);

        myAugmentation0(Y,x_size,y_size,8,B);

        YUV420toRGB(Y,U,V,x_size,y_size,out_img.bits());
        delete[] Y;
        delete[] U;
        delete[] V;

	}else if(prog_name == "Augmentation 1"){
        double incriment = params[0];
        out_img = QImage(x_size,y_size,in_img.format());
        myAugmentation1(in_img.bits(),x_size,y_size,out_img.bits(),incriment);


	}
    else if(prog_name == "Augmentation 2"){
        double angle = params[0];
        out_img = QImage(x_size,y_size,in_img.format());
        myAugmentation2(in_img.bits(),out_img.bits(),angle,x_size,y_size);
    }
    else if(prog_name == "Augmentation 3"){
        int numberOfBlock = params[0];
        out_img = in_img.copy(0,0,x_size,y_size);
        myAugmentation3(out_img.bits(),x_size,y_size,numberOfBlock);
    }

}
