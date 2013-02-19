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

#include <QString>
#include <View>
#include <Request>
#include <Response>
#include <internal/SessionContainer>
#include <Cookie>
#include <UrlHelper>
#include <QHash>

using namespace internal;

class Controller : public SessionContainer, public UrlHelper {
	public:
		Controller();
		virtual ~Controller();

		virtual void initialize(Request& request);
		virtual bool beforeAction();
		virtual void afterAction();
		virtual const Response& getResponse() const;

		const RequestParameters& getParameters() const;
		RequestParameters& getParameters();
		const Cookies& getCookies() const;
		Cookies& getCookies();
	protected:
		void render(const View& view);
		void renderWithLayout(const QString& templateFile, const QString& layoutFile);
		void redirect(const QString& url);

		Response response;
		RequestParameters parameters;
		Cookies cookies;
};
