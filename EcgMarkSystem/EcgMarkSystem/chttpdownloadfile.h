#ifndef CHTTPDOWNLOADFILE_H
#define CHTTPDOWNLOADFILE_H


#include <QWidget>

//网络相关头文件
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
//文件相关头文件
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>

class CHttpDownLoadFile : public QWidget
{
    Q_OBJECT

public:
    CHttpDownLoadFile(const QString &url, const QString &fileName, const QString &dir, QWidget *parent);
    ~CHttpDownLoadFile();

    void DownLoadFile();
    void DestroyData();

signals:
    //文件下载结束
    void DownloadFinishedSignal();
    //文件下载进度
    void DownloadProcess(QString, qint64, qint64);

public slots:
    void ReplyNewDataArrived();//响应m_netReply有新的数据到达
    void ReplyFinished();//响应数据接收完成
    void ReplyDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);	//响应文件下载进度

public:
    QNetworkAccessManager *m_netAccessManager;//网络参数

    QNetworkReply *m_netReply;
    QUrl m_urlAdress;//网络地址
    QString m_strFileName;//需要下载的文件名
    QString m_strDir;//文件的存储位置

    QFile *m_file;//下载的文件
    qint64 m_nReceived;//下载文件时，已经接收的文件大小和总共大小
    qint64 m_nTotal;
    bool m_bIsFinished;
};

#endif // CHTTPDOWNLOADFILE_H
