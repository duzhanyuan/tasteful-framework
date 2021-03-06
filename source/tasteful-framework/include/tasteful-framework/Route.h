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

#include <string>

#include <QString>
#include <QPair>
#include <QHash>
#include <QList>
#include <QRegExp>
#include <QVariantMap>
#include <QSharedPointer>

#include <tasteful-server/http.h>

#include <tasteful-framework/tasteful-framework_api.h>

#include <tasteful-framework/Action.h>

namespace tastefulframework {

class TASTEFUL_FRAMEWORK_API RequestedAction
{
public:
    RequestedAction();
    RequestedAction(const tastefulserver::HttpMethod & method, const QString & path);

    tastefulserver::HttpMethod getMethod() const;
    QString getPath() const;

private:
    tastefulserver::HttpMethod m_method;
    QString m_path;
};

class TASTEFUL_FRAMEWORK_API Route
{
public:
    Route(const tastefulserver::HttpMethod & method, const QString & urlPattern);

    static Route* create(const tastefulserver::HttpMethod & method, const QString & urlPattern);
    tastefulserver::HttpMethod getMethod() const;
    QString getUrlPattern() const;
    Action* getAction() const;
    void setAction(QSharedPointer<Action> action);

    virtual bool match(const RequestedAction & requestedAction) const = 0;
    virtual QString urlFor(const QVariantMap & parameters) const = 0;
    virtual bool isStatic() const;
    virtual bool isDynamic() const;
    virtual bool isWildcard() const;

protected:
    QString urlParameters(const QVariantMap & parameters) const;

    tastefulserver::HttpMethod m_method;
    QString m_urlPattern;
    QSharedPointer<Action> m_action;
};

class TASTEFUL_FRAMEWORK_API StaticRoute : public Route
{
public:
    StaticRoute(const tastefulserver::HttpMethod & method, const QString & urlPattern);

    virtual bool isStatic() const;
    virtual bool match(const RequestedAction & requestedAction) const;
    virtual QString urlFor(const QVariantMap & parameters) const;
};

class TASTEFUL_FRAMEWORK_API DynamicRoute : public Route
{
public:
    DynamicRoute(const tastefulserver::HttpMethod & method, const QString & urlPattern);

    virtual bool isDynamic() const;
    virtual bool match(const RequestedAction & requestedAction) const;
    virtual QString urlFor(const QVariantMap & parameters) const;

    QHash<QString, QString> getMatchedParts(const QString & path) const;

private:
    class UrlPart
    {
public:
        UrlPart(const QString & part);

        QString getName() const;
        bool isVariable() const;
        bool match(const QString & otherPart) const;

private:
        QString m_part;
        bool m_variable;
    };

    QList<UrlPart> m_urlParts;
};

class TASTEFUL_FRAMEWORK_API WildcardRoute : public Route
{
public:
    WildcardRoute(const tastefulserver::HttpMethod & method, const QString & urlPattern);

    virtual bool isWildcard() const;
    virtual bool match(const RequestedAction & requestedAction) const;
    virtual QString urlFor(const QVariantMap & parameters) const;

private:
    QRegExp m_regexp;
};

} // namespace tastefulframework
