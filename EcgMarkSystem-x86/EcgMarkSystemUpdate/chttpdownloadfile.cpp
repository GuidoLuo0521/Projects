#include "chttpdownloadfile.h"

CHttpDownLoadFile::CHttpDownLoadFile(const QString &url, const QString &fileName, const QString &dir, QWidget *parent)
    : QWidget(parent),
    m_urlAdress(url),
    m_strFileName(fileName),
    m_strDir(dir),
    m_bIsFinished(false)
{
    m_netAccessManager = new QNetworkAccessManager(this);

    DownLoadFile();
}

CHttpDownLoadFile::~CHttpDownLoadFile()
{
}

void CHttpDownLoadFile::DownLoadFile()
{
    m_bIsFinished = false;
    QNetworkRequest request(m_urlAdress);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    m_netReply = m_netAccessManager->get(request);

    connect(m_netReply, SIGNAL(readyRead()), this, SLOT(ReplyNewDataArrived()));//当有新数据到达时就会触发此信号
    connect(m_netReply, SIGNAL(finished()), this, SLOT(ReplyFinished()));//完成数据接收后发送此信号
    connect(m_netReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(ReplyError(QNetworkReply::NetworkError)));//出现错误时发送此信号;
    connect(m_netReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(ReplyDownloadProgress(qint64, qint64)));//用来提示文件下载进度

    if (m_strFileName.isEmpty())//文件名
    {
        QFileInfo fileInfo(m_urlAdress.path());
        m_strFileName = fileInfo.fileName();

    }
    if (!m_strDir.isEmpty())//文件夹
    {
        QDir directory(m_strDir);
        if (!directory.exists())//没有此文件夹，则创建
        {
            directory.mkpath(m_strDir);
        }
        m_strFileName = m_strDir + "/" + m_strFileName;//添加/是为了防止用户名没有加/，因为对于文件夹来说两个/都会当成一个/
    }

    if (QFile::exists(m_strFileName))//如果文件已经存在，那么删除
    {
        QFile::remove(m_strFileName);
    }

    m_file = new QFile(m_strFileName);
    if (!m_file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        m_file->close();
        delete m_file;
        m_file = NULL;

        return;
    }
}

void CHttpDownLoadFile::DestroyData()
{
    m_netAccessManager->deleteLater();
    m_netReply->deleteLater();
    m_file->close();
    m_file->deleteLater();
}

void CHttpDownLoadFile::ReplyNewDataArrived()//响应m_netReply有新的数据到达
{
    if (m_file)
    {        
        // 写文件-形式为追加
        QFile file(m_strFileName);
        if (file.open(QIODevice::OpenModeFlag::Append))
            file.write(m_netReply->readAll());
        file.close();
    }
    else
    {
        qDebug() << m_netReply->readAll();
    }
}

void CHttpDownLoadFile::ReplyFinished()//响应数据接收完成
{
    m_bIsFinished = true;
    m_netAccessManager->deleteLater();
    m_netReply->deleteLater();
    m_file->close();
    m_file->deleteLater();

    emit DownloadFinishedSignal();
}

void CHttpDownLoadFile::ReplyDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    QFileInfo fileInfo(m_urlAdress.path());
    QString strFileName = fileInfo.fileName();
    emit DownloadProcess(strFileName, bytesReceived, bytesTotal);
}
