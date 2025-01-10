// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 加载人脸检测模型
    if (!face_cascade.load("D:/documents/qt/qtcamera_opencv/FaceOpencv/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/etc/haarcascades/haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade!" << std::endl;
    }

    // 打开摄像头
    cap.open(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Capture_clicked()
{
    cv::Mat frame;
    cap >> frame;
    processFrame(frame);
}

void MainWindow::processFrame(cv::Mat frame)
{
    std::vector<cv::Rect> faces;
    cv::Mat gray;

    // 转换为灰度图
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    // 检测人脸
    face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    // 绘制人脸框并保存人脸图像
    saveDetectedFaces(faces, frame);

    // 在QLabel上显示处理后的图像
    QImage qimg = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped();
    ui->videoLabel->setPixmap(QPixmap::fromImage(qimg));
}

void MainWindow::saveDetectedFaces(std::vector<cv::Rect> faces, cv::Mat frame)
{
    int i = 0;
    for (cv::Rect face : faces)
    {
        cv::Mat faceROI = frame(face);
        std::stringstream ss;
        ss << "face_" << i++ << ".jpg";

        // 打印当前工作目录
        QString currentDir = QDir::currentPath();
        qDebug() << "Current working directory: " << currentDir;
        cv::imwrite(ss.str(), faceROI);
        std::cerr << "save picture successfuly!" << std::endl;
    }
}


