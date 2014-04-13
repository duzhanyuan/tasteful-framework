/**
 * (C) LGPL-3
 *
 * Tasteful Framework <https://github.com/scheibel/tasteful-framework>
 *
 * Copyright: 2012 Lux, Scheibel
 * Authors:
 *     Roland Lux <rollux2000@googlemail.com>
 *     Willy Scheibel <willyscheibel@gmx.de>
 *
 * This file is part of Tasteful Framework.
 *
 * Tasteful Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tasteful Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Tasteful Framework.  If not, see <http://www.gnu.org/licenses/>.
 **/

#pragma once

#include <tastefulframework/WebAppConfig.h>

#include <QXmlSimpleReader>

#include <tastefulframework/tastefulframework_api.h>

class TASTEFULFRAMEWORK_API WebAppConfigReader : public QObject
{
    Q_OBJECT

public:
    WebAppConfigReader(const QString & filename);

    WebAppConfig parse();

    QString getFilename() const;

private slots:
    void startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts);
    void endElement(const QString & namespaceURI, const QString & localName, const QString & qName);
    void characters(const QString & ch);

private:
    QString filename;
    QStringList pathElements;
    QString path;
    QString element;
    WebAppConfig config;

    void handleApplication(const QString & ch);
    void handleDirectories(const QString & ch);
    void handleServer(const QString & ch);
    void handleDatabase(const QString & ch);
};
