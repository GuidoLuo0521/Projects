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
        GT_SELECTED_MARK
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    virtual bool eventFilter(QObject *watched, QEvent *event);

protected:
    //virtual void mousePressEvent(QMouseEvent *event);
    //virtual void mouseReleaseEvent(QMouseEvent *event);
    //virtual void mouseMoveEvent(QMouseEvent *event);

signals:
    void signalCurrentDirChanged();
    void signalCurrentFileChanged();

    void signalUpdataCustomplotEcgData();
    void signalUpdataCustomplotMarkData();
    void signalUpdataCustomplotSelectedData();

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
    void slotRePaint();

    void slotInsertCustomplotMarkData();

private:
    void ClearLastFile();

    void ClearHitMarkDate();
    void ClearMarkPointVect();
    void ClearCustomplotEcgData();
    void ClearCustomplotMarkData();
    void ClearCustomplotSelectdData();

    void InsertMarkPointList(MarkPointType marktype, const QJsonArray& jsonarr);
    void InsertEcgDataList(const QJsonArray& jsonarr);

    void InitLayout();
    void InitCustomplot();

    void BindSignalSlot();


private:
    void AddMarkPoint(MarkPointType type);
    void ShowSelectdType();
    void ShowMarkCount();
    void ShowStatusTips(const QString& str);
    void SetCustomplotSelectdData(double x, double y);

    HitMarkPoint HitMark(double xpos, double ypos);

    Ui::MainWindow *ui;

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

    CustomplotAxisData m_CustomplotSelectdData;

    MarkPointVect m_vectMarkPoint[MarkPointType::MARK_POINT_COUNT];
    HitMarkPoint m_HitMarkPoint;


    bool m_bMousePressing = false;

};
#endif // MAINWINDOW_H
