#include "MineButton.h"

const int MINE_BUTTON_SIZE = 50;

MineButton::MineButton(int x , int y , QWidget* parent):QPushButton(parent)
{
    X = x;
    Y = y;

    setFixedSize(MINE_BUTTON_SIZE,MINE_BUTTON_SIZE);
    hasLeftClicked = false;
    hasRightClickedFlag = false;
    thisNumber = 0;
    thisProperty = MineButton::Empty;
    setButtonPix();
}

void MineButton::setButtonPix()
{
    if(!hasLeftClicked)
        setIcon(QIcon(tr(":/images/empty.png")));
    if(hasRightClickedFlag)
        setIcon(QIcon(tr(":/images/know.png")));
    if(hasLeftClicked)
    {
        if(thisProperty == MineButton::Mine)
            setIcon(QIcon(tr(":/images/bomber.png")));
        if(thisProperty == MineButton::Number)
        {
            QString nus = tr(":/images/") + QString::number(thisNumber) + tr(".png");
            setIcon(QIcon(nus));
        }
        if(thisProperty == MineButton::Empty)
            setIcon(QIcon(tr(":/images/cd.png")));
    }

    setIconSize(QSize(MINE_BUTTON_SIZE,MINE_BUTTON_SIZE));
}

void MineButton::setButtonProperty(MineButton::buttonProperty p , int m)
{
    thisProperty = p;
    thisNumber = m;
    setButtonPix();
}

MineButton::buttonProperty MineButton::getButtonProperty()const
{
    return thisProperty;
}

void MineButton::simulateMouseLeftClick()
{
    hasLeftClicked = true;
    setButtonPix();
}

void MineButton::mousePressEvent(QMouseEvent* event)
{
    if(hasLeftClicked)
    {
        QPushButton::mousePressEvent(event);
        return;
    }
    if(event->button() == Qt::LeftButton)
    {
        if(!hasLeftClicked and thisProperty == MineButton::Mine)
            emit clickMine();
        if(!hasLeftClicked)
            emit leftClicked(X,Y);
        hasLeftClicked = true;    
    }
    else if(event->button() == Qt::RightButton)
    {
        if(hasRightClickedFlag)
            hasRightClickedFlag = false;
        else
        {
            hasRightClickedFlag = true;
            emit rightClicked();
        }
    }
    setButtonPix();
    QPushButton::mousePressEvent(event);
}

bool MineButton::findMine()const
{
    if(hasRightClickedFlag && thisProperty == MineButton::Mine)
        return true;
    else
        return false;
}

void MineButton::resetButton()
{
    hasLeftClicked = false;
    hasRightClickedFlag = false;
    thisNumber = 0;
    thisProperty = MineButton::Empty;
    setButtonPix();
}

bool MineButton::hasOpened()const
{
    return hasLeftClicked;
}















































































































































































