#include <QLayout>
#include "WinMine.h"

WinMine::WinMine(QWidget* parent):QMainWindow(parent)
{
    setWindowTitle(tr("扫雷"));
    setWindowIcon(QIcon(tr(":/images/bomber.png")));
    reset_Action = new QAction(tr("重置"),this);
    close_Action = new QAction(tr("结束"),this);
    easy_Action = new QAction(tr("简单"),this);
    normal_Action = new QAction(tr("中等"),this);
    hard_Action = new QAction(tr("困难"),this);

    game_Menu = new QMenu(tr("游戏"));
    option_Menu = new QMenu(tr("难度"));

    menus_MenuBar = menuBar();  //生成菜单栏

    option_ActionGroup = new QActionGroup(this);

    gameOver_Dialog = new GameOverDialog(this);

    gameMap = new GameMap;

    gameOver_Dialog->hide();

    easy_Action->setCheckable(true);
    normal_Action->setCheckable(true);
    hard_Action->setCheckable(true);
    easy_Action->setChecked(true);

    setCentralWidget(gameMap);
    game_Menu->addAction(reset_Action);
    game_Menu->addAction(close_Action);

    option_ActionGroup->addAction(easy_Action);
    option_ActionGroup->addAction(normal_Action);
    option_ActionGroup->addAction(hard_Action);
    option_Menu->addAction(easy_Action);
    option_Menu->addAction(normal_Action);
    option_Menu->addAction(hard_Action);

    menus_MenuBar->addMenu(game_Menu);
    menus_MenuBar->addMenu(option_Menu);

    layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(gameMap,SIGNAL(hasWin()),this,SLOT(gameWin()));
    connect(gameMap,SIGNAL(hasFail()),this,SLOT(gameFail()));
    connect(reset_Action,SIGNAL(triggered()),this,SLOT(resetGame()));
    connect(easy_Action,SIGNAL(triggered()),this,SLOT(resetGame()));  //resetGame()默认是简单难度，所以这里把简单选项直接连接到这里
    connect(normal_Action,SIGNAL(triggered()),this,SLOT(normalGame()));
    connect(hard_Action,SIGNAL(triggered()),this,SLOT(hardGame()));
}

void WinMine::gameWin()
{
    gameOver_Dialog->setInfo(tr("Win"));
    gameOver_Dialog->exec();
    gameMap->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void WinMine::gameFail()
{
    gameOver_Dialog->setInfo(tr("Fail"));
    gameOver_Dialog->exec();
    gameMap->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void WinMine::resetGame(int l)
{
    gameMap->resetGame(l);
    gameMap->setAttribute(Qt::WA_TransparentForMouseEvents,false);
}

void WinMine::normalGame()
{
    resetGame(NORMAL_WINMINE);
}

void WinMine::hardGame()
{
    resetGame(HARD_WINMINE);
}
