#include <QDebug>
#include <QDateTime>
#include "DisplayThread.h"

DisplayThread::DisplayThread(QSemaphore *semaphore, QLinkedList<FrameData> *frameData, QLabel * label)
    :m_semaphore(semaphore)
    ,m_frameQueue(frameData)
    ,m_label(label)
    ,m_stopDisplay(false)
{
    qDebug() << "init displayThread" << endl;
}

DisplayThread::~DisplayThread()
{
    qDebug() << "run delete displayThread" << endl;

}

void DisplayThread::run()
{
    qDebug() << "run displayThread" << endl;
    while(true){
        m_semaphore->acquire();  //信号量-1，当信号量为0的时候就阻塞
        //m_semaphore->tryAcquire();  //也可以使用这个，tryAcquire会尝试获取许可，没获取到也不会阻塞线程
        if(m_stopDisplay){
            qDebug() << "Display thread stopped.";
            break;
        }
        if(!m_frameQueue->isEmpty()){
            FrameData data = m_frameQueue->takeFirst();
            cv::Mat rgbFrame;
            cv::cvtColor(data.frame, rgbFrame, cv::COLOR_BGR2RGB);

            //绘制时间戳
            QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            std::string timestampStr = timestamp.toStdString();  //OpenCV使用的c++的标准库函数
            int fontFace = cv::FONT_HERSHEY_SIMPLEX;
            double fontScale = 1.0;  //文本的基线，用于对齐文本
            int thickness = 2;       //文本的线条宽度
            cv::Scalar color(255, 255, 255);
            int baseline = 0;
            cv::Size textSize = cv::getTextSize(timestampStr, fontFace, fontScale, thickness, &baseline);
            cv::Point textOrg((rgbFrame.cols - textSize.width) / 2, 30);  // 水平居中
            cv::putText(rgbFrame, timestampStr, textOrg, fontFace, fontScale, color, thickness);

            //绘制点
            cv::Point pt(100, 100);
            cv::Scalar pointColor(0, 0, 255);
            int radius = 30;
            int pointThickness = -1;
            cv::circle(rgbFrame, pt, radius, pointColor, pointThickness);

            //绘制线
            cv::Point pt1(50, 50);
            cv::Point pt2(500, 200);
            cv::Scalar lineColor(0, 255, 0);
            int lineThickness = 2;
            cv::line(rgbFrame, pt1, pt2, lineColor, lineThickness);

            //绘制圆圈
            cv::Point center(300, 300);
            int circleRadius = 100;
            cv::Scalar circleColor(0, 255, 255);
            int circleThickness = 2;
            cv::circle(rgbFrame, center, circleRadius, circleColor, circleThickness);
            QImage img(rgbFrame.data, rgbFrame.cols, rgbFrame.rows,
                       rgbFrame.step, QImage::Format_RGB888);
            m_label->setPixmap(QPixmap::fromImage(img));
        }
    }
}

void DisplayThread::stopDisplay()
{
    qDebug() << "run stopDisplay" << endl;
    QMutexLocker locker(&m_mutex);  // 使用 QMutexLocker 确保线程安全
    m_stopDisplay = true;    // 设置停止标志
    m_semaphore->release();  // 先停止capture线程，m_semaphore不会release了，display就一直阻塞在acquire的地方，导致程序不能正常关闭，所以需要释放信号量，让线程能继续执行并检查停止标志
}
