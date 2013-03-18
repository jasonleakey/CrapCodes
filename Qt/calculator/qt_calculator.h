/*
 *  CPP_practice - TODO
 *
 *  Feb 6, 2010
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  --------------------------------------------------------------------
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */

#ifndef QT_CALCULATOR_H
#define QT_CALCULATOR_H

#include <QtGui/QWidget>
#include "ui_qt_calculator.h"


class QT_calculator : public QWidget
{
    Q_OBJECT

public:
    QT_calculator(QWidget *parent = 0);
    ~QT_calculator();

private:
    Ui::QT_calculatorClass ui;

private slots:
	void on_doubleSpinBox_valueChanged(double value);
	void on_doubleSpinBox_2_valueChanged(double value);
};

#endif // QT_CALCULATOR_H
