#include "GameDialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>


GameDialog::GameDialog(QWidget *parent)
    : QDialog(parent)
{
    label = new QLabel(tr("Game Over!"));
    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(label);

//    continueButton = new QPushButton(tr("Continue"));
    quitButton = new QPushButton(tr("quit"));

    QHBoxLayout* bottomLayout = new QHBoxLayout;
//    bottomLayout->addWidget(continueButton);
    bottomLayout->addWidget(quitButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);
}
