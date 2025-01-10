#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QFileDialog>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void capture_image();
    void display_image(int, QImage);
    void save_image();
    void stop();

private:
    Ui::MainWindow *ui;

    QCamera   *camera;                    // 读取摄像头
    QCameraViewfinder *view_finder;     // 渲染摄像头
    QCameraImageCapture *image_capture; // 获取摄像头当前帧
};

#endif // MAINWINDOW_H
