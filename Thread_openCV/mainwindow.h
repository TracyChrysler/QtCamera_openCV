#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSemaphore>
#include <QLinkedList>
#include <QLabel>
#include "CaptureThread.h"
#include "DisplayThread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QSemaphore *m_semaphore;
    QLinkedList<FrameData> *m_frameQueue;
    QLabel *m_label;
    DisplayThread *m_displayThread;
    CaptureThread *m_captureThread;

};
#endif // MAINWINDOW_H
