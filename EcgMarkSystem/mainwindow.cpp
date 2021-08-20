#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chttpdownloadfile.h"
#include "autoupdatewidget.h"

#include <QSplitter>
#include <QHBoxLayout>
#include <QEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_pModel(nullptr)
    , m_pSaveAction(nullptr)
    , m_pSetDirAction(nullptr)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/Main.ico"));

    InitLayout();
    BindSignalSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if( watched == m_pCustomPlot )
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                m_bMousePressing = true;

                double x = mouseEvent->pos().x();
                double y = mouseEvent->pos().y();
                double x_ = m_pCustomPlot->xAxis->pixelToCoord(x);
                double y_ = m_pCustomPlot->yAxis->pixelToCoord(y);
                int xint = int(x_+0.5);

                m_dMousePosX = x_;
                m_dMousePosY = y_;

                HitMarkPoint hitpoint = HitMark(xint, y_);
                if(hitpoint.type < MarkPointType::MARK_POINT_COUNT)
                {
                    m_HitMarkPoint = hitpoint;
                    ShowSelectdType();
                    SetCustomplotSelectdData(xint, m_CustomplotEcgData[1][ xint ]);

                    return true;
                }
            }
        }
        else if( event->type() == QEvent::MouseMove)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            double x = mouseEvent->pos().x();
            double y = mouseEvent->pos().y();
            double x_ = m_pCustomPlot->xAxis->pixelToCoord(x);
            double y_ = m_pCustomPlot->yAxis->pixelToCoord(y);
            int xint = int(x_+0.5);

            QString str = QString("(x:%1,y:%2)").arg(QString::number(xint,10,3))
                              .arg(QString::number(y_,10,3));
            m_pStatusAxisPosLable->setText(str);

            m_dMousePosX = x_;
            m_dMousePosY = y_;

            if(m_HitMarkPoint.type < MARK_POINT_COUNT)
            {
                if( m_bMousePressing)
                {
                    m_HitMarkPoint.nNewPos = xint;
                    SetCustomplotSelectdData(xint, m_CustomplotEcgData[1][ xint ]);
                }

                return true;
            }
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            if(m_bMousePressing)
            {
                m_bMousePressing = false;

                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                double x = mouseEvent->pos().x();
                double y = mouseEvent->pos().y();
                double x_ = m_pCustomPlot->xAxis->pixelToCoord(x);
                double y_ = m_pCustomPlot->yAxis->pixelToCoord(y);
                int xint = int(x_+0.5);

                m_dMousePosX = x_;
                m_dMousePosY = y_;

                if(m_HitMarkPoint.type < MARK_POINT_COUNT)
                {
                    m_HitMarkPoint.nNewPos = xint;
                    SetCustomplotSelectdData(xint, m_CustomplotEcgData[1][ xint ]);

                    return true;
                }
            }
        }
        else if(event->type() == QEvent::KeyRelease)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if( keyEvent->key() == Qt::Key::Key_Delete)
            {
                if(m_HitMarkPoint.type < MARK_POINT_COUNT)
                {
                    slotUpdataHitToMarkPointData(false);
                    ClearHitMarkDate();
                    SetCustomplotSelectdData(-1, -1);
                    ShowSelectdType();
                    return true;
                }
            }
            else if(keyEvent->key() == Qt::Key_Return)
            {
                if(m_HitMarkPoint.type < MARK_POINT_COUNT)
                {
                    slotUpdataHitToMarkPointData(true);
                    ClearHitMarkDate();
                    SetCustomplotSelectdData(-1, -1);
                    ShowSelectdType();
                    return true;
                }
            }
            else if(keyEvent->key() == Qt::Key_Escape)
            {
                ClearHitMarkDate();
                SetCustomplotSelectdData(-1, -1);
                ShowSelectdType();
                return true;
            }
            else if(keyEvent->key() == Qt::Key_Q) { AddMarkPoint(MarkPointType::PS); return true; }
            else if(keyEvent->key() == Qt::Key_W) { AddMarkPoint(MarkPointType::P); return true; }
            else if(keyEvent->key() == Qt::Key_E) { AddMarkPoint(MarkPointType::PE); return true; }
            else if(keyEvent->key() == Qt::Key_A) { AddMarkPoint(MarkPointType::Q); return true; }
            else if(keyEvent->key() == Qt::Key_S) { AddMarkPoint(MarkPointType::R); return true; }
            else if(keyEvent->key() == Qt::Key_D) { AddMarkPoint(MarkPointType::S); return true; }
            else if(keyEvent->key() == Qt::Key_Z) { AddMarkPoint(MarkPointType::TS); return true; }
            else if(keyEvent->key() == Qt::Key_X) { AddMarkPoint(MarkPointType::T); return true; }
            else if(keyEvent->key() == Qt::Key_C) { AddMarkPoint(MarkPointType::TE); return true; }
            else if(keyEvent->key() == Qt::Key_Home) { slotUpdataCustomplotEcgData(); return  true; }
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::slotCurrentDirChanged()
{
    QString strDir = QFileDialog::getExistingDirectory(this, "选择文件夹", "F:/QRS_lable_data");
    if(strDir.isEmpty())
        return;

    m_strCurrentDir = strDir;
    emit signalCurrentDirChanged();
}

void MainWindow::slotCurrentFileChanged()
{
    slotOpenCurrentFile();
}

void MainWindow::slotFillFileList()
{
    QDir dir(m_strCurrentDir);
    QFileInfoList list = dir.entryInfoList();

    m_pModel->clear();

    for( int i = 0; i < list.size(); ++i )
    {
        QString str = list[i].fileName();
        if(str != "." && str != "..")
        {
            QStandardItem *item = new QStandardItem(list[i].fileName());
            m_pModel->appendRow(item);
        }
    }

    m_pListView->setModel(m_pModel);

    connect(m_pListView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &MainWindow::slotListViewSelectdChanged);
}

void MainWindow::slotListViewSelectChanged(QModelIndex index)
{
    m_strCurrentFile = index.data().toString();
    emit signalCurrentFileChanged();
}

void MainWindow::slotListViewSelectdChanged(const QModelIndex &current, const QModelIndex &previous)
{
    slotListViewSelectChanged(current);
}

void MainWindow::slotOpenCurrentFile()
{
    QString strFilePath = m_strCurrentDir + '/' + m_strCurrentFile;

    if(QFile::exists(strFilePath) == false)
        return;

    ClearLastFile();

    setWindowTitle(m_strCurrentFile);

    //ShowMessage(strFilePath);

    QFile file(strFilePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    file.close();

    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        ShowStatusTips("解析json文件错误！");

        m_strCurrentFile = "";
        this->setWindowTitle(m_strCurrentFile);
        return;
    }
    QJsonObject jsonObject = document.object();
    InsertEcgDataList(jsonObject["data"].toArray());

    for( int i = 0; i < g_listMarkPointTypeNameInJson.size(); ++i )
    {
        QJsonArray jsonarray = jsonObject[g_listMarkPointTypeNameInJson[i]].toArray();
        InsertMarkPointList((MarkPointType)i, jsonarray);
    }

    emit signalUpdataCustomplotEcgData();
    emit signalUpdataCustomplotMarkData();
    emit signalUpdataCustomplotSelectedData();
}


static void InsertToJsonArray(QJsonObject& jsonObject, const QString& name, const MarkPointVect& vMarkPoint)
{
    QJsonArray jsonarray;
    int nSize = vMarkPoint.size();
    for( int i = 0; i < nSize; ++i )
    {
        jsonarray.push_back(vMarkPoint[i].nPos);
    }
    jsonObject.insert(name, jsonarray);
}

void MainWindow::slotSaveCurrentFile()
{
    if(m_vectMarkPoint[(int)MarkPointType::PS].size() != m_vectMarkPoint[(int)MarkPointType::PE].size())
    {
        QMessageBox::critical(this, "警告", "PS PE 个数不相等");
        return;
    }
    if(m_vectMarkPoint[(int)MarkPointType::Q].size() != m_vectMarkPoint[(int)MarkPointType::S].size())
    {
        QMessageBox::critical(this, "警告", "Q S 个数不相等");
        return;
    }
    if(m_vectMarkPoint[(int)MarkPointType::TS].size() != m_vectMarkPoint[(int)MarkPointType::TE].size())
    {
        QMessageBox::critical(this, "警告", "TS TE 个数不相等");
        return;
    }

    if(m_CustomplotEcgData->size() <= 0)
    {
        ShowStatusTips("未打开文件");
        return;
    }

    QFileInfo fileInfo(m_strCurrentDir + "/" + m_strCurrentFile);
    QString strFilePath = m_strCurrentDir + "/" + fileInfo.baseName() + "_副本." + fileInfo.suffix();

    QString str;
    QJsonObject jsonObject;
    {
        QJsonArray jsonarray;
        int nSize = m_CustomplotEcgData->size();
        for( int i = 0; i < nSize; ++i )
        {
            jsonarray.push_back(m_CustomplotEcgData[1][i]);
        }
        jsonObject.insert("data", jsonarray);
    }
    for( int i = 0; i < g_listMarkPointTypeNameInJson.size(); ++i )
    {
        InsertToJsonArray(jsonObject, g_listMarkPointTypeNameInJson[i], m_vectMarkPoint[i]);
    }

    QJsonDocument document;
    document.setObject(jsonObject);

    QFile file(strFilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(document.toJson());
    file.flush();

    file.close();

    ShowStatusTips("文件已保存：" + strFilePath);

    emit signalCurrentDirChanged();
    emit signalCurrentFileChanged();
}

void MainWindow::slotCheckUpdate()
{
    AutoUpdateWidget autoupdate;
    if(autoupdate.exec() == QDialog::Accepted)
    {
        QMessageBox::information(this, "提示", "请用浏览器中下载文件替换目录中Exe，然后重启软件。");
        close();
    }
}

void MainWindow::slotUpdataCustomplotMarkData()
{
    m_pCustomPlot->graph(GT_MARK_POINT_P)->setData(m_CustomplotPMarkData[0], m_CustomplotPMarkData[1]);
    m_pCustomPlot->graph(GT_MARK_POINT_R)->setData(m_CustomplotRMarkData[0], m_CustomplotRMarkData[1]);
    m_pCustomPlot->graph(GT_MARK_POINT_T)->setData(m_CustomplotTMarkData[0], m_CustomplotTMarkData[1]);

    ShowMarkCount();

    emit signalRePaint();
}

void MainWindow::slotUpdataHitToMarkPointData(bool insert)
{
    if( m_HitMarkPoint.type < MARK_POINT_COUNT )
    {
        if(m_HitMarkPoint.nIndex >= 0 && m_HitMarkPoint.nIndex < m_vectMarkPoint[m_HitMarkPoint.type].size())
            m_vectMarkPoint[m_HitMarkPoint.type].erase(m_vectMarkPoint[m_HitMarkPoint.type].begin() + m_HitMarkPoint.nIndex);

        if(insert && m_HitMarkPoint.nNewPos < m_CustomplotEcgData->size() )
        {
            m_vectMarkPoint[m_HitMarkPoint.type].push_back(m_HitMarkPoint.nNewPos);
            std::sort(m_vectMarkPoint[m_HitMarkPoint.type].begin(), m_vectMarkPoint[m_HitMarkPoint.type].end(), MarkPointStructure::CompMarkPoint);
        }

        emit signalInsertMarkPoint();
    }
}

void MainWindow::slotUpdataCustomplotSelectedData()
{
    m_pCustomPlot->graph(GT_SELECTED_MARK)->setData(m_CustomplotSelectdData[0], m_CustomplotSelectdData[1]);
    emit signalRePaint();
}

void MainWindow::slotUpdataCustomplotEcgData()
{
    m_pCustomPlot->graph(GT_ECG_DATA)->setData(m_CustomplotEcgData[0], m_CustomplotEcgData[1]);
    m_pCustomPlot->xAxis->setRange(0, m_CustomplotEcgData[0].size() + 100);           // 设置x轴的范围为(-1,1)
    m_pCustomPlot->yAxis->setRange(m_MinVal_Y * 3, m_MaxVal_Y * 3);

    emit signalRePaint();
}

void MainWindow::slotRePaint()
{
    m_pCustomPlot->replot();
}

void MainWindow::slotInsertCustomplotMarkData()
{
    ClearCustomplotMarkData();

    for( int i = 0; i < MARK_POINT_COUNT; ++i)
    {
        for(int j = 0; j < m_vectMarkPoint[i].size(); ++j)
        {
            int x = m_vectMarkPoint[i][j].nPos;
            double y = m_CustomplotEcgData[1][x];

            if(i <= MarkPointType::PE)
            {
                m_CustomplotPMarkData[0].push_back(x);
                m_CustomplotPMarkData[1].push_back(y);
            }
            else if( i <= MarkPointType::S )
            {
                m_CustomplotRMarkData[0].push_back(x);
                m_CustomplotRMarkData[1].push_back(y);
            }
            else if( i <= MarkPointType::TE )
            {
                m_CustomplotTMarkData[0].push_back(x);
                m_CustomplotTMarkData[1].push_back(y);
            }
        }
    }

    emit signalUpdataCustomplotMarkData();
}

void MainWindow::ClearLastFile()
{
    m_MaxVal_Y = -10000,
    m_MinVal_Y =  10000;

    ClearMarkPointVect();
    ClearCustomplotEcgData();
    ClearCustomplotMarkData();
    ClearCustomplotSelectdData();

    ClearHitMarkDate();
}

void MainWindow::ClearHitMarkDate()
{
    m_HitMarkPoint.Clear();
}

void MainWindow::ClearMarkPointVect()
{
    for( int i = 0; i < MARK_POINT_COUNT; ++i)
    {
        m_vectMarkPoint[i].clear();
    }
}

void MainWindow::ClearCustomplotEcgData()
{
    m_CustomplotEcgData[0].clear();
    m_CustomplotEcgData[1].clear();
}

void MainWindow::ClearCustomplotMarkData()
{
    m_CustomplotPMarkData[0].clear();
    m_CustomplotPMarkData[1].clear();

    m_CustomplotRMarkData[0].clear();
    m_CustomplotRMarkData[1].clear();

    m_CustomplotTMarkData[0].clear();
    m_CustomplotTMarkData[1].clear();
}

void MainWindow::ClearCustomplotSelectdData()
{
    m_CustomplotSelectdData[0].clear();
    m_CustomplotSelectdData[1].clear();
}

void MainWindow::InsertMarkPointList(MarkPointType marktype, const QJsonArray& jsonarr)
{
    MarkPointVect& list = m_vectMarkPoint[(int)marktype];
    list.clear();

    for( int i = 0, nVal = 0; i < jsonarr.size(); ++i )
    {
        nVal = jsonarr[i].toInt();
        MarkPointStructure mark(nVal);
        list.push_back(mark);
    }

    std::sort(list.begin(), list.end(), MarkPointStructure::CompMarkPoint);
    emit signalInsertMarkPoint();
}

void MainWindow::InsertEcgDataList(const QJsonArray &jsonarr)
{
    double dVal = 0.0;
    for( int i = 0; i < jsonarr.size(); ++i )
    {
        dVal = jsonarr[i].toDouble();
        m_CustomplotEcgData[0].push_back(i);
        m_CustomplotEcgData[1].push_back(dVal);

        if(dVal > m_MaxVal_Y)
            m_MaxVal_Y = dVal;
        if(dVal < m_MinVal_Y)
            m_MinVal_Y = dVal;
    }
}

void MainWindow::InitLayout()
{
    QMenuBar * pMenuBar = this->menuBar();

    m_pSetDirAction = new QAction("路径");
    pMenuBar->addAction(m_pSetDirAction);

    m_pSaveAction = new QAction("保存");
    pMenuBar->addAction(m_pSaveAction);

    QMenu * pHelpMenu = new QMenu("帮助");
    m_pUpdateAction = new QAction("检查更新");
    pHelpMenu->addAction(m_pUpdateAction);
    pMenuBar->addMenu(pHelpMenu);


    // 文件列表
    QSplitter * pMainSplitter = new QSplitter(Qt::Horizontal);
    m_pListView = new QListView;
    m_pListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pMainSplitter->addWidget(m_pListView);
    m_pListView->installEventFilter(this);

    // 绘图
    InitCustomplot();
    pMainSplitter->addWidget(m_pCustomPlot);

    pMainSplitter->setStretchFactor(0, 1);
    pMainSplitter->setStretchFactor(1, 15);

    this->setCentralWidget(pMainSplitter);

    m_pModel = new QStandardItemModel;

    //
    QStatusBar * pStatusBar = this->statusBar();

    m_pStatusTipsLable = new QLabel("");
    pStatusBar->addWidget(m_pStatusTipsLable);

    m_pStatusMarkCountLable = new QLabel("");
    pStatusBar->addPermanentWidget(m_pStatusMarkCountLable);

    m_pStatusSelectdLable = new QLabel("选中点:");
    pStatusBar->addPermanentWidget(m_pStatusSelectdLable);

    m_pStatusAxisPosLable = new QLabel("坐标:(0, 0)");
    pStatusBar->addPermanentWidget(m_pStatusAxisPosLable);

}

void MainWindow::InitCustomplot()
{
    m_pCustomPlot = new QCustomPlot;
    m_pCustomPlot->xAxis->setLabel("x");             // 设置x轴的标签
    m_pCustomPlot->yAxis->setLabel("y");
    m_pCustomPlot->legend->setVisible(true);         // 显示图例

    m_pCustomPlot->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    m_pCustomPlot->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    m_pCustomPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);

    m_pCustomPlot->setInteraction(QCP::iRangeDrag, true); //鼠标单击拖动
    m_pCustomPlot->setInteraction(QCP::iRangeZoom, true); //滚轮滑动缩放

    QSharedPointer<QCPAxisTickerFixed> intTicker( new QCPAxisTickerFixed );
    //设置刻度之间的步长为1
    intTicker->setTickStep(1);
    //设置缩放策略
    intTicker->setScaleStrategy( QCPAxisTickerFixed::ssMultiples );
    //应用自定义整形ticker
    m_pCustomPlot->xAxis->setTicker( intTicker ) ;

    QSharedPointer<QCPAxisTickerFixed> doubleTicker( new QCPAxisTickerFixed );
    doubleTicker->setTickStep(0.1);
    doubleTicker->setScaleStrategy( QCPAxisTickerFixed::ssMultiples );
    m_pCustomPlot->yAxis->setTicker( doubleTicker ) ;

    /***************************************************************************************/
    // 心电数据
    m_pCustomPlot->addGraph();
    m_pCustomPlot->graph(GT_ECG_DATA)->setName("ECG");   // 设置曲线图的名字

    QPen drawPen;
    drawPen.setWidth(5);
    /***************************************************************************************/
    // 标记点 P
    m_pCustomPlot->addGraph();
    m_pCustomPlot->graph(GT_MARK_POINT_P)->setName("Ps P Pe");
    m_pCustomPlot->graph(GT_MARK_POINT_P)->setLineStyle(QCPGraph::lsNone);
    m_pCustomPlot->graph(GT_MARK_POINT_P)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    drawPen.setColor(QColor::fromRgb(255, 0, 0, 180));
    m_pCustomPlot->graph(GT_MARK_POINT_P)->setPen(drawPen);
    /***************************************************************************************/
    // 标记点 QRS
    m_pCustomPlot->addGraph();
    m_pCustomPlot->graph(GT_MARK_POINT_R)->setName("QRS");
    m_pCustomPlot->graph(GT_MARK_POINT_R)->setLineStyle(QCPGraph::lsNone);
    m_pCustomPlot->graph(GT_MARK_POINT_R)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    drawPen.setColor(QColor::fromRgb(0, 255, 0, 180));
    m_pCustomPlot->graph(GT_MARK_POINT_R)->setPen(drawPen);
    /***************************************************************************************/
    // 标记点 T
    m_pCustomPlot->addGraph();
    m_pCustomPlot->graph(GT_MARK_POINT_T)->setName("TS T Te");
    m_pCustomPlot->graph(GT_MARK_POINT_T)->setLineStyle(QCPGraph::lsNone);
    m_pCustomPlot->graph(GT_MARK_POINT_T)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    drawPen.setColor(QColor::fromRgb(0, 0, 255, 180));
    m_pCustomPlot->graph(GT_MARK_POINT_T)->setPen(drawPen);

    /***************************************************************************************/
    // 选中点
    m_pCustomPlot->addGraph();
    m_pCustomPlot->graph(GT_SELECTED_MARK)->setName("Select");
    m_pCustomPlot->graph(GT_SELECTED_MARK)->setLineStyle(QCPGraph::lsNone);
    m_pCustomPlot->graph(GT_SELECTED_MARK)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    drawPen.setWidth(8);
    drawPen.setColor(QColor::fromRgb(255, 0, 255, 255));
    m_pCustomPlot->graph(GT_SELECTED_MARK)->setPen(drawPen);

    m_pCustomPlot->installEventFilter(this);

}

void MainWindow::BindSignalSlot()
{
    connect(m_pSetDirAction, &QAction::triggered, this, &MainWindow::slotCurrentDirChanged);
    connect(m_pSaveAction, &QAction::triggered, this, &MainWindow::slotSaveCurrentFile);
    connect(m_pUpdateAction, &QAction::triggered, this, &MainWindow::slotCheckUpdate);

    connect(m_pListView ,SIGNAL(clicked(QModelIndex)), this, SLOT(slotListViewSelectChanged(QModelIndex)));

    //connect(m_pListView ,SIGNAL(activated(QModelIndex)), this, SLOT(slotListViewSelectChanged(QModelIndex)));

    //connect(m_pModel, &QStandardItemModel::itemChanged, this, &MainWindow::slotListViewSelectdChanged);


    connect(this, &MainWindow::signalCurrentDirChanged, this, &MainWindow::slotFillFileList);
    connect(this, &MainWindow::signalCurrentFileChanged, this, &MainWindow::slotCurrentFileChanged);

    connect(this, &MainWindow::signalUpdataCustomplotEcgData, this, &MainWindow::slotUpdataCustomplotEcgData);
    connect(this, &MainWindow::signalUpdataCustomplotMarkData, this, &MainWindow::slotUpdataCustomplotMarkData);
    connect(this, &MainWindow::signalUpdataCustomplotSelectedData, this, &MainWindow::slotUpdataCustomplotSelectedData);

    connect(this, &MainWindow::signalInsertMarkPoint, this, &MainWindow::slotInsertCustomplotMarkData);

    connect(this, &MainWindow::signalRePaint, this, &MainWindow::slotRePaint);
}

void MainWindow::AddMarkPoint(MarkPointType type)
{
    m_HitMarkPoint.Clear();
    m_HitMarkPoint.type = type;
    m_HitMarkPoint.nIndex = - 1;
    m_HitMarkPoint.nNewPos = m_dMousePosX;

    slotUpdataHitToMarkPointData(true);
    ClearHitMarkDate();
}

void MainWindow::SetCustomplotSelectdData(double x, double y)
{
    ClearCustomplotSelectdData();

    if(m_HitMarkPoint.type < MARK_POINT_COUNT)
    {
        m_CustomplotSelectdData[0].push_back(x);
        m_CustomplotSelectdData[1].push_back(y);
    }

    emit signalUpdataCustomplotSelectedData();
}

void MainWindow::ShowStatusTips(const QString& str)
{
    m_pStatusTipsLable->setText(str);
}

void MainWindow::ShowSelectdType()
{
    bool bCorrect = m_HitMarkPoint.type <= MARK_POINT_COUNT;
    m_pStatusSelectdLable->setText("选中点：" +
                                   g_listMarkPointTypeName[ bCorrect ? m_HitMarkPoint.type : MARK_POINT_COUNT] +
                                   " " +
                                   (bCorrect ? QString::number(m_HitMarkPoint.nSelectPos) : " "));
}

void MainWindow::ShowMarkCount()
{
    QString str;
    for(int i = 0; i < MARK_POINT_COUNT; ++i)
    {
        str += (g_listMarkPointTypeName[i] + "(" + QString::number(m_vectMarkPoint[i].size()) + ") ");
        if((i+1) % 3 == 0)
            str += "   ";
    }

    m_pStatusMarkCountLable->setText(str);
}

HitMarkPoint MainWindow::HitMark(double xpos, double ypos)
{
    int bestdiff = 5000;
    double lower = xpos - 5,
           bigger = xpos + 5;
    double topper = ypos - 0.1 * abs(m_MaxVal_Y - m_MinVal_Y),
           botton = ypos + 0.1 * abs(m_MaxVal_Y - m_MinVal_Y);

    HitMarkPoint bestpoint;
    for(int i = 0; i < MarkPointType::MARK_POINT_COUNT; ++i)
    {
        for(int j = 0; j < m_vectMarkPoint[i].size(); ++j)
        {
            if(  lower < m_vectMarkPoint[i][j].nPos &&
                bigger > m_vectMarkPoint[i][j].nPos &&
                topper < m_CustomplotEcgData[1][m_vectMarkPoint[i][j].nPos] &&
                botton > m_CustomplotEcgData[1][m_vectMarkPoint[i][j].nPos])
            {
                int diff = abs(m_vectMarkPoint[i][j].nPos - xpos);
                if(diff < bestdiff)
                {
                    bestdiff = diff;

                    bestpoint.nIndex = j;
                    bestpoint.type = (MarkPointType)i;
                    bestpoint.nNewPos = m_vectMarkPoint[i][j].nPos;
                    bestpoint.nSelectPos = m_vectMarkPoint[i][j].nPos;
                }
            }
        }
    }

    return  bestpoint;
}

