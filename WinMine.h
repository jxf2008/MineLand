#ifndef WINMINE_H
#define WINMINE_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QActionGroup>
#include "GameMap.h"
#include "GameOverDialog.h"

const int EASY_WINMINE = 10;  //这三个值代表地雷的数目，即难度
const int NORMAL_WINMINE = 20;
const int HARD_WINMINE = 30;


class WinMine : public QMainWindow
{
    Q_OBJECT
private:
    QAction* reset_Action;
    QAction* close_Action;
    QAction* easy_Action;
    QAction* normal_Action;
    QAction* hard_Action;

    QMenu* game_Menu;
    QMenu* option_Menu;

    QMenuBar* menus_MenuBar;

    QActionGroup* option_ActionGroup;

    GameOverDialog* gameOver_Dialog;

    GameMap* gameMap;
public:
    WinMine(QWidget* parent = 0);
private slots:
    void gameWin();
    void gameFail();
    void resetGame(int l = EASY_WINMINE);
    void normalGame();
    void hardGame();

};

#endif // MAINWINDOW_H

/*
    void gameWin()  (私有槽)
    赢得游戏后显示游戏获胜的提示

    void gameFail()  (私有槽)
    游戏失败后显示失败的提示

    void resetGame(int l = EASY_WINMINE)  (私有槽)
    重置游戏,重置默认为简单

    void normalGame()  (私有槽)
    该函数直接调用函数resetGame（）参数为NORMAL_WINMINE

    void hardGame()  (私有槽)
    该函数直接调用函数resetGame（）参数为HARD_WINMINE
 */
