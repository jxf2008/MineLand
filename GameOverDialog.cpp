#include <QHBoxLayout>
#include "GameOverDialog.h"

const int WIDTH_GAMEOVERDIALOG = 200;
const int HEIGHT_GAMEOVERDIALOG = 100;
const int FONT_SIZE_GAMEOVERDIALOG = 30;

GameOverDialog::GameOverDialog(QWidget* parent):QDialog(parent)
{
    info_PushButton = new QPushButton;

    info_PushButton->setFixedSize(WIDTH_GAMEOVERDIALOG,HEIGHT_GAMEOVERDIALOG);
    QFont ft;
    ft.setPointSize(FONT_SIZE_GAMEOVERDIALOG);
    info_PushButton->setFont(ft);

    QHBoxLayout* main_Layout = new QHBoxLayout;
    main_Layout->addWidget(info_PushButton,0,Qt::AlignCenter);
    main_Layout->setSpacing(0);
    setLayout(main_Layout);
    main_Layout->setSizeConstraint(QLayout::SetFixedSize);

    //setWindowFlags(Qt::CustomizeWindowHint);

    connect(info_PushButton,SIGNAL(clicked()),this,SLOT(hide()));
}

void GameOverDialog::setInfo(const QString &str)
{
    info_PushButton->setText(str);
}
