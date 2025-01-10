#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCloseEvent>  // 包含 QCloseEvent

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "init MainWindow" << endl;
    m_semaphore = new QSemaphore(0);
    m_frameQueue = new QLinkedList<FrameData>();   //QLinkedList是Qt的一个模板类，<FrameData>是模板参数，表示该链表将存储一个FrameData类型的元素
    m_label = new QLabel(this);
    m_label->setGeometry(50, 50, 640, 480);
    m_captureThread = new CaptureThread(m_semaphore, m_frameQueue);
    m_displayThread = new DisplayThread(m_semaphore, m_frameQueue, m_label);

    m_captureThread->start();    //调用run函数
    m_displayThread->start();

}

MainWindow::~MainWindow()
{
    qDebug() << "delete MainWindow" << endl;
    delete m_displayThread;
    delete m_captureThread;
    delete m_frameQueue;
    delete m_semaphore;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "run closeEvent" << endl;
    if(m_captureThread->isRunning()){
        m_captureThread->stopCapture();
        m_captureThread->quit();
        m_captureThread->wait();
    }
    if(m_displayThread->isRunning()){
        m_displayThread->stopDisplay();
        m_displayThread->quit();
        m_displayThread->wait();
    }
    event->accept();
}

