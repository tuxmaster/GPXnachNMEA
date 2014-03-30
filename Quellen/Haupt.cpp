/*
	Copyright (C) 2014 Frank Büttner frank-buettner@gmx.net

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include "Haupt.h"

Haupt::Haupt(QObject *eltern, const QString &eingabedatei, const QString &ausgabedatei) : QObject(eltern),K_Eingabedatei(eingabedatei),K_Ausgabedatei(ausgabedatei)
{
	QTimer::singleShot(0,this,SLOT(Start()));
}
void Haupt::Start()
{
	qDebug()<<K_Eingabedatei;
	qDebug()<<K_Ausgabedatei;
	Q_EMIT Beenden();
}
