#include "weeklyreporthistorydialog.h"

#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "common/staffinfo.h"

WeeklyReportHistoryDialog::WeeklyReportHistoryDialog(QWidget *parent) : QWidget(parent)
{
    InitLayout();
    m_pNetManager = new QNetworkAccessManager(this);
}

void WeeklyReportHistoryDialog::InitLayout()
{
    QVBoxLayout * pHistoryLayout = new QVBoxLayout;
    m_pTableView = new QTableView;
    QFont fnt = m_pTableView->font();
    fnt.setPointSize(12);
    m_pTableView->setFont(fnt);
    m_pTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_pTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);



    m_pStandardItemModel = new QStandardItemModel;

    int nIndex = 0;
    m_pStandardItemModel->setColumnCount(6);
    m_pStandardItemModel->setHeaderData(nIndex++, Qt::Horizontal, "提交编号");
    m_pStandardItemModel->setHeaderData(nIndex++, Qt::Horizontal, "提交周数");
    m_pStandardItemModel->setHeaderData(nIndex++, Qt::Horizontal, "项目名称");
    m_pStandardItemModel->setHeaderData(nIndex++, Qt::Horizontal, "完成内容");
    m_pStandardItemModel->setHeaderData(nIndex++, Qt::Horizontal, "下周计划");
    m_pStandardItemModel->setHeaderData(nIndex++, Qt::Horizontal, "提交时间");


    //AddDate();

    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableView->setItemDelegateForColumn(0, readOnlyDelegate);
    m_pTableView->setItemDelegateForColumn(1, readOnlyDelegate);
    m_pTableView->setItemDelegateForColumn(2, readOnlyDelegate);
    m_pTableView->setItemDelegateForColumn(3, readOnlyDelegate);
    m_pTableView->setItemDelegateForColumn(4, readOnlyDelegate);

    //TextEditDelegate * pTextEditDelegateFinish = new TextEditDelegate(TextEditDelegate::TT_PlainText ,this);
    //m_pTableView->setItemDelegateForColumn(2, pTextEditDelegateFinish);
    //
    //TextEditDelegate * pTextEditDelegatePlain = new TextEditDelegate(TextEditDelegate::TT_PlainText ,this);
    //m_pTableView->setItemDelegateForColumn(3, pTextEditDelegatePlain);


    //TextEditDelegate * pTextEditDelegatePlain = new TextEditDelegate(TextEditDelegate::TT_PlainText ,this);
    //m_pTableView->setItemDelegateForColumn(2, pTextEditDelegatePlain);
    //m_pTableView->setItemDelegateForColumn(3, pTextEditDelegatePlain);

    m_pTableView->setModel(m_pStandardItemModel);

    pHistoryLayout->addWidget(m_pTableView);
    this->setLayout(pHistoryLayout);
}

void WeeklyReportHistoryDialog::slotGetDate()
{
    int nRowCount = m_pStandardItemModel->rowCount();
    m_pStandardItemModel->removeRows(0, nRowCount);

    CStaffInfo * pStaffInfo = StaffInfoSingleton::GetInstance();

    // 构建及发送请求
    QString strWebUrl = "http://www.millet.fun/GuidoCMS/WebAPI/WeeklyReport";
    //QString strWebUrl = "https://localhost:44348/WeeklyReport";
    QString strUrl = QString("%1/?staffid=%2").arg(strWebUrl).arg(pStaffInfo->GetStaffID());
    QNetworkRequest request;
    request.setUrl(QUrl(strUrl));
    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *pReply = m_pNetManager->get(request);
    // 开启一个局部的事件循环，等待页面响应结束
    QEventLoop eventLoop;
    QObject::connect(m_pNetManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    // 获取网页Body中的内容
    QString strJson = pReply->readAll();
    //qDebug() << strJson;

    QJsonDocument doc = QJsonDocument::fromJson(strJson.toUtf8());
    QJsonObject obj = doc.object();

    QString str = "", key = "";
    int nRow = 0, nColumn = 0;
    QStringList list =  obj.keys();
    foreach (key, list)
    {
        if(obj[key].isObject())
        {
            nColumn = 0;

            QJsonObject objval =  obj[key].toObject();
            str = QString("%1").arg(key);
            m_pStandardItemModel->setItem(nRow, nColumn++, new QStandardItem(str));
            str = QString("%1").arg(objval["WeekNumber"].toString());
            m_pStandardItemModel->setItem(nRow, nColumn++, new QStandardItem(str));
            str = QString("%1").arg(objval["Project"].toString());
            m_pStandardItemModel->setItem(nRow, nColumn++, new QStandardItem(str));
            str = QString("%1").arg(objval["Finished"].toString());
            m_pStandardItemModel->setItem(nRow, nColumn++, new QStandardItem(str));
            str = QString("%1").arg(objval["Plan"].toString());
            m_pStandardItemModel->setItem(nRow, nColumn++, new QStandardItem(str));
            str = QString("%1").arg(objval["CommitDate"].toString());
            m_pStandardItemModel->setItem(nRow, nColumn++, new QStandardItem(str));
        }
        nRow++;
    }

    pReply->deleteLater();
}

void WeeklyReportHistoryDialog::slotAccountChanged()
{
    slotGetDate();
}
