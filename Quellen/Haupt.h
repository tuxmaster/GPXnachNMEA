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

#ifndef HAUPT_H
#define HAUPT_H

#include <QtCore>

class Haupt : public QObject
{
		Q_OBJECT
	public:
		explicit Haupt(QObject *eltern = 0);

	Q_SIGNALS:
		void	Beenden();

	public Q_SLOTS:
	private Q_SLOTS:
		void	Start();

};

#endif // HAUPT_H
