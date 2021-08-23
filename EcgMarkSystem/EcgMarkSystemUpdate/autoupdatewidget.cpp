#include "autoupdatewidget.h"
#include "ui_autoupdatewidget.h"

#include <QApplication>
#include <QIcon>
#include <QProcess>
#include <QThread>


const QString AutoUpdateWidget::skm_UpdateExeName = "EcgMarkSystem.exe";
const QString AutoUpdateWidget::skm_UpdateFileName = "update.json";
const QString AutoUpdateWidget::skm_LocalTempUpdateName = "tempupdate.json";
const QString AutoUpdateWidget::skm_UpdateUrl = "http://www.millet.fun/ECG/EcgMarkSystem/update.json";

AutoUpdateWidget::AutoUpdateWidget(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AutoUpdateWidget)
{
    ui->setupUi(this);
    ui->progressBar->setHidden(true);
    ui->btnCancle->setHidden(true);
    ui->btnDownload->setHidden(true);

    setWindowTitle("检查版本");
    setWindowIcon(QIcon(":/icon/Main.ico"));
    setFixedSize(400,300);
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint);

    m_NetManager = new QNetworkAccessManager(this);          //新建QNetworkAccessManager对象
    connect(m_NetManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyJsonFinished(QNetworkReply*)));//关联信号和槽

    QNetworkRequest quest;
    quest.setUrl(QUrl(skm_UpdateUrl)); //包含最新版本软件的下载地址
    quest.setHeader(QNetworkRequest::UserAgentHeader, "RT-Thread ART");
    QNetworkReply *reply = m_NetManager->get(quest);    //发送get网络请求
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));

    connect(ui->btnCancle, &QPushButton::clicked, this, &AutoUpdateWidget::close);
    connect(ui->btnDownload, &QPushButton::clicked, this, &AutoUpdateWidget::slotDownLoadNewExe);

}

AutoUpdateWidget::~AutoUpdateWidget()
{
    delete ui;
}


QString AutoUpdateWidget::GetCurrentVersion()
{
    if(QFile::exists(skm_UpdateFileName) == false)
        return  "V0.0";

    QFile file(skm_UpdateFileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    file.close();

    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        //QMessageBox::information(nullptr, "提示", "本地文件更新文件错误！");
        return "V0.0";
    }
    QJsonObject jsonObject = document.object();
    QJsonObject PulseValue = jsonObject.value("PulseSensor").toObject();
    QString Version = PulseValue.value("LatestVersion").toString();  //V1.0

    return  Version;

}

int AutoUpdateWidget::ParserUpdateJson(const QString& str)
{
    //    QMessageBox msgBox;
    QJsonParseError err_rpt;
    QJsonDocument  root_Doc = QJsonDocument::fromJson(str.toUtf8(),&err_rpt);//字符串格式化为JSON
    if(err_rpt.error != QJsonParseError::NoError)
    {
        //        qDebug() << "root格式错误";
        QMessageBox::critical(nullptr, "检查失败", "服务器地址错误或JSON格式错误!");
        return -1;
    }
    if(root_Doc.isObject())
    {
        QJsonObject  root_Obj = root_Doc.object();   //创建JSON对象，不是字符串
        QJsonObject PulseValue = root_Obj.value("PulseSensor").toObject();
        QString Version = PulseValue.value("LatestVersion").toString();  //V1.0
        QString Url = PulseValue.value("Url").toString();
        QString UpdateTime = PulseValue.value("UpdateTime").toString();
        QString ReleaseNote = PulseValue.value("ReleaseNote").toString();

        QString strCurrent = GetCurrentVersion();
        if(Version > strCurrent)
        {
            QString warningStr = "检测到新版本!\n版本号：" + Version + "\n" +
                                 "更新时间：" + UpdateTime + "\n" +
                                 "更新说明：" + ReleaseNote;
            ui->label->setText(warningStr);

            ui->btnCancle->show();
            ui->btnDownload->show();
            m_strNewExeUrl = Url;
        }
        else
            ui->label->setText("当前已经是最新版本!");
    }
    return 0;
}


void AutoUpdateWidget::slotError(QNetworkReply::NetworkError error)
{
    QMessageBox::warning(this, "警告", QString::number(error));
}

void AutoUpdateWidget::slotDownLoadNewExe()
{
    slotUpdateLocalUpdateFile();
    ui->progressBar->setHidden(false);

    //杀掉正在运行的进程
    QProcess taskkill;
    taskkill.execute("taskkill", QStringList() << "-im" << AutoUpdateWidget::skm_UpdateExeName << "-f");

    CHttpDownLoadFile *pHttpdownload = new CHttpDownLoadFile(
        m_strNewExeUrl,
        AutoUpdateWidget::skm_UpdateExeName,
        QApplication::applicationDirPath(),
        this);

    connect( pHttpdownload, SIGNAL(DownloadProcess(QString, qint64, qint64)), this, SLOT(slotUpdateProcessBar(QString, qint64, qint64)));
    connect( pHttpdownload, SIGNAL(DownloadFinishedSignal()), this, SLOT(slotDownloadExeFinished()));

}

void AutoUpdateWidget::slotUpdateLocalUpdateFile()
{
    if(QFile::exists(skm_LocalTempUpdateName) == false )
        return;

    if(QFile::rename(skm_LocalTempUpdateName, skm_UpdateFileName) == false)
    {
        QMessageBox::critical(this, "错误", "更新本地版本文件错误。");
        return;
    }
}

void AutoUpdateWidget::replyJsonFinished(QNetworkReply *reply)
{

    QFile file(skm_LocalTempUpdateName);
    if(file.open(QIODevice::Text | QIODevice::WriteOnly) == false)
    {
        QMessageBox::critical(this, "错误", "创建临时文件更新错误。");
        return;
    }

    QByteArray array = reply->readAll();
    file.write(array);
    file.flush();
    file.close();

    ParserUpdateJson(array);
}

void AutoUpdateWidget::slotDownloadExeFinished()
{
    QMessageBox::information(this, "提示", "更新完成。");
    QFile::remove(skm_LocalTempUpdateName);

    QProcess process(this);
    process.startDetached(AutoUpdateWidget::skm_UpdateExeName);

    accept();
}

void AutoUpdateWidget::slotUpdateProcessBar(QString str, qint64 rec, qint64 tol)
{
    ui->progressBar->setValue(double(rec) / double(tol) * 100);
}

