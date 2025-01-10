// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Capture_clicked();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture cap;
    cv::CascadeClassifier face_cascade;

    void processFrame(cv::Mat frame);
    void saveDetectedFaces(std::vector<cv::Rect> faces, cv::Mat frame);
};

#endif // MAINWINDOW_H
