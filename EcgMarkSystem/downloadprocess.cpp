#include "downloadprocess.h"
#include "ui_downloadprocess.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QHttpPart>

DownLoadProcess::DownLoadProcess(const QString& strUrl, const QString& strSavePath, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::DownLoadProcess),
    m_strUrl(strUrl),
    m_strSavePath(strSavePath)
{
    ui->setupUi(this);

    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint);
    m_pNetworkAccessManager = new QNetworkAccessManager(this);

    m_pFile = new QFile(strSavePath);
    if(m_pFile->open(QIODevice::WriteOnly) == false)
    {
        QMessageBox::critical(this, "错误", m_pFile->errorString());
        delete  m_pFile;
        m_pFile = nullptr;

        close();
    }

    ShowTips("正在下载：" + strUrl);
    StartRequest(QUrl(m_Url));
}

DownLoadProcess::~DownLoadProcess()
{
    delete ui;
}

void DownLoadProcess::StartRequest(QUrl url)
{
    m_pReply = m_pNetworkAccessManager->get(QNetworkRequest(url));
    connect( m_pReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(UpdateProgress(qint64, qint64)));
    connect( m_pReply, SIGNAL(readyRead()), this, SLOT(HttpReadyRead()));
    connect( m_pReply, SIGNAL(finished()), this, SLOT(HttpFinished()));
}

void DownLoadProcess::ShowTips(const QString &str)
{
    ui->label->setText(str);
}

void DownLoadProcess::HttpFinished()
{
    m_pReply->deleteLater();
    m_pReply = nullptr;

    m_pFile->flush();
    m_pFile->close();

    delete m_pFile;
    m_pFile = nullptr;

    close();
}

void DownLoadProcess::HttpReadyRead()
{
    if( m_pFile )
    {
        m_pFile->write(m_pReply->readAll());
    }
}

void DownLoadProcess::UpdateProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setValue(bytesReceived);
}

