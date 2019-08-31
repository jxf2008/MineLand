#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class MineButton : public QPushButton
{
    Q_OBJECT
public:
    enum buttonProperty{Mine,Number,Empty}; //按钮的3种属性，地雷，数字，空白
private:
    int X;
    int Y;
    bool hasLeftClicked;
    bool hasRightClickedFlag;
    int thisNumber;
    buttonProperty thisProperty;
    void setButtonPix();
public:
    MineButton(int x , int y ,QWidget* parent = 0);
    void setButtonProperty(MineButton::buttonProperty p , int m = 0);
    MineButton::buttonProperty getButtonProperty()const;
    void simulateMouseLeftClick();
    bool findMine()const;
    void resetButton();
    bool hasOpened()const;
protected:
    void mousePressEvent(QMouseEvent* event);
signals:
    void leftClicked(int,int);
    void rightClicked();
    void clickMine();
};

#endif // MINEBUTTON_H
/*
  void setButtonPix()  (私有函数)
  根据按钮的属性来设置图片

  void setButtonProperty(MineButton::buttonProperty p , int m = 0)  (公有函数)
  该函数设定按钮的属性，地雷，数字，空白，参数为枚举buttonProperty,第二个参数为数字，当属性为数字时的具体值

  MineButton::buttonProperty getButtonProperty()const  (公有函数)
  返回该按钮的属性

  void simulateMouseLeftClick()  (公有函数)
  该函数修改类成员hasLeftClicked的值为true，同时重新设置图片，效果等同于鼠标左键点击

  bool findMine()const  (公有函数)
  如果鼠标右键该按钮，并且该按钮为地雷(即标记了正确的地雷)，则返回true,否则返回false

  void resetButton()  (公有函数)
  初始化按钮

  bool hasOpened()  (公有函数)
  返回该按钮是否被左键点开

  void leftClicked()  (信号)
  鼠标左键点击发射的信号,因为不是每次左键点击都会发射信号，所以无法用按钮自带的clicked()信号

  void rightClicked()  (信号)
  鼠标右键点击发射的信号

  void clickMine()  (信号)
  鼠标左键点击到了地雷，发射该信号，游戏失败
*/
