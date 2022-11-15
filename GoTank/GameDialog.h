#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>

class QLabel;
class QPushButton;


class GameDialog : public QDialog
{
    Q_OBJECT
public:
    GameDialog(QWidget* parent = 0);

public:
    QLabel* label;
//    QPushButton* continueButton;
    QPushButton* quitButton;
};

#endif // GAMEDIALOG_H
