#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->append("正在连接数据库...");
    QTimer::singleShot(200, this, SLOT(initConnect()));
}

MainWindow::~MainWindow()
{
    db7.close();
    db6.close();
    delete ui;
}

bool MainWindow::initConnect()
{
    if (createConnect())
    {
        ui->textEdit->append("数据库已连接!");
        QSqlQuery query7(db7);
        QSqlQuery query6(db6);
        query7.exec("SELECT * from passwd where user_name='SUCKBITCH@gd'");
        query6.exec("SELECT * from passwd where user_name='SUCKBITCH@gd'");
        QString user_name;
        QString active7;
        QString active6;
        while (query7.next())
        {
            user_name = query7.value(0).toString();
            active7 = query7.value(3).toString();
        }
        while (query6.next())
        {
            active6 = query6.value(3).toString();
        }
        if (active6 == "Y" && active6 == "Y")
        {
            active7 = "已激活";
        }
        else
        {
            active7 = "未激活";
            ui->activateBut->setEnabled(true);
        }
        ui->textEdit->append(QString("用户名:  ") + user_name);
        ui->textEdit->append(QString("状态:  ") + active7);
        return true;
    }
    else
    {
        ui->textEdit->append("无法连接数据库!");
        return false;
    }
    return false;
}

bool MainWindow::createConnect()
{
    db7 = QSqlDatabase::addDatabase("QMYSQL", QString("con7"));
    db7.setHostName("218.7.37.197");
    db7.setDatabaseName("radius");
    db7.setUserName("radius");
    db7.setPassword("guessme");
    if (!db7.open())
    {
        qDebug() << "not connected" << endl;
        QMessageBox::critical(0, "无法连接到数据库,请检查你的网络连接.",
                              db7.lastError().text());
        return false;
    }
    qDebug() << "connected" << QSqlDatabase::drivers() << endl;

    db6 = QSqlDatabase::addDatabase("QMYSQL", QString("con6"));
    db6.setHostName("218.7.37.196");
    db6.setDatabaseName("radius");
    db6.setUserName("radius");
    db6.setPassword("guessme");
    if (!db6.open())
    {
        qDebug() << "not connected" << endl;
        QMessageBox::critical(0, "无法连接到数据库,请检查你的网络连接.",
                              db6.lastError().text());
        return false;
    }
    qDebug() << "connected" << QSqlDatabase::drivers() << endl;
    return true;
}

bool MainWindow::on_activateBut_clicked()
{
    if (ui->activateBut->isEnabled())
    {
        ui->textEdit->append("激活中...");
        QTimer::singleShot(100, this, SLOT(activate()));
        return true;
    }
    return false;
}

