/********************************************************************************
** Form generated from reading ui file 'clogin.ui'
**
** Created: Sat Apr 24 01:18:07 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CLOGIN_H
#define UI_CLOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CloginClass
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *CloginClass)
    {
        if (CloginClass->objectName().isEmpty())
            CloginClass->setObjectName(QString::fromUtf8("CloginClass"));
        CloginClass->resize(228, 105);
        horizontalLayout_2 = new QHBoxLayout(CloginClass);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setMargin(11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(CloginClass);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(CloginClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(CloginClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(CloginClass);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(CloginClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(CloginClass);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(CloginClass);
        QObject::connect(pushButton_2, SIGNAL(clicked()), CloginClass, SLOT(close()));

        QMetaObject::connectSlotsByName(CloginClass);
    } // setupUi

    void retranslateUi(QDialog *CloginClass)
    {
        CloginClass->setWindowTitle(QApplication::translate("CloginClass", "Clogin", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CloginClass", "User Name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CloginClass", "Password", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("CloginClass", "OK", 0, QApplication::UnicodeUTF8));
        pushButton->setShortcut(QApplication::translate("CloginClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("CloginClass", "Cancel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CloginClass);
    } // retranslateUi

};

namespace Ui {
    class CloginClass: public Ui_CloginClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOGIN_H
