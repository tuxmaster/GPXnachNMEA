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

#include <QtCore>

#include "Haupt.h"

int main(int argc, char *argv[])
{
	QCoreApplication Anwendung(argc, argv);

	QTranslator UebersetzerQt;
	UebersetzerQt.load(QString("qt_%1").arg(QLocale::system().name()),QLibraryInfo::location(QLibraryInfo::TranslationsPath));

	Anwendung.installTranslator(&UebersetzerQt);

	Anwendung.setApplicationVersion(VERSION);
	Anwendung.setApplicationName(Anwendung.arguments()[0]);

	QCommandLineParser Komandozeile;

	Komandozeile.addVersionOption();
	Komandozeile.addHelpOption();
	Komandozeile.setApplicationDescription(QCoreApplication::tr("Konvertiert eine GPX Datei in eine NMEA 0183 Datei."));
	Komandozeile.addPositionalArgument(EINGABE,QCoreApplication::tr("Die .gpx Datei."));
	Komandozeile.addPositionalArgument(AUSGABE,QCoreApplication::tr("Die .nmea Datei."));

	Komandozeile.process(Anwendung);

	if (Komandozeile.positionalArguments().size()!=2)
		Komandozeile.showHelp(1);

	Haupt *los=new Haupt(&Anwendung,Komandozeile.positionalArguments()[0],Komandozeile.positionalArguments()[1]);
	QObject::connect(los,SIGNAL(Beenden()),&Anwendung,SLOT(quit()));

	return Anwendung.exec();
}
