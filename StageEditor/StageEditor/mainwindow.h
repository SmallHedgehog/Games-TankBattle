#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QPainter>
#include <QToolBar>
#include <QLabel>
#include <QList>
#include <QDebug>
#include <QMouseEvent>
#include <QPicture>
#include <QFileDialog>
#include "defines.h"
#include "enums.h"

struct Node
{
    int type;
    int x;
    int y;
};
typedef struct Node ICON_NODE;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent (QPaintEvent*);
    void mousePressEvent (QMouseEvent* event);

private:
    void InitAction();                  // 初始化Action
    void AddToolBar();                  // 增加工具栏
    void InitWindow();                  // 初始化窗口
    void DrawGrid(QPainter* painter);   // 绘制网格
    void DrawIcon(QPainter* painter, ICON_NODE& node);   // 绘制图标
    void ConnectSignalsAndSlots();      // 连接信号与槽

private:
    QAction *normalAct, *steelAct, *grassAct, *waterAct;
    QAction *symbolAct;
    QAction *saveFile, *clearData;
    QToolBar* toolBar;

    Type type;
    int x_pos;
    int y_pos;
    QList<ICON_NODE> lists;

private slots:
    void setType(QAction* action);
    void SaveFile();
    void OpenFile();
    void ClearData();
};

#endif // MAINWINDOW_H
