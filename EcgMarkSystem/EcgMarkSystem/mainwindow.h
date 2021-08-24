#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QListView>
#include <QStandardItemModel>
#include <QTableView>
#include <QModelIndex>


#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "ecgmarkdef.h"
#include "qcustomplot.h"
#include "chttpdownloadfile.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum QCustomPlotGrapType
    {
        GT_ECG_DATA,
        GT_MARK_POINT_P,
        GT_MARK_POINT_R,
        GT_MARK_POINT_T,
        GT_SELECTED_MARK,
        GT_ACTIVIED_MARK,

        GT_MARK_COUNT

    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    virtual bool eventFilter(QObject *watched, QEvent *event);

signals:
    void signalFillFileList();
    void signalCurrentFileChanged();

    void signalUpdataCustomplotEcgData();
    void signalUpdataCustomplotMarkData();
    void signalUpdataCustomplotSelectedData();
    void signalUpdataCustomplotActiviedData();

    void signalRePaint();
    void signalUpdataHitToMark(bool insert);
    void signalInsertMarkPoint();

private slots:
    void slotCurrentDirChanged();
    void slotCurrentFileChanged();

    void slotFillFileList();
    void slotListViewSelectChanged(QModelIndex);
    void slotListViewSelectdChanged(const QModelIndex &current, const QModelIndex &previous);

    void slotOpenCurrentFile();
    void slotSaveCurrentFile();
    void slotCheckUpdate();

    void slotUpdataCustomplotEcgData();
    void slotUpdataCustomplotMarkData();
    void slotUpdataHitToMarkPointData(bool insert);

    void slotUpdataCustomplotSelectedData();
    void slotUpdataCustomplotActiviedData();
    void slotRePaint();

    void slotInsertCustomplotMarkData();

    void slotShowListViewContextMenu(const QPoint&);

    void slotSetListSort();

    void slotOpenDir();
    void slotDeleteFile();
    void slotSetFillFileKeyWord();

    void slotDownloadUpdateExeFinished();

private:
    void ClearLastFile();

    void ClearHitMarkDate();
    void ClearMarkPointVect();

    void ClearCustomplotEcgData();
    void ClearCustomplotMarkData();
    void ClearCustomplotSelectedData();
    void ClearCustomplotActiviedData();

    void InsertEcgDataList(const QJsonArray& jsonarr);
    void InsertMarkPointList(MarkPointType marktype, const QJsonArray& jsonarr);

    void InitColor();
    void InitLayout();
    void InitMenuBar();
    void InitStatuBar();
    void InitCustomplot();

    /**********************************************************************************/
    void InitListView();
    void BindSignalSlot();

private:
    QString GetCurrentVersion();
    bool CheckSaveCorrect();

    void AddMarkPoint(MarkPointType type);
    void ShowSelectdType();
    void ShowMarkCount();
    void ShowStatusTips(const QString& str);
    void SetCustomplotActiviedData(double x, double y);
    void SetCustomplotSelectedData(double x, double y);

    HitMarkPoint HitMark(double xpos, double ypos);

    Ui::MainWindow *ui;

    QMenu * m_pListViewContextMenu;
    QLabel * m_pStatusTipsLable;
    QLabel * m_pStatusMarkCountLable;
    QLabel * m_pStatusAxisPosLable;
    QLabel * m_pStatusSelectdLable;

    QCustomPlot * m_pCustomPlot;
    QListView * m_pListView;
    QStandardItemModel *m_pModel;

    QAction * m_pSaveAction;
    QAction * m_pUpdateAction;
    QAction * m_pSetDirAction;

    // pop menu
    QAction * m_pActionSortByName ;
    QAction * m_pActionSortByTime ;
    QAction * m_pActionSortBySize ;
    QAction * m_pActionSortByType ;
    QAction * m_pActionSortByLocal;

    QAction * m_pActionOpenDir;
    QAction * m_pActionDeleteFile;

    QAction * m_pActionKeyByAll;
    QAction * m_pActionKeyByRaw;
    QAction * m_pActionKeyByDup;

    // 文件列表选项
    int m_nCustomFilterType;    // 0: 全部显示 1：原始文件 2：副本
    QDir::SortFlag m_Sortflag = QDir::SortFlag::LocaleAware;


    QString m_strCurrentDir;
    QString m_strCurrentFile;

    double m_dMousePosX;
    double m_dMousePosY;

    double m_MaxVal_Y = -10000,
           m_MinVal_Y =  10000;

    CustomplotAxisData m_CustomplotEcgData;

    CustomplotAxisData m_CustomplotPMarkData;
    CustomplotAxisData m_CustomplotRMarkData;
    CustomplotAxisData m_CustomplotTMarkData;

    CustomplotAxisData m_CustomplotSelectedData;
    CustomplotAxisData m_CustomplotActiviedData;

    MarkPointVect m_vectMarkPoint[MarkPointType::MARK_POINT_COUNT];
    HitMarkPoint m_HitMarkPoint;

    QColor m_vColorMark[GT_MARK_COUNT];
    QColor m_vColorSelected[GT_MARK_COUNT];

    bool m_bMousePressing = false;

    CHttpDownLoadFile * m_pHttpdownload;

};
#endif // MAINWINDOW_H
