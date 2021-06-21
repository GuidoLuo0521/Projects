#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QListWidget>
#include <QStatusBar>
#include <QAction>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QWidget>
#include <QVector>
#include "FileInfo.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

protected:
    void wheelEvent(QWheelEvent *event);

    // slots
private slots:
    void slot_SetFolder();
    void slot_ConverToImageTriggered();
    void slot_FileInfoChanged();
    void slot_FileListCurrentRowChanged(int currentRow);

signals:
    void signal_FileInfoChanged();


////////////////////////////////////////////

    // Action
private:
    void CreateAction();

    // MenuBar
private:
    void InitMenuBar();

    // ToolBar
private:
    void InitToolBar();

    // MainWindow
private:
    void InitMainWindow();

    // Action
private:
    void BindAction();

    ////////////////////////////////////////////
    // Actioon
private:
    QAction * m_pConverToImage;
    QAction * m_pSetFolder;

    // QListWidget
private:
    QListWidget* m_pFileList;
    QVector<stFileInfo> m_vFileInfo;

    // GraphicsScene GraphicsView
private:
    QGraphicsScene* m_pGraphicsScene;
    QGraphicsView* m_pGraphicsView;

};
#endif // MAINWINDOW_H
