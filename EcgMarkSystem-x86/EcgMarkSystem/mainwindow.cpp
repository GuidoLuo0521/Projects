
#include "mainwindow.h"
#include "ui_mainwindow.h"


static const QString skg_UpdateFileName = "update.json";
static const QString skg_UpdateExeName = "EcgMarkSystemUpdate.exe";
static const QString skg_UpdateUrl = "http://www.millet.fun/ECG/EcgMarkSystem/EcgMarkSystemUpdate.exe";

#include <QSplitter>
#include <QHBoxLayout>
#include <QEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_pModel(nullptr)
    , m_pSaveAction(nullptr)
    , m_pSetDirAction(nullptr)
    , m_pHttpdownload(nullptr)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/Main.ico"));

    m_strCurrentVersion = GetCurrentVersion();
    setWindowTitle("EMS - " + m_strCurrentVersion);

    InitColor();
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

                    SetCustomplotSelectedData(hitpoint.nSelectPos, m_CustomplotEcgData[1][ hitpoint.nSelectPos ]);
                    SetCustomplotActiviedData(hitpoint.nSelectPos, m_CustomplotEcgData[1][ hitpoint.nSelectPos ]);

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
                    SetCustomplotActiviedData(xint, m_CustomplotEcgData[1][ xint ]);
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
                    SetCustomplotActiviedData(xint, m_CustomplotEcgData[1][ xint ]);

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

                    SetCustomplotSelectedData(-1, -1);
                    SetCustomplotActiviedData(-1, -1);
                    ShowSelectdType();
                    return true;
                }
            }
            else if(keyEvent->key() == Qt::Key_Return)
            {
                m_bMousePressing = false;
                if(m_HitMarkPoint.type < MARK_POINT_COUNT)
                {
                    slotUpdataHitToMarkPointData(true);
                    ClearHitMarkDate();

                    SetCustomplotSelectedData(-1, -1);
                    SetCustomplotActiviedData(-1, -1);
                    ShowSelectdType();
                    return true;
                }
            }
            else if(keyEvent->key() == Qt::Key_Escape)
            {
                ClearHitMarkDate();

                SetCustomplotSelectedData(-1, -1);
                SetCustomplotActiviedData(-1, -1);
                ShowSelectdType();

                return true;
            }
            else if(keyEvent->key() == Qt::Key_Q) { AddMarkPoint(MarkPointType::PS); return true; }
            else if(keyEvent->key() == Qt::Key_W) { AddMarkPoint(MarkPointType::P); return true; }
            else if(keyEvent->key() == Qt::Key_E) { AddMarkPoint(MarkPointType::PE); return true; }
            else if(keyEvent->key() == Qt::Key_A) { AddMarkPoint(MarkPointType::QS); return true; }
            else if(keyEvent->key() == Qt::Key_S) { AddMarkPoint(MarkPointType::R); return true; }
            else if(keyEvent->key() == Qt::Key_D) { AddMarkPoint(MarkPointType::SE); return true; }
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
    QString strInitPath = "F:/QRS_lable_data";
    if(m_strCurrentDir != "")
        strInitPath = m_strCurrentDir;

    QString strDir = QFileDialog::getExistingDirectory(this, "选择文件夹", strInitPath);
    if(strDir.isEmpty())
        return;

    m_strCurrentDir = strDir;

    m_pActionOpenDir->setEnabled(true);
    m_pActionDeleteFile->setEnabled(true);

    emit signalFillFileList();
}

void MainWindow::slotCurrentFileChanged()
{
    slotOpenCurrentFile();
}

void MainWindow::slotFillFileList()
{
    QDir dir(m_strCurrentDir);
    QFileInfoList list = dir.entryInfoList( QDir::Filter::Files, m_Sortflag);

    m_pModel->clear();

    for( int i = 0; i < list.size(); ++i )
    {
        QString str = list[i].fileName();
        if(str != "." && str != "..")
        {
            if(m_nCustomFilterType == 1)
            {
                if( str.contains("副本") == false )
                {
                    QStandardItem *item = new QStandardItem(list[i].fileName());
                    m_pModel->appendRow(item);
                }
            }
            else if (m_nCustomFilterType == 2)
            {
                if( str.contains("副本") == true )
                {
                    QStandardItem *item = new QStandardItem(list[i].fileName());
                    m_pModel->appendRow(item);
                }
            }
            else
            {
                QStandardItem *item = new QStandardItem(list[i].fileName());
                m_pModel->appendRow(item);
            }
        }
    }
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

    setWindowTitle("EMS - " + m_strCurrentVersion + " " + m_strCurrentFile);

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
        this->setWindowTitle("EMS - " + m_strCurrentVersion + " " + m_strCurrentFile);
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
    emit signalUpdataCustomplotActiviedData();
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
    if(CheckSaveCorrect() == false)
        return;

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

    emit signalFillFileList();
    emit signalCurrentFileChanged();
}

void MainWindow::slotCheckUpdate()
{
    // 可以单独写一个 update.exe 文件;
    if( QFile::exists(QApplication::applicationDirPath() + "/" + skg_UpdateExeName) == false)
    {
        ShowStatusTips("更新文件：" + skg_UpdateExeName + " 不存在，正在下载。");

        m_pHttpdownload = new CHttpDownLoadFile(
            skg_UpdateUrl,
            skg_UpdateExeName,
            QApplication::applicationDirPath(),
            this);

        connect( m_pHttpdownload, SIGNAL(DownloadFinishedSignal()), this, SLOT(slotDownloadUpdateExeFinished()));

    }
    else
    {
        slotDownloadUpdateExeFinished();
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
    QPen pen = m_pCustomPlot->graph(GT_SELECTED_MARK)->pen();
    pen.setColor(m_vColorSelected[GT_SELECTED_MARK]);

    QString strName = "Select ";
    strName += g_listMarkPointTypeName[m_HitMarkPoint.type];

    switch(m_HitMarkPoint.type)
    {
    case MarkPointType::PS:
    case MarkPointType::P:
    case MarkPointType::PE:
        pen.setColor(m_vColorSelected[GT_MARK_POINT_P]);
        m_pCustomPlot->graph(GT_SELECTED_MARK)->setPen(pen);
        break;
    case MarkPointType::QS:
    case MarkPointType::R:
    case MarkPointType::SE:
        pen.setColor(m_vColorSelected[GT_MARK_POINT_R]);
        m_pCustomPlot->graph(GT_SELECTED_MARK)->setPen(pen);
        break;
    case MarkPointType::TS:
    case MarkPointType::T:
    case MarkPointType::TE:
        pen.setColor(m_vColorSelected[GT_MARK_POINT_T]);
        m_pCustomPlot->graph(GT_SELECTED_MARK)->setPen(pen);
        break;
    default:
         m_pCustomPlot->graph(GT_SELECTED_MARK)->setPen(pen);
        break;
    }

    m_pCustomPlot->graph(GT_SELECTED_MARK)->setName(strName);
    m_pCustomPlot->graph(GT_SELECTED_MARK)->setData(m_CustomplotSelectedData[0], m_CustomplotSelectedData[1]);
    emit signalRePaint();
}

void MainWindow::slotUpdataCustomplotActiviedData()
{
    m_pCustomPlot->graph(GT_ACTIVIED_MARK)->setData(m_CustomplotActiviedData[0], m_CustomplotActiviedData[1]);
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
            else if( i <= MarkPointType::SE )
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

void MainWindow::slotShowListViewContextMenu(const QPoint&)
{
    m_pListViewContextMenu->exec(QCursor::pos());//在当前鼠标位置显示
}

void MainWindow::slotSetListSort()
{
    m_pActionSortByName->setChecked(false);
    m_pActionSortBySize->setChecked(false);
    m_pActionSortByTime->setChecked(false);
    m_pActionSortByType->setChecked(false);
    m_pActionSortByLocal->setChecked(false);

    QAction * pAction = (QAction *)sender();

    if(pAction == m_pActionSortByName)
        m_Sortflag = QDir::SortFlag::Name;
    else if(pAction == m_pActionSortBySize)
        m_Sortflag = QDir::SortFlag::Size;
    else if(pAction == m_pActionSortByTime)
        m_Sortflag = QDir::SortFlag::Time;
    else if(pAction == m_pActionSortByType)
        m_Sortflag = QDir::SortFlag::Type;
    else
        m_Sortflag = QDir::SortFlag::LocaleAware;

    if(pAction != nullptr)
        pAction->setChecked(true);

    emit signalFillFileList();
}

void MainWindow::slotOpenDir()
{
    if(m_strCurrentDir == "")
    {
        ShowStatusTips("未设置路径。");
        return;
    }

    QDesktopServices::openUrl(QUrl::fromLocalFile(m_strCurrentDir));
}

void MainWindow::slotDeleteFile()
{
    if(m_strCurrentDir == "")
    {
        ShowStatusTips("未设置路径。");
        return;
    }

    QModelIndexList indexlist = m_pListView->selectionModel()->selectedIndexes();
    for( int i = 0; i < indexlist.size(); ++i )
    {
        QString strName = indexlist[i].data().toString();
        QString strAbsPath = m_strCurrentDir + "/" + strName;

        QFile::remove(strAbsPath);
    }

    ShowStatusTips("已删除文件。");

    emit signalFillFileList();
}

void MainWindow::slotSetFillFileKeyWord()
{
    m_pActionKeyByDup->setChecked(false);
    m_pActionKeyByRaw->setChecked(false);
    m_pActionKeyByAll->setChecked(false);

    QAction * pAction = (QAction *)sender();
    if(pAction == m_pActionKeyByDup)
    {
        m_nCustomFilterType = 2;
        m_pActionKeyByDup->setChecked(true);
    }
    else if(pAction == m_pActionKeyByRaw)
    {
        m_nCustomFilterType = 1;
        m_pActionKeyByRaw->setChecked(true);
    }
    else
    {
        m_nCustomFilterType = 0;
        m_pActionKeyByAll->setChecked(true);
    }

    emit signalFillFileList();
}

void MainWindow::slotDownloadUpdateExeFinished()
{
    QString strUpdateExePath = QApplication::applicationDirPath() + "/" + skg_UpdateExeName;
    if( QFile::exists(strUpdateExePath) == false)
    {
        if(m_pHttpdownload != nullptr)
        {
            ShowStatusTips("更新文件，下载失败。");
            delete m_pHttpdownload;
            m_pHttpdownload = nullptr;
            return;
        }

        ShowStatusTips("更新文件不存在，请联系管理员。");
        return;
    }

    if(m_pHttpdownload != nullptr)
    {
        ShowStatusTips("更新文件，下载完成。");
        delete m_pHttpdownload;
        m_pHttpdownload = nullptr;
    }

    QProcess process(this);
    process.startDetached(strUpdateExePath);
}

void MainWindow::ClearLastFile()
{
    m_MaxVal_Y = -10000,
    m_MinVal_Y =  10000;

    ClearMarkPointVect();
    ClearCustomplotEcgData();
    ClearCustomplotMarkData();
    ClearCustomplotSelectedData();
    ClearCustomplotActiviedData();

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

void MainWindow::ClearCustomplotSelectedData()
{
    m_CustomplotSelectedData[0].clear();
    m_CustomplotSelectedData[1].clear();
}

void MainWindow::ClearCustomplotActiviedData()
{
    m_CustomplotActiviedData[0].clear();
    m_CustomplotActiviedData[1].clear();
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

void MainWindow::InitColor()
{
    m_vColorMark[GT_ECG_DATA] = QColor::fromRgb(0, 0, 255, 180);
    m_vColorMark[GT_MARK_POINT_P] = QColor::fromRgb(255, 0, 0, 180);
    m_vColorMark[GT_MARK_POINT_R] = QColor::fromRgb(0, 255, 0, 180);
    m_vColorMark[GT_MARK_POINT_T] = QColor::fromRgb(0, 0, 255, 180);
    m_vColorMark[GT_SELECTED_MARK] = QColor::fromRgb(255, 0, 255, 100);
    m_vColorMark[GT_ACTIVIED_MARK] = QColor::fromRgb(255, 0, 255, 255);

    m_vColorSelected[GT_MARK_POINT_P] = QColor::fromRgb(255, 32, 11, 255);
    m_vColorSelected[GT_MARK_POINT_R] = QColor::fromRgb(153, 204, 51, 255);
    m_vColorSelected[GT_MARK_POINT_T] = QColor::fromRgb(1, 0, 41, 255);
    m_vColorSelected[GT_SELECTED_MARK] = QColor::fromRgb(255, 255, 255);
}

void MainWindow::InitLayout()
{
    QSplitter * pMainSplitter = new QSplitter(Qt::Horizontal);

    // 菜单栏
    InitMenuBar();
    // 状态栏
    InitStatuBar();
    // 文件列表
    InitListView();
    // 绘图
    InitCustomplot();

    pMainSplitter->addWidget(m_pListView);    
    pMainSplitter->addWidget(m_pCustomPlot);

    pMainSplitter->setStretchFactor(0, 1);
    pMainSplitter->setStretchFactor(1, 15);

    this->setCentralWidget(pMainSplitter);

 }

void MainWindow::InitMenuBar()
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
}

void MainWindow::InitStatuBar()
{
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


    QPen drawPen;
    /***************************************************************************************/
    // 心电数据
    m_pCustomPlot->addGraph();
    m_pCustomPlot->graph(GT_ECG_DATA)->setName("ECG");   // 设置曲线图的名字

    drawPen.setWidth(1);
    drawPen.setColor(m_vColorMark[GT_ECG_DATA]);
    m_pCustomPlot->graph(GT_ECG_DATA)->setPen(drawPen);
    /***************************************************************************************/

    drawPen.setWidth(5);
    /***************************************************************************************/
    // 标记点 P
    m_pCustomPlot->addGraph();
    m_pCustomPlot->graph(GT_MARK_POINT_P)->setName("Ps P Pe");
    m_pCustomPlot->graph(GT_MARK_POINT_P)->setLineStyle(QCPGraph::lsNone);
    m_pCustomPlot->graph(GT_MARK_POINT_P)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    drawPen.setColor(m_vColorMark[GT_MARK_POINT_P]);
    m_pCustomPlot->graph(GT_MARK_POINT_P)->setPen(drawPen);

    /***************************************************************************************/
    // 标记点 QRS
    m_pCustomPlot->addGraph();
    m_pCustomPlot->graph(GT_MARK_POINT_R)->setName("Rs R Re");
    m_pCustomPlot->graph(GT_MARK_POINT_R)->setLineStyle(QCPGraph::lsNone);
    m_pCustomPlot->graph(GT_MARK_POINT_R)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    drawPen.setColor(m_vColorMark[GT_MARK_POINT_R]);
    m_pCustomPlot->graph(GT_MARK_POINT_R)->setPen(drawPen);

    /***************************************************************************************/
    // 标记点 T
    m_pCustomPlot->addGraph();
    m_pCustomPlot->graph(GT_MARK_POINT_T)->setName("TS T Te");
    m_pCustomPlot->graph(GT_MARK_POINT_T)->setLineStyle(QCPGraph::lsNone);
    m_pCustomPlot->graph(GT_MARK_POINT_T)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    drawPen.setColor(m_vColorMark[GT_MARK_POINT_T]);
    m_pCustomPlot->graph(GT_MARK_POINT_T)->setPen(drawPen);

    /***************************************************************************************/
    // 被选中点
    m_pCustomPlot->addGraph();
    m_pCustomPlot->graph(GT_SELECTED_MARK)->setName("Select");
    m_pCustomPlot->graph(GT_SELECTED_MARK)->setLineStyle(QCPGraph::lsNone);
    m_pCustomPlot->graph(GT_SELECTED_MARK)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    drawPen.setColor(m_vColorSelected[GT_SELECTED_MARK]);
    m_pCustomPlot->graph(GT_SELECTED_MARK)->setPen(drawPen);

    /***************************************************************************************/
    // 激活移动点
    m_pCustomPlot->addGraph();
    m_pCustomPlot->graph(GT_ACTIVIED_MARK)->setName("Active");
    m_pCustomPlot->graph(GT_ACTIVIED_MARK)->setLineStyle(QCPGraph::lsNone);
    m_pCustomPlot->graph(GT_ACTIVIED_MARK)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    drawPen.setWidth(8);
    drawPen.setColor(m_vColorMark[GT_ACTIVIED_MARK]);
    m_pCustomPlot->graph(GT_ACTIVIED_MARK)->setPen(drawPen);

    /***************************************************************************************/
    m_pCustomPlot->installEventFilter(this);

}

void MainWindow::InitListView()
{
    m_pModel = new QStandardItemModel;
    m_pListView = new QListView;

    m_pListView->setModel(m_pModel);
    connect(m_pListView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &MainWindow::slotListViewSelectdChanged);
    //m_pListView->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);

    m_pListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 右键菜单
    m_pListView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_pListView, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(slotShowListViewContextMenu(const QPoint&)));

    m_pListViewContextMenu = new QMenu(m_pListView);
    QMenu * pSortType = new QMenu("排序方式");
    m_pListViewContextMenu->addMenu(pSortType);

    m_pActionSortByLocal = pSortType->addAction("默认");
    m_pActionSortByName = pSortType->addAction("名称");
    m_pActionSortByTime = pSortType->addAction("时间");
    m_pActionSortBySize = pSortType->addAction("大小");
    m_pActionSortByType = pSortType->addAction("类型");

    //排序
    m_pActionSortByName->setCheckable(true);
    m_pActionSortBySize->setCheckable(true);
    m_pActionSortByTime->setCheckable(true);
    m_pActionSortByType->setCheckable(true);
    m_pActionSortByLocal->setCheckable(true);
    m_pActionSortByLocal->setChecked(true);
    m_Sortflag = QDir::SortFlag::LocaleAware;

    connect(m_pActionSortByName, SIGNAL(triggered(bool)), this, SLOT(slotSetListSort()));
    connect(m_pActionSortByTime, SIGNAL(triggered(bool)), this, SLOT(slotSetListSort()));
    connect(m_pActionSortBySize, SIGNAL(triggered(bool)), this, SLOT(slotSetListSort()));
    connect(m_pActionSortByType, SIGNAL(triggered(bool)), this, SLOT(slotSetListSort()));
    connect(m_pActionSortByLocal, SIGNAL(triggered(bool)), this, SLOT(slotSetListSort()));

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // 筛选副本
    QMenu * pFilterType = new QMenu("筛选");
    m_pListViewContextMenu->addMenu(pFilterType);

    m_pActionKeyByAll = pFilterType->addAction("全部");
    m_pActionKeyByRaw = pFilterType->addAction("原始");
    m_pActionKeyByDup = pFilterType->addAction("副本");

    m_pActionKeyByAll->setCheckable(true);
    m_pActionKeyByRaw->setCheckable(true);
    m_pActionKeyByDup->setCheckable(true);

    m_pActionKeyByAll->setChecked(true);

    connect(m_pActionKeyByAll, SIGNAL(triggered(bool)), this, SLOT(slotSetFillFileKeyWord()));
    connect(m_pActionKeyByRaw, SIGNAL(triggered(bool)), this, SLOT(slotSetFillFileKeyWord()));
    connect(m_pActionKeyByDup, SIGNAL(triggered(bool)), this, SLOT(slotSetFillFileKeyWord()));

    ////////////////////////////////////////////////////////////////////////////////////////////////
    m_pActionOpenDir = m_pListViewContextMenu->addAction("文件夹");
    m_pActionDeleteFile = m_pListViewContextMenu->addAction("删除");

    m_pActionOpenDir->setEnabled(false);
    m_pActionDeleteFile->setEnabled(false);

    connect(m_pActionOpenDir, SIGNAL(triggered(bool)), this, SLOT(slotOpenDir()));
    connect(m_pActionDeleteFile, SIGNAL(triggered(bool)), this, SLOT(slotDeleteFile()));


    m_pListView->installEventFilter(this);
}

void MainWindow::BindSignalSlot()
{
    connect(m_pSetDirAction, &QAction::triggered, this, &MainWindow::slotCurrentDirChanged);
    connect(m_pSaveAction, &QAction::triggered, this, &MainWindow::slotSaveCurrentFile);
    connect(m_pUpdateAction, &QAction::triggered, this, &MainWindow::slotCheckUpdate);

    connect(m_pListView ,SIGNAL(clicked(QModelIndex)), this, SLOT(slotListViewSelectChanged(QModelIndex)));

    connect(this, &MainWindow::signalFillFileList, this, &MainWindow::slotFillFileList);
    connect(this, &MainWindow::signalCurrentFileChanged, this, &MainWindow::slotCurrentFileChanged);

    connect(this, &MainWindow::signalUpdataCustomplotEcgData, this, &MainWindow::slotUpdataCustomplotEcgData);
    connect(this, &MainWindow::signalUpdataCustomplotMarkData, this, &MainWindow::slotUpdataCustomplotMarkData);
    connect(this, &MainWindow::signalUpdataCustomplotSelectedData, this, &MainWindow::slotUpdataCustomplotSelectedData);
    connect(this, &MainWindow::signalUpdataCustomplotActiviedData, this, &MainWindow::slotUpdataCustomplotActiviedData);

    connect(this, &MainWindow::signalInsertMarkPoint, this, &MainWindow::slotInsertCustomplotMarkData);

    connect(this, &MainWindow::signalRePaint, this, &MainWindow::slotRePaint);
}

bool MainWindow::CheckSaveCorrect()
{
    if(m_vectMarkPoint[(int)MarkPointType::PS].size() != m_vectMarkPoint[(int)MarkPointType::PE].size())
    {
        QMessageBox::critical(this, "警告", "PS PE 个数不相等");
        return false;
    }
    if(m_vectMarkPoint[(int)MarkPointType::QS].size() != m_vectMarkPoint[(int)MarkPointType::SE].size())
    {
        QMessageBox::critical(this, "警告", "Q S 个数不相等");
        return false;
    }
    if(m_vectMarkPoint[(int)MarkPointType::TS].size() != m_vectMarkPoint[(int)MarkPointType::TE].size())
    {
        QMessageBox::critical(this, "警告", "TS TE 个数不相等");
        return false;
    }

    if(m_CustomplotEcgData->size() <= 0)
    {
        ShowStatusTips("未打开文件");
        return false;
    }

    return true;
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


void MainWindow::SetCustomplotActiviedData(double x, double y)
{
    ClearCustomplotActiviedData();

    if(m_HitMarkPoint.type < MARK_POINT_COUNT)
    {        
        m_CustomplotActiviedData[0].push_back(x);
        m_CustomplotActiviedData[1].push_back(y);
    }

    emit signalUpdataCustomplotActiviedData();
}

void MainWindow::SetCustomplotSelectedData(double x, double y)
{
    ClearCustomplotSelectedData();

    if(m_HitMarkPoint.type < MARK_POINT_COUNT)
    {
        m_CustomplotSelectedData[0].push_back(x);
        m_CustomplotSelectedData[1].push_back(y);
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


QString MainWindow::GetCurrentVersion()
{
    if(QFile::exists(QApplication::applicationDirPath() + "/" + skg_UpdateFileName) == false)
    {
        return  "V Unknow";
    }

    QFile file(QApplication::applicationDirPath() + "/" + skg_UpdateFileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    file.close();

    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        //QMessageBox::information(nullptr, "提示", "本地文件更新文件错误！");
        return "V Unknow";
    }
    QJsonObject jsonObject = document.object();
    QJsonObject PulseValue = jsonObject.value("PulseSensor").toObject();
    QString Version = PulseValue.value("LatestVersion").toString();  //V1.0

    return  Version;
}
