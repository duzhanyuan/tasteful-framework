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

#include <tastefulframework/TemplateView.h>
#include <tastefulframework/MimeDatabase.h>
#include <QFileInfo>

TemplateView::TemplateView(const QString& filename) : filename(filename) {
}

void TemplateView::setFilename(const QString& filename) {
	this->filename = filename;
}

void TemplateView::renderOn(Response& response) const {
	View::renderOn(response);
	
	response.setMimeTypeForFileName(filename);
}

QByteArray TemplateView::content() const {
	QByteArray content = transformFile(filename).toString().toUtf8();
	
	if (MimeDatabase::contentTypeForFilename(filename, "text/plain").is("text", "html")) {
		content.prepend("<!DOCTYPE html>\n");
	}
	
	return content;
}