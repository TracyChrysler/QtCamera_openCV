#ifndef DISPLAYTHREAD_H
#define DISPLAYTHREAD_H

#include <QThread>
#include <QSemaphore>
#include <QLinkedList>
#include <QImage>
#include <QLabel>
#include <QMutex>
#include <QWaitCondition>
#include "FrameData.h"

class DisplayThread : public QThread {
    Q_OBJECT
public:
    DisplayThread(QSemaphore * semaphore, QLinkedList<FrameData> * frameQueue, QLabel * label);
    ~DisplayThread();
    void stopDisplay();

protected:
    void run() override;

private:
    QSemaphore * m_semaphore;
    QLinkedList<FrameData> * m_frameQueue;
    QLabel * m_label;
    QLabel *label1;
    QLabel *label2;
    bool m_stopDisplay;
    QMutex m_mutex;
};

#endif // DISPLAYTHREAD_H
