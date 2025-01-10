#include "widget.h"

#include <QApplication>
#include <opencv2/opencv.hpp>   //只导入这一个头文件就行，这个头文件包含了opencv的基本功能
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //改成自己图片的路径,注意使用的是'/'
    Mat image=imread("D:/qt/openCV/11.jpg");
    imshow("Output",image);
//    Widget w;
//    w.show();
    return a.exec();
}
