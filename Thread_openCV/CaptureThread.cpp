#include <QDebug>
#include "CaptureThread.h"

CaptureThread::CaptureThread(QSemaphore *semaphore, QLinkedList<FrameData> *frameQueue)
    :m_semaphore(semaphore)
    ,m_frameQueue(frameQueue)
    ,m_cap(0)
    ,m_stopCapture(false)
{
    qDebug() << "init captureThread" << endl;
}

CaptureThread::~CaptureThread()
{
    qDebug() << "run delete captureThread" << endl;
}

void CaptureThread::run()
{
    qDebug() << "run captureThread" << endl;
    m_cap.open(0);
    if(!m_cap.isOpened()){
        qWarning("Failed to open camera");
        return;
    }

    while(!m_stopCapture){
        cv::Mat frame;
        m_cap >> frame;
        if(frame.empty()){
            qWarning() << "capture an empty frame";
            continue;
        }

        FrameData data;
        data.frame = frame.clone();
        if(data.frame.empty()){
            qWarning() << "cloned frame is empty";
            continue;
        }
        m_frameQueue->append(data);
        m_semaphore->release();  //信号量计数器+1，唤醒被阻塞在acquire上的进程
    }
    m_cap.release();  // 显式释放摄像头
}

void CaptureThread::stopCapture()
{
    qDebug() << "run stopCapture" << endl;
    m_stopCapture = true;
}




