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

#include "qt_calculator.h"
#include <QtUiTools>

QT_calculator::QT_calculator(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
}

QT_calculator::~QT_calculator()
{

}

void QT_calculator::on_doubleSpinBox_valueChanged(double value)
{
	ui.label_6->setText(QString::number(value + ui.doubleSpinBox_2->value()));
}

void QT_calculator::on_doubleSpinBox_2_valueChanged(double value)
{
	ui.label_6->setText(QString::number(value + ui.doubleSpinBox->value()));
}
