#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QDialog>
#include <QList>
#include "MineButton.h"

class GameMap : public QDialog
{
    Q_OBJECT
private:
    QList<MineButton*> mine_List;
    int gameLevel;
public:
    GameMap(QWidget *parent = 0);
    ~GameMap();
    void setGameLevel(int levels);
    void setNumberButton();
    void resetGame(int levels = 10);
signals:
    void hasWin();
    void hasFail();
private slots:
    void checkVictory();
    void gameFail();
    void autoShowEmpty(int X , int Y);
};

#endif // GAMEMAP_H
/*
    void setGameLevel(int l)  (公有函数)
    设置游戏难度，参数为地雷的个数

    void setNumberButton()  (公有函数)
    当设置完地雷后，该调用该函数可以生成地雷周围的数字

    void resetGame()  (公有函数)
    初始化游戏(重新布置所有按钮)

    void hasWin()  (信号)
    获取胜利后发射该信号

    void checkVictory()  (私有槽)
    检查是否胜利(胜利的条件为右键标记出所有的地雷)

    void hasLost()  (信号)
    游戏失败时会发射该信号

    void gameFail()  (私有槽)
    点击到地雷后游戏失败，调用该槽，该槽会把未能标记的地雷显示出来，同时会发射信号hasFail()

    void autoShowEmpty()  (私有槽)
    点击到一个空白按钮是，自动展开附件的空白按钮
*/
