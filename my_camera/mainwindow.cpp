#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    camera(new QCamera(this)),
    view_finder(new QCameraViewfinder),
    image_capture(new QCameraImageCapture(camera))
{
    ui->setupUi(this);

    ui->image_view->addWidget(view_finder);
    ui->lb_image_capture->setScaledContents(true);

    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(view_finder);
    camera->start();

    connect(image_capture, SIGNAL(imageCaptured(int, QImage)), this, SLOT(display_image(int, QImage)));
    connect(ui->button_capture, SIGNAL(clicked()), this, SLOT(capture_image()));
    connect(ui->button_save, SIGNAL(clicked()), this, SLOT(save_image()));
    connect(ui->button_quit, SIGNAL(clicked()), this, SLOT(stop()));

}

MainWindow::~MainWindow()
{
    delete camera;
    delete view_finder;
    delete image_capture;
    delete ui;
}

void MainWindow::display_image(int, QImage image)
{
    ui->statusBar->showMessage("捕获到画面!", 5000);
    ui->lb_image_capture->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::capture_image()
{
    image_capture->capture();
    ui->statusBar->showMessage("捕获画面 ...", 1000);

}

void MainWindow::save_image()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("save file"), QDir::homePath(), tr("jpegfile(*.jpg)"));
    if (fileName.isEmpty()) {
        ui->statusBar->showMessage(tr("取消保存"), 5000);
        return;
    }
    const QPixmap *pixmap = ui->lb_image_capture->pixmap();
    if (pixmap) {
        pixmap->save(fileName);
        ui->statusBar->showMessage(tr("保存成功"), 5000);
    }
}

void MainWindow::stop()
{
    camera->stop();
    close();
}

