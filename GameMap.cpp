#include <QGridLayout>
#include <QtGlobal>
#include <QTime>
#include "GameMap.h"

#include <QDebug>

const int MINE_COUNT = 15; //按钮（每行）的数量

GameMap::GameMap(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout* main_Layout = new QGridLayout;

    for(int rows = 0 ; rows < MINE_COUNT ; ++rows)
    {
        for(int columns = 0 ; columns < MINE_COUNT ; ++ columns)
        {
            mine_List.append(new MineButton(rows,columns));
            mine_List.last()->setStyleSheet(tr("border:0xp"));
            main_Layout->addWidget(mine_List.last(),rows,columns);
            connect(mine_List.last(),SIGNAL(rightClicked()),this,SLOT(checkVictory()));
            connect(mine_List.last(),SIGNAL(clickMine()),this,SLOT(gameFail()));
            connect(mine_List.last(),SIGNAL(leftClicked(int,int)),this,SLOT(autoShowEmpty(int,int)));
        }
    }

    main_Layout->setSpacing(0);
    main_Layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(main_Layout);

    resetGame();
}

GameMap::~GameMap()
{

}

void GameMap::setGameLevel(int levels)
{
    qsrand(QTime::currentTime().msec());  //生成随机种子,随机数质量不是很高，但对于这个程序足够了
    gameLevel = levels;
    QList<int> mineIndex;
    while(true)
    {
        int s = qrand()%(MINE_COUNT*MINE_COUNT);
        if(!(mineIndex.contains(s)))
            mineIndex.append(s);
        if(mineIndex.count() == levels)
            break;
    }
    for(auto A : mineIndex)
        mine_List.at(A)->setButtonProperty(MineButton::Mine);
}

void GameMap::setNumberButton()
{
    for(int rows = 0 ; rows < MINE_COUNT ; ++rows)
    {
        for(int columns = 0 ; columns < MINE_COUNT ; ++ columns)
        {
            MineButton::buttonProperty bp = mine_List.at(rows*MINE_COUNT+columns)->getButtonProperty();
            if(bp == MineButton::Mine)  //计算一个按钮周围有几个是雷
                continue;
            int n = 0;
            if(rows-1 >= 0 && columns-1 >= 0)  //左上
            {
                if(mine_List.at((rows-1)*MINE_COUNT+(columns-1))->getButtonProperty() == MineButton::Mine)
                ++n;
            }
            if(rows-1 >= 0)  //上方
            {
                if(mine_List.at((rows-1)*MINE_COUNT+columns)->getButtonProperty() == MineButton::Mine)
                ++n;
            }
            if(rows-1 >= 0 && columns+1 < MINE_COUNT)  //右上
            {
                if(mine_List.at((rows-1)*MINE_COUNT+(columns+1))->getButtonProperty() == MineButton::Mine)
                ++n;
            }
            if(columns+1 < MINE_COUNT)  //右侧
            {
                if(mine_List.at(rows*MINE_COUNT+(columns+1))->getButtonProperty() == MineButton::Mine)
                ++n;
            }
            if(rows+1 < MINE_COUNT && columns+1 < MINE_COUNT)  //右下
            {
                if(mine_List.at((rows+1)*MINE_COUNT+(columns+1))->getButtonProperty() == MineButton::Mine)
                ++n;
            }
            if(rows+1 < MINE_COUNT)  //下方
            {
                if(mine_List.at((rows+1)*MINE_COUNT+columns)->getButtonProperty() == MineButton::Mine)
                ++n;
            }
            if(rows+1 < MINE_COUNT && columns-1 >= 0)  //左下
            {
                if(mine_List.at((rows+1)*MINE_COUNT+(columns-1))->getButtonProperty() == MineButton::Mine)
                ++n;
            }
            if(columns-1 >= 0)  //左侧
            {
                if(mine_List.at(rows*MINE_COUNT+(columns-1))->getButtonProperty() == MineButton::Mine)
                ++n;
            }
            if(n == 0)   //如果周围没有地雷，则不改变按钮属性（按钮属性默认为MineButton::Empty)
                continue;
            mine_List.at(rows*MINE_COUNT+columns)->setButtonProperty(MineButton::Number,n);
        }
    }
}

void GameMap::resetGame(int levels)
{
    for(auto A : mine_List)
        A->resetButton();
    setGameLevel(levels);
    setNumberButton();
}

void GameMap::checkVictory()
{
    int i = 0;
    for(auto A : mine_List)
    {
        if(A->findMine())
            ++i;
    }
    if(i == gameLevel)
        emit hasWin();
}

void GameMap::gameFail()
{
    for(auto A : mine_List)
    {
        if(A->getButtonProperty() == MineButton::Mine)
            A->simulateMouseLeftClick();
    }
    emit hasFail();
}

void GameMap::autoShowEmpty(int X , int Y)
{
    if(mine_List.at(X*MINE_COUNT+Y)->getButtonProperty() != MineButton::Empty)
        return;    //只有点击到空白按钮，才能自动展开
    for(int r = X ; r > 0 ; --r)  //这个循环用于逐行打开按钮所在行上面各行的空白按钮
    {
        auto A = mine_List.at((r-1)*MINE_COUNT+Y);
        if(A->hasOpened() || A->getButtonProperty() != MineButton::Empty)
            break;
        for(int i = Y ; i < MINE_COUNT ; ++i)  //一行分别向左和向右
        {
            auto A1 = mine_List.at((r-1)*MINE_COUNT+i);
            if(!A1->hasOpened() && A1->getButtonProperty() == MineButton::Empty)
                A1->simulateMouseLeftClick();
            else
                break;
        }
        for(int i = Y-1 ; i > 0 ; --i)
        {
            auto A1 = mine_List.at((r-1)*MINE_COUNT+i);
            if(!A1->hasOpened() && A1->getButtonProperty() == MineButton::Empty)
                A1->simulateMouseLeftClick();
            else
                break;
        }
    }

    for(int r = X ; r < MINE_COUNT ; ++r)  //这个循环用于逐行向下打开
    {
        auto A = mine_List.at(r*MINE_COUNT+Y);
        if(A->hasOpened() || A->getButtonProperty() != MineButton::Empty)
            break;
        for(int i = Y ; i < MINE_COUNT ; ++i)  //一行分别向左和向右
        {
            auto A1 = mine_List.at(r*MINE_COUNT+i);
            if(!A1->hasOpened() && A1->getButtonProperty() == MineButton::Empty)
                A1->simulateMouseLeftClick();
            else
                break;
        }
        for(int i = Y-1 ; i > 0 ; --i)
        {
            auto A1 = mine_List.at(r*MINE_COUNT+i);
            if(!A1->hasOpened() && A1->getButtonProperty() == MineButton::Empty)
                A1->simulateMouseLeftClick();
            else
                break;
        }
    }
}























































































































