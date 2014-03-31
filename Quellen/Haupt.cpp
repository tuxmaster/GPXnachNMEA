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
	K_Positionen=new QList<QGeoPositionInfo>;
	connect(this,SIGNAL(Fehler(QString)),this,SLOT(Fehlerbehandlung(QString)));
	QTimer::singleShot(0,this,SLOT(Start()));
}
Haupt::~Haupt()
{
	delete K_Positionen;
}

void Haupt::Start()
{
	QFile GPX_Datei(K_Eingabedatei);
	if (!GPX_Datei.open(QFile::ReadOnly))
	{
		Q_EMIT Fehler(tr("Fehler beim öffnen der Datei %1.\n%2").arg(K_Eingabedatei).arg(GPX_Datei.errorString()));
		return;
	}
	QXmlStreamReader XML(&GPX_Datei);
	QDateTime Zeitstempel;
	double Kurs=0;
	double Geschwindigkeit=0;
	QGeoCoordinate Position;
	while (!XML.atEnd())
	{
		if(XML.tokenType()==QXmlStreamReader::StartElement)
		{
			if (XML.name()=="trkpt")
			{
				while (!((XML.tokenType()==QXmlStreamReader::EndElement)&&(XML.name()=="trkpt")))
				{
					if(XML.name()=="trkpt")
						Position=QGeoCoordinate(XML.attributes().value("lat").toDouble(),XML.attributes().value("lon").toDouble());
					if((XML.name()=="ele")&&(XML.tokenType()==QXmlStreamReader::StartElement))
						Position.setAltitude(XML.readElementText().toDouble());
					if((XML.name()=="time")&&(XML.tokenType()==QXmlStreamReader::StartElement))
						Zeitstempel=QDateTime::fromString(XML.readElementText(),Qt::ISODate);
					if((XML.name()=="extensions")&&(XML.tokenType()==QXmlStreamReader::StartElement))
					{
						while(!((XML.tokenType()==QXmlStreamReader::EndElement)&&(XML.name()=="extensions")))
						{
							if(((XML.name()=="course")&&(XML.prefix()=="nmea"))&&(XML.tokenType()==QXmlStreamReader::StartElement))
								Kurs=XML.readElementText().toDouble();
							if(((XML.name()=="speed")&&(XML.prefix()=="nmea"))&&(XML.tokenType()==QXmlStreamReader::StartElement))
								Geschwindigkeit=XML.readElementText().toDouble()*0.514444; //Knoten ->m/sec
							XML.readNext();
						}
					}
					XML.readNext();
				}
				QGeoPositionInfo Positionsinfo(Position,Zeitstempel);
				Positionsinfo.setAttribute(QGeoPositionInfo::MagneticVariation,Kurs);
				Positionsinfo.setAttribute(QGeoPositionInfo::GroundSpeed,Geschwindigkeit);
				K_Positionen->append(Positionsinfo);
			}
		}
		XML.readNext();
	}
	GPX_Datei.close();
	Q_EMIT Beenden();
}
void Haupt::Fehlerbehandlung(const QString &fehler)
{
	qDebug()<<fehler;
	Q_EMIT Beenden();
}
