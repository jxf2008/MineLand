#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>
#include <QPushButton>

class GameOverDialog : public QDialog
{
    Q_OBJECT
private:
    QPushButton* info_PushButton;
public:
    GameOverDialog(QWidget* parent = 0);
    void setInfo(const QString& str);
};

#endif // GAMEOVERDIALOG_H
