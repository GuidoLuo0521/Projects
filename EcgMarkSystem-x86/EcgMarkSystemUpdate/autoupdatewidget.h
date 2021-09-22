#ifndef AUTOUPDATEWIDGET_H
#define AUTOUPDATEWIDGET_H

#include <QUrl>
#include <QDesktopServices>
//网络相关头文件
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
//JSON相关头文件
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTime>
#include <QProgressBar>
#include <QTextCodec>
#include "chttpdownloadfile.h"
#include <QWidget>

namespace Ui {
class AutoUpdateWidget;
}

class AutoUpdateWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AutoUpdateWidget(QDialog *parent = nullptr);
    ~AutoUpdateWidget();

private:

    int ParseJson(const QString &str);      //解析数据函数的声明

signals:
    void signalDownLoadNewFile(QString url);

private:
    QString GetCurrentVersion();
    int ParserUpdateJson(const QString& str);

private slots:
    void slotError(QNetworkReply::NetworkError);

    void slotCancleDownLoadNewExe();
    void slotDownLoadNewExe();
    void replyJsonFinished(QNetworkReply *reply);   //json 文件下载结束

    void slotDownloadExeFinished();   //json 文件下载结束

    void slotUpdateProcessBar(QString, qint64, qint64);

private:
    Ui::AutoUpdateWidget *ui;

private:
    QNetworkAccessManager *	m_NetManager;     //定义网络请求对象
    QNetworkAccessManager *	m_NetManagerDown;     //定义网络请求对象
    QNetworkReply *			m_pReply;
    QUrl					m_url;
    QString					m_strUrl;
    QString					m_strFileName;

    QString m_strNewExeUrl;

    CHttpDownLoadFile * m_pHttpdownload;


    static const QString skm_UpdateExeName;
    static const QString skm_UpdateFileName;
    static const QString skm_UpdateUrl;
    static const QString skm_LocalTempUpdateName;

};

#endif // AUTOUPDATEWIDGET_H
