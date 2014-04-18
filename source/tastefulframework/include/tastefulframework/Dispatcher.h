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

#include <tastefulframework/Route.h>
#include <tastefulframework/RouteRegistry.h>
#include <tastefulframework/Action.h>
#include <tastefulframework/Response.h>
#include <tastefulframework/Request.h>
#include <QString>
#include <QHash>
#include <QObject>

#include <tastefulframework/tastefulframework_api.h>

namespace tastefulframework {

class TASTEFULFRAMEWORK_API Dispatcher : public QObject
{
    Q_OBJECT

public:
    Dispatcher();

    Response dispatch(Request & request) const;

private slots:
    void addRoute(Route * route);

private:
    void initializeRoutes();

    Response defaultDispatch(Request & request) const;

    Route* findMatch(const RequestedAction & requestedAction) const;
    Route* findStaticMatch(const RequestedAction & requestedAction) const;
    Route* findDynamicMatch(const RequestedAction & requestedAction) const;
    Route* findWildcardMatch(const RequestedAction & requestedAction) const;

    Response performActionFor(Route * route, Request & request) const;

    QHash<RouteRegistry::Key, Route *> m_staticRoutes;
    QList<Route *> m_dynamicRoutes;
    QList<Route *> m_wildcardRoutes;
};

} // namespace tastefulframework
