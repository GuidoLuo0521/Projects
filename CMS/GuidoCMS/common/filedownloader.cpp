#include "filedownloader.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>

FileDownloader::FileDownloader(QObject *parent) :
    QObject(parent)
{
    connect( &m_WebCtrl, SIGNAL (finished(QNetworkReply*)), this, SLOT (fileDownloaded(QNetworkReply*)) );
}

FileDownloader::~FileDownloader()
{

}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    //  QString strUrl = pReply->url().toString();
    QByteArray data = pReply->readAll();

    bool bSuccess = false;

    if(data != "")
    {
        QFileInfo fileinfo(m_strFilePath);
        QDir dir = fileinfo.dir();

        if(dir.exists() == false)
        {
            QString str = dir.path();
            qDebug() << str;
            dir.mkpath( str );
        }

        QFile file(m_strFilePath);
        file.open(QIODevice::WriteOnly);
        file.write(data);
        file.flush();
        file.close();

        bSuccess = true;
    }

    //emit a signal
    pReply->deleteLater();
    emit signalDownLoaded(m_strFilePath, bSuccess);
}

void FileDownloader::DownLoadFile(QString imageUrl, QString filepath)
{
    QUrl url = QUrl(imageUrl);
    m_strFilePath = filepath;

    QNetworkRequest request(url);
    m_WebCtrl.get(request);
}
