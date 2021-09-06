#include "weeklyreporthistorydialog.h"

WeeklyReportHistoryDialog::WeeklyReportHistoryDialog(QWidget *parent) : QWidget(parent)
{
    InitLayout();
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

    m_pStandardItemModel->setColumnCount(4);
    m_pStandardItemModel->setHeaderData(0, Qt::Horizontal, "提交时间");
    m_pStandardItemModel->setHeaderData(1, Qt::Horizontal, "项目名称");
    m_pStandardItemModel->setHeaderData(2, Qt::Horizontal, "完成内容");
    m_pStandardItemModel->setHeaderData(3, Qt::Horizontal, "下周计划");
    //m_pStandardItemModel->setHeaderData(4, Qt::Horizontal, "修改内容");

    AddDate();

    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableView->setItemDelegateForColumn(0, readOnlyDelegate);
    m_pTableView->setItemDelegateForColumn(1, readOnlyDelegate);
    m_pTableView->setItemDelegateForColumn(2, readOnlyDelegate);
    m_pTableView->setItemDelegateForColumn(3, readOnlyDelegate);

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

void WeeklyReportHistoryDialog::AddDate()
{
    for(int i = 0; i < 20; ++i)
    {
        m_pStandardItemModel->setItem(i, 0, new QStandardItem(QString("2021-09-0%1").arg(i) ));
        m_pStandardItemModel->setItem(i, 1, new QStandardItem("诊断算法\n心博分类\n心电算法"));
        m_pStandardItemModel->setItem(i, 2, new QStandardItem("1、完善心电算法，对T波高耸的数据进行分析，目前 T波高耸数据已经能正常检测。\n"
                                                              "2、完善心博分类算法，测试手表和手环数据，因为我的数据较为正常，因此后面找更多人测试。\n"
                                                              "3、增加心博指定心博模板的算法。目前已经编码完成。\n"
                                                              "4、查看任开文的源码，了解他们的自动诊断算法。\n"));

        m_pStandardItemModel->setItem(i, 3, new QStandardItem("1、了解任开文的心博分类算法，整理成文档。\n"
                                                              "2、分析端测试手表和手环的数据。\n"
                                                              "3、跟进分析端的使用和修改。\n"));
    }
}
