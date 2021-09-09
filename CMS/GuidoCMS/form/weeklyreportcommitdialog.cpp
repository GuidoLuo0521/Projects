#include "weeklyreportcommitdialog.h"
#include "database/cmsdatabase.h"
#include "common/staffinfo.h"
#include "common/commonapi.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>



WeeklyReportCommitDialog::WeeklyReportCommitDialog(QWidget *parent) :
    QWidget(parent),
    m_bChanged(false)
{
    InitLayout();

    m_pNetworkManager = new QNetworkAccessManager(this);
    //QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(m_pNetworkManager,
                                                       SIGNAL(finished(QNetworkReply*)),
                                                       this,
                                                       SLOT(slotRequestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);
}

void WeeklyReportCommitDialog::slotCommit()
{
    if(m_bChanged == false)
    {
        QMessageBox::warning(this, "警告", "未修改！");
        return;
    }

    CStaffInfo * pStaffInfo = StaffInfoSingleton::GetInstance();
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();

    QString strDate = pDB->WDB_Date("yyyy-MM-dd hh:mm:ss");
    QString strWeekNumber = pDB->WDB_WeekNumber();

    QJsonObject jsonObject;
    jsonObject.insert("StaffID", pStaffInfo->GetStaffID());
    jsonObject.insert("Date", strDate);
    jsonObject.insert("WeekNumber", strWeekNumber);
    jsonObject.insert("IP", GetIPPath());
    jsonObject.insert("MAC", GetMacPath());
    jsonObject.insert("Project", m_pProjectName->Text());
    jsonObject.insert("Finished", m_pFinishEdit->Text());
    jsonObject.insert("Plan", m_pPlanEdit->Text());

    //weeknumber-staffid
    QString strNameDate = strDate;
    strNameDate = strNameDate.remove(' ');
    strNameDate = strNameDate.remove(':');
    strNameDate = strNameDate.remove('-');
    QString strFilePath = QString("%1-%2-%3.json").arg(strWeekNumber).arg(pStaffInfo->GetStaffID()).arg(strNameDate);
    jsonObject.insert("FileName", strFilePath);

    QJsonDocument document;
    document.setObject(jsonObject);

#if 0
    QFile file(strFilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(document.toJson());
    file.flush();
    file.close();
#endif

    QString strQuery = QString("INSERT INTO weeklyreport(StaffID, FileName, WeekNumber, CommitDate, CommitIP, CommitMac) "
                               "VALUES('%1', '%2', '%3', '%4', '%5', '%6')")
            .arg(pStaffInfo->GetStaffID()).arg(strFilePath).arg(strWeekNumber)
            .arg(strDate).arg(GetIPPath()).arg(GetMacPath());


    // web 部分放入 webapi 插入
    //pDB->WDB_Exec( strQuery);
    pDB->LDB_Exec( strQuery);

    //QString strWebUrl = "https://localhost:44348/WeeklyReport";
    QString strWebUrl = "http://www.millet.fun/GuidoCMS/WebAPI/WeeklyReport";
    QNetworkRequest request;
    request.setUrl(QUrl(strWebUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString strJson = document.toJson();

    m_pNetworkManager->post(request, strJson.toUtf8());

}

void WeeklyReportCommitDialog::slotRequestFinished(QNetworkReply* reply)
{
    reply->deleteLater();
    QMessageBox::information(this, "提示", "提交成功。");
    m_bChanged = false;
}

void WeeklyReportCommitDialog::slotTextChanged()
{
    m_bChanged = true;
}

void WeeklyReportCommitDialog::slotAccountChanged()
{
    slotClear();
    m_bChanged = false;
}

void WeeklyReportCommitDialog::slotClear()
{
    m_pProjectName->LineEdit()->clear();
    m_pFinishEdit->TextEdit()->clear();
    m_pPlanEdit->TextEdit()->clear();
}

void WeeklyReportCommitDialog::InitLayout()
{
    m_pProjectName = new StanderLineEdit("项目名称：", "");
    m_pFinishEdit = new StanderPlainTextEdit("完成内容：", "");
    m_pPlanEdit = new StanderPlainTextEdit("下周计划：", "");

    m_pFinishEdit->TextEdit()->setFont(QFont("宋体", 12, 12));
    m_pPlanEdit->TextEdit()->setFont(QFont("宋体", 12, 12));

    connect(m_pProjectName->LineEdit(), &QLineEdit::textChanged, this, &WeeklyReportCommitDialog::slotTextChanged);
    connect(m_pPlanEdit->TextEdit(), &QPlainTextEdit::textChanged, this, &WeeklyReportCommitDialog::slotTextChanged);
    connect(m_pFinishEdit->TextEdit(), &QPlainTextEdit::textChanged, this, &WeeklyReportCommitDialog::slotTextChanged);

    QVBoxLayout * pEditLayout = new QVBoxLayout;

    QPushButton * pBtnAdd = new QPushButton("提交");
    QPushButton * pBtnClear = new QPushButton("清除");
    QHBoxLayout * pBtnLayout = new QHBoxLayout;
    pBtnLayout->addStretch();
    pBtnLayout->addWidget(pBtnAdd);
    pBtnLayout->addWidget(pBtnClear);

    connect(pBtnAdd, &QPushButton::clicked, this, &WeeklyReportCommitDialog::slotCommit);
    connect(pBtnClear, &QPushButton::clicked, this, &WeeklyReportCommitDialog::slotClear);

    pEditLayout->addLayout(m_pProjectName->Layout());
    pEditLayout->addLayout(m_pFinishEdit->Layout());
    pEditLayout->addLayout(m_pPlanEdit->Layout());
    pEditLayout->addLayout(pBtnLayout);

    this->setLayout(pEditLayout);
}
