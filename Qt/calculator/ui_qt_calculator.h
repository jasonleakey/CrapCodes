/********************************************************************************
** Form generated from reading ui file 'qt_calculator.ui'
**
** Created: Sat Apr 24 01:18:07 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_QT_CALCULATOR_H
#define UI_QT_CALCULATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSplitter>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QT_calculatorClass
{
public:
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_4;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QWidget *QT_calculatorClass)
    {
        if (QT_calculatorClass->objectName().isEmpty())
            QT_calculatorClass->setObjectName(QString::fromUtf8("QT_calculatorClass"));
        QT_calculatorClass->resize(209, 62);
        horizontalLayout = new QHBoxLayout(QT_calculatorClass);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setMargin(11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter = new QSplitter(QT_calculatorClass);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        doubleSpinBox = new QDoubleSpinBox(widget);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setMaximum(2000);

        verticalLayout->addWidget(doubleSpinBox);

        splitter->addWidget(widget);
        label_2 = new QLabel(splitter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        splitter->addWidget(label_2);
        widget1 = new QWidget(splitter);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        doubleSpinBox_2 = new QDoubleSpinBox(widget1);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));

        verticalLayout_2->addWidget(doubleSpinBox_2);

        splitter->addWidget(widget1);
        label_4 = new QLabel(splitter);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        splitter->addWidget(label_4);
        widget2 = new QWidget(splitter);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        verticalLayout_3 = new QVBoxLayout(widget2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setMargin(11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_3->addWidget(label_5);

        label_6 = new QLabel(widget2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFrameShape(QFrame::Box);
        label_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(label_6);

        splitter->addWidget(widget2);

        horizontalLayout->addWidget(splitter);


        retranslateUi(QT_calculatorClass);

        QMetaObject::connectSlotsByName(QT_calculatorClass);
    } // setupUi

    void retranslateUi(QWidget *QT_calculatorClass)
    {
        QT_calculatorClass->setWindowTitle(QApplication::translate("QT_calculatorClass", "QT_calculator", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QT_calculatorClass", "Input 1", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("QT_calculatorClass", "+", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("QT_calculatorClass", "Input 2", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("QT_calculatorClass", "=", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("QT_calculatorClass", "output", 0, QApplication::UnicodeUTF8));
        label_6->setText(QString());
        Q_UNUSED(QT_calculatorClass);
    } // retranslateUi

};

namespace Ui {
    class QT_calculatorClass: public Ui_QT_calculatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_CALCULATOR_H
