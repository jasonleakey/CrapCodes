#ifndef CLOGIN_H
#define CLOGIN_H

#include <QtGui/QDialog>
#include "ui_clogin.h"

class Clogin : public QDialog
{
    Q_OBJECT

public:
    Clogin(QWidget *parent = 0);
    ~Clogin();

private:
    Ui::CloginClass ui;
};

#endif // CLOGIN_H
