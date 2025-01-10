#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QThread>
#include <QSemaphore>   //线程同步
#include <QLinkedList>
#include <opencv2/opencv.hpp>
#include "FrameData.h"

class CaptureThread : public QThread {
    Q_OBJECT
public:
    CaptureThread(QSemaphore *semaphore, QLinkedList<FrameData> *frameQueue);
    ~CaptureThread();
    void stopCapture();

protected:
    void run() override;     //QThread的虚函数

private:
    QSemaphore *m_semaphore;
    QLinkedList<FrameData> *m_frameQueue;
    cv::VideoCapture m_cap;
    bool m_stopCapture;
};

#endif // CAPTURETHREAD_H
