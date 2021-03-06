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

#include <tasteful-framework/FrontController.h>

#include <QDir>

#include <tasteful-server/http.h>

#include <tasteful-framework/Logger.h>

namespace tastefulframework {

FrontController::FrontController()
{
}

tastefulserver::HttpResponse FrontController::handleRequest(const tastefulserver::HttpRequest & httpRequest)
{
    Request request(httpRequest);

    request.obtainSessionFrom(&m_sessionPool);
    Response response = dispatch(request);
    response.setSession(request.getSession());

    return response.asHttpResponse();
}

Response FrontController::dispatch(Request & request)
{
    QFile file("public:" + request.getPath().mid(1));

    if (canDeliver(file))
    {
        return Response::forFile(file);
    }

    Response response = m_dispatcher.dispatch(request);
    checkContent(response);

    return response;
}

void FrontController::checkContent(Response & response) const
{
    if ((response.getStatusCode()>=400) && response.getContent().isEmpty())
    {
        QString filename = QString("public:%1.html").arg(response.getStatusCode());
        if (QFileInfo(filename).exists())
        {
            response.setContentFromFile(filename);
            logger() << "replaced content with " << QFileInfo(filename).baseName();
        }
    }
}

bool FrontController::canDeliver(const QFile & file) const
{
    QFileInfo fileInfo(file);
    QString absolutePath = fileInfo.absolutePath() + "/";
    bool foundMatch = false;

    for (QString & publicDir : QDir::searchPaths("public"))
    {
        if (absolutePath.startsWith(QDir(publicDir).absolutePath() + "/"))
        {
            foundMatch = true;
            break;
        }
    }

    return foundMatch && fileInfo.exists() && fileInfo.isFile() && fileInfo.isReadable();
}

} // namespace tastefulframework
