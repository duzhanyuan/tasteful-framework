/**
 * (C) LGPL-3
 *
 * Tasteful Framework <https://github.com/scheibel/tasteful-framework>
 *
 * Copyright: 2012-2014 Lux, Scheibel
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

#include <QString>
#include <QHash>

#include <tasteful-server/ContentType.h>

#include <tasteful-framework/tasteful-framework_api.h>

namespace tastefulframework {

class TASTEFUL_FRAMEWORK_API MimeDatabase
{
public:
    MimeDatabase();

    static QString mimeTypeFor(const QString & suffix, const QString & defaultValue = "");
    static QString mimeTypeForFilename(const QString & filename, const QString & defaultValue = "");
    static tastefulserver::ContentType contentTypeFor(const QString & suffix, const QString & defaultValue = "");
    static tastefulserver::ContentType contentTypeForFilename(const QString & filename, const QString & defaultValue = "");

protected:
    QString getMimeTypeFor(const QString & filename, const QString & defaultValue) const;
    void addMimeType(const QString & mimeType, const QString & extension);
    void loadMimeTypes();
    void loadMimeTypesFromFilename(const QString & filename);

private:
    static MimeDatabase s_instance;
    QHash<QString, QString> m_mimeTypes;
};

} // namespace tastefulframework
