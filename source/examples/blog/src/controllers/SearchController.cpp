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

#include <controllers/SearchController.h>

#include <models/BlogPost.h>
#include <views/SearchForm.h>
#include <views/SearchResult.h>

#include <tastefulserver/QVariantTree.h>

void SearchController::index()
{
    render(SearchForm(getSession()));
}

void SearchController::find()
{
    QString searchString = parameters["string"].value<QString>();

    if (searchString.isNull() || searchString.isEmpty())
    {
        render(SearchForm(getSession()));

        return;
    }

    QList<BlogPost *> searchResult;
    for (BlogPost * blogPost : BlogPost::find("1 ORDER BY id DESC"))
    {
        if (blogPost->title().contains(searchString, Qt::CaseInsensitive))
        {
            searchResult << blogPost;
        }
        else if (blogPost->text().contains(searchString, Qt::CaseInsensitive))
        {
            searchResult << blogPost;
        }
        else
        {
            // ~ for (Tag* tag : blogPost->getTags()) {
            // ~ if (tag->name().contains(searchString, Qt::CaseInsensitive)) {
            // ~ searchResult << blogPost;

            // ~ break;
            // ~ }
            // ~ }
        }
    }

    render(SearchResult(getSession(), searchResult, searchString));
}

void SearchController::findPost()
{
    find();
}
