#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    AddToolBar ();
    InitWindow ();
    ConnectSignalsAndSlots ();

    type = NONE;
    x_pos = 0;
    y_pos = 0;
}

// 初始化窗口
void MainWindow::InitWindow ()
{
    // 调整窗口大小
    //resize (WIN_WIDTH, WIN_HEIGHT);
    // 设置窗口固定大小
    setFixedSize (WIN_WIDTH, WIN_HEIGHT);
    // 设置窗口图标
    setWindowIcon (QIcon(QString(":/res_win/win_icon.png")));
}

// 初始化Action
void MainWindow::InitAction ()
{
    normalAct = new QAction(QIcon(QString(":/res_app/normal.png")), QString("Normal"), this);
    steelAct = new QAction(QIcon(QString(":/res_app/steel.png")), QString("Steel"), this);
    grassAct = new QAction(QIcon(QString(":/res_app/grass.png")), QString("Grass"), this);
    waterAct = new QAction(QIcon(QString(":/res_app/water.png")), QString("Water"), this);
    symbolAct = new QAction(QIcon(QString(":/res_app/symbol.png")), QString("Symbol"), this);
    saveFile = new QAction(QIcon(QString(":/res_app/save.png")), QString("SaveFile"), this);
    clearData = new QAction(QIcon(QString(":/res_app/clear.png")), QString("clearData"), this);
}

// 增加工具栏
void MainWindow::AddToolBar ()
{
    InitAction ();
    toolBar = addToolBar (QString("MainToolBar"));
    toolBar->setIconSize (QSize(60, 60));
    toolBar->setAutoFillBackground (true);
    toolBar->setBackgroundRole (QPalette::Light);
    toolBar->setAllowedAreas (Qt::NoToolBarArea);

    QList<QAction*> listActs;
    listActs << symbolAct << normalAct << steelAct
             << grassAct << waterAct << toolBar->addSeparator ()
             << saveFile << clearData;
    toolBar->addActions(listActs);
}

// 连接信号与槽
void MainWindow::ConnectSignalsAndSlots ()
{
    connect (toolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(setType(QAction*)));
    connect (saveFile, SIGNAL(triggered(bool)), this, SLOT(SaveFile()));
    connect (clearData, SIGNAL(triggered(bool)), this, SLOT(ClearData()));

    OpenFile ();
}

void MainWindow::paintEvent (QPaintEvent *)
{
    QPainter painter(this);

    // 绘制网格
    DrawGrid (&painter);

    // 绘制图标
    for (int i=0; i<lists.size (); ++i)
    {
        DrawIcon (&painter, lists[i]);
    }
}

// 重写鼠标左击事件
void MainWindow::mousePressEvent (QMouseEvent *event)
{
    if (event->button () == Qt::LeftButton)
    {
        x_pos = (event->x () / GRID_SIZE) * GRID_SIZE;
        y_pos = (event->y () / GRID_SIZE) * GRID_SIZE;
        if (type != NONE)
        {
            ICON_NODE node = {
                int(type), x_pos, y_pos
            };
            lists.append (node);

            update ();
        }
    }
}

// 绘制图标
void MainWindow::DrawIcon(QPainter* painter, ICON_NODE &node)
{
    switch (Type(node.type))
    {
    case NORMAL:
        painter->drawPixmap (node.x, node.y, QPixmap(QString(":/res_app/normal.png")));
        break;
    case STELL:
        painter->drawPixmap (node.x, node.y, QPixmap(QString(":/res_app/steel.png")));
        break;
    case GRASS:
        painter->drawPixmap (node.x, node.y, QPixmap(QString(":/res_app/grass.png")));
        break;
    case WATER:
        painter->drawPixmap (node.x, node.y, QPixmap(QString(":/res_app/water.png")));
        break;
    case SYMBOL:
        painter->drawPixmap (node.x, node.y, QPixmap(QString(":/res_app/symbol.png")));
        break;
    case NONE:
        break;
    }
}

// 绘制网格
void MainWindow::DrawGrid (QPainter *painter)
{
    // 网格大小30*30
    for (int x=0; x<26; ++x)
    {
        painter->drawLine (x * GRID_SIZE, 0, x * GRID_SIZE, WIN_HEIGHT);
    }

    for (int y=0; y<26; ++y)
    {
        painter->drawLine (0, y * GRID_SIZE, WIN_WIDTH, y * GRID_SIZE);
    }
}

void MainWindow::setType (QAction *action)
{
    if (action == normalAct){
        type = NORMAL;
    }
    else if (action == steelAct){
        type = STELL;
    }
    else if (action == grassAct){
        type = GRASS;
    }
    else if (action == waterAct){
        type = WATER;
    }
    else if (action == symbolAct){
        type = SYMBOL;
    }
    else{
        type = NONE;
    }
}

// 清除数据
void MainWindow::ClearData ()
{
    lists.clear ();
    update ();
}

// 保存数据到文件中
void MainWindow::SaveFile()
{
    QString fileName = QFileDialog::getSaveFileName (this, QString("Save file dialog"), "", QString("(*.txt)"));
    if (!fileName.isNull ())
    {
        QFile file(fileName);
        if (!file.open (QIODevice::WriteOnly))
        {
            qDebug() << "Open file error!";
            return ;
        }
        else
        {
            QTextStream out(&file);
            for (int i=0; i<lists.size (); ++i)
            {
                out << lists[i].type << " " << lists[i].x
                    << " " << lists[i].y << "\n";
            }
        }
        file.close ();
    }
}

// 打开文件
void MainWindow::OpenFile ()
{
    QString fileName = QFileDialog::getOpenFileName (this, QString("Open file dialog"), "", QString("(*.txt)"));
    if (!fileName.isNull ())
    {
        QFile file(fileName);
        if (!file.open (QIODevice::ReadOnly))
        {
            qDebug() << "read file error!";
            return ;
        }
        else
        {
            QTextStream in(&file);
            QString str = "";
            while (!in.atEnd ())
            {
                str = in.readLine ();
                QStringList strlists = str.split (" ");
                ICON_NODE node = {
                  QString(strlists[0]).toInt (), QString(strlists[1]).toInt (), QString(strlists[2]).toInt ()
                };
                lists << node;
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete toolBar;
}
