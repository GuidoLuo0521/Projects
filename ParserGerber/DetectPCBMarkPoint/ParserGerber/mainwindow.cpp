#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commontool.h"
#include "cparsergerber.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QToolBar>
#include <QDir>
#include <QWheelEvent>

QString stFileInfo::s_strCurrentFolderPath  = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    

    CreateAction();

    InitMainWindow();

    InitMenuBar();

    InitToolBar();

    BindAction();
}

MainWindow::~MainWindow()
{
    m_vFileInfo.clear();

    delete ui;
}

void MainWindow::slot_SetFolder()
{
    stFileInfo::s_strCurrentFolderPath = CommonFileTool::GetSelectFolder();

    emit signal_FileInfoChanged();
}

void MainWindow::slot_ConverToImageTriggered()
{
    QString strFile = CommonFileTool::GetSelectFile();

    CParserGerber parser;
    parser.Parser(strFile);

}

void MainWindow::slot_FileInfoChanged()
{
    QDir dir(stFileInfo::s_strCurrentFolderPath);
    if( ! dir.exists() )
    {
        return;
    }

    QStringList filters;
    filters << "*.bmp" << "*.jpg" << "*.png";

    dir.setNameFilters(filters);

    QStringList fileList = dir.entryList();
    m_pFileList->clear();
    m_vFileInfo.clear();

    for (int i = 0; i < fileList.count(); ++i)
    {
        if(fileList[i] != "." && fileList[i] != "..")
        {
            m_pFileList->addItem(fileList[i]);
            m_vFileInfo.push_back(stFileInfo(fileList[i], CT_NONE));
        }
    }
}

void MainWindow::slot_FileListCurrentRowChanged(int currentRow)
{
    if(currentRow == -1 || m_vFileInfo.size() <= 0)
        return;

    m_pGraphicsScene->clear();

    QString strFilePath = QString("%1/%2").arg(stFileInfo::s_strCurrentFolderPath).arg(m_vFileInfo[currentRow].strFileName);
    if( QFileInfo::exists(strFilePath) == false )
        return;

    QImage img(strFilePath);
    if( img.isNull() )
        return;

    // Test QImage Size
    //QImage img(20000, 20000, QImage::Format_RGBA8888);
    //img.fill(QColor::fromRgb(0,0,0));

    m_pGraphicsScene->addPixmap(QPixmap::fromImage(img));

    this->setWindowTitle(QString("%1").arg(m_vFileInfo[currentRow].strFileName));
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(QApplication::keyboardModifiers () == Qt::ControlModifier)
    {
        if(event->delta() > 0)
        {
            m_pGraphicsView->scale(1.1, 1.1);
        }
        else
        {
            m_pGraphicsView->scale(0.9, 0.9);
        }
    }
}

void MainWindow::CreateAction()
{
    m_pSetFolder = new QAction(QString("Folder"));
    m_pConverToImage = new QAction(QString("All"));

}

void MainWindow::InitMenuBar()
{
    QMenu * pMenu = nullptr;
    // File
    pMenu = new QMenu("&File", this);
    pMenu->addAction(m_pSetFolder);

    ui->menubar->addMenu(pMenu);
}

void MainWindow::InitToolBar()
{
    QToolBar * pFileBar = this->addToolBar("File");
    pFileBar->addAction(m_pSetFolder);

    QToolBar * pToolBar = this->addToolBar("Convert");
    pToolBar->addAction(m_pConverToImage);
}

void MainWindow::InitMainWindow()
{

    QWidget * pWidget = new QWidget();
    QGridLayout * pMainLayout = new QGridLayout;

    m_pFileList = new QListWidget(this);

    // 创建显示容器
    m_pGraphicsScene = new QGraphicsScene(this);
    m_pGraphicsView = new QGraphicsView( m_pGraphicsScene, this);

    m_pGraphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    m_pGraphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    // 加入到布局
    pMainLayout->addWidget(m_pFileList, 0, 0);
    pMainLayout->addWidget(m_pGraphicsView, 0, 1);

    pMainLayout->setColumnStretch(0, 2);
    pMainLayout->setColumnStretch(1, 8);

    pWidget->setLayout(pMainLayout);
    this->setCentralWidget(pWidget);
}

void MainWindow::BindAction()
{
    connect(m_pSetFolder, &QAction::triggered, this, &MainWindow::slot_SetFolder);
    connect(m_pConverToImage, &QAction::triggered, this, &MainWindow::slot_ConverToImageTriggered);

    connect(this, &MainWindow::signal_FileInfoChanged, this, &MainWindow::slot_FileInfoChanged );

    connect(m_pFileList, &QListWidget::currentRowChanged, this, &MainWindow::slot_FileListCurrentRowChanged);
}

