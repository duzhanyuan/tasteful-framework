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

#include <views/BlogPostList.h>

#include <controllers/BlogPostController.h>
#include <views/BlogPostPartial.h>

BlogPostList::BlogPostList(Session * session, const QHash<unsigned, BlogPost *> & blogPosts)
    : BlogView(session)
    , _blogPosts(blogPosts)
{
    setFilename("blogposttable.html");

    addTransform("blogposttable", &BlogPostList::blogPostTable);

    addTransform("newlink", [this](DomNode & node) {
            node("href") = url(&BlogPostController::create);
        });
}

void BlogPostList::blogPostTable(DomNode & node) const
{
    BlogPostPartial blogPostPartial(node["tr"][1].remove(), _session);

    for (unsigned id : _blogPosts.keys())
    {
        blogPostPartial.setData(_blogPosts.value(id), id);
        node << blogPostPartial;
    }
}
