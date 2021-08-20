#ifndef DOWNLOADPROCESS_H
#define DOWNLOADPROCESS_H

#include <QDialog>

//网络相关头文件
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
//文件相关头文件
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>

namespace Ui {
class DownLoadProcess;
}

class DownLoadProcess : public QDialog
{
    Q_OBJECT

public:
    explicit DownLoadProcess(const QString& strUrl, const QString& strSavePath, QDialog *parent = nullptr);
    ~DownLoadProcess();

    void StartRequest(QUrl url);

private:
    void ShowTips(const QString& str);

private slots:
    void HttpFinished();
    void HttpReadyRead();
    void UpdateProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    Ui::DownLoadProcess *ui;

private:
    QNetworkAccessManager * m_pNetworkAccessManager;
    QNetworkReply * m_pReply;
    QUrl m_Url;
    QFile * m_pFile;

    QString m_strUrl;
    QString m_strSavePath;

};

#endif // DOWNLOADPROCESS_H
