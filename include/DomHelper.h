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

#include <functional>
#include <QString>
#include <QList>
#include <QDomDocument>

#define CUSTOM_TAG(tagname) template <typename... Args> NodeCreator tagname (Args... args) const

#define SUPPORT_TAG(tagname) \
	CUSTOM_TAG(tagname) {\
		return tag(#tagname)(args...);\
	}

#define SUPPORT_ATTRIBUTE(attributename) \
	TagModifier attributename(const QString& attributename) const {\
		return attribute(#attributename, attributename);\
	}


class DomNode;

typedef std::function<void(QDomElement&)> TagModifier;

class NodeCreatorPlaceholder;

class NodeCreator {
	public:
		NodeCreator();
		NodeCreator(const QString& name);
		NodeCreator(const NodeCreatorPlaceholder& placeholder);

		void add() { /*ignore*/ }
		template <typename T, typename... Args> void add(T t, Args... args) {
			addModifier(t);
			add(args...);
		}

		QDomElement operator()(QDomDocument doc) const;
		void operator()(QDomNode node) const;
	private:
		void addModifier(TagModifier modifier);
		void addModifier(const NodeCreator& creator);
		void addModifier(const NodeCreatorPlaceholder& creatorPlaceholder);

		void addModifier(const DomNode& node);
		void addModifier(const QDomNode& node);

		void addModifier(const QString& text);
		void addModifier(const char* text);
		void addModifier(int i);
		void addModifier(unsigned u);
		void addModifier(long i);
		void addModifier(double d);

		QString name;
		QList<TagModifier> modifiers;
		bool null;
};

class NodeCreatorPlaceholder {
	public:
		NodeCreatorPlaceholder(const QString& name) : name(name) {};

		template <typename... Args>
		NodeCreator operator()(Args... args) const {
			NodeCreator NodeCreator(name);
			NodeCreator.add(args...);
			return NodeCreator;
		}
	private:
		QString name;
};

class DomHelper {
	public:
		QDomDocument loadDocument(const QString& filename) const;

		NodeCreatorPlaceholder tag(const QString& name) const;
		TagModifier attribute(const QString& name, const QString& value) const;

		// convenience attributes
		TagModifier cssClass(const QString& name) const;

		// convenience tags
		CUSTOM_TAG(formbutton) { return input(type("button"), args...); }
		CUSTOM_TAG(checkbox) { return input(type("checkbox"), args...); }
		CUSTOM_TAG(file) { return input(type("file"), args...); }
		CUSTOM_TAG(hidden) { return input(type("hidden"), args...); }
		CUSTOM_TAG(imagebutton) { return input(type("image"), args...); }
		CUSTOM_TAG(password) { return input(type("password"), args...); }
		CUSTOM_TAG(radiobutton) { return input(type("radio"), args...); }
		CUSTOM_TAG(resetbutton) { return input(type("reset"), args...); }
		CUSTOM_TAG(submitbutton) { return input(type("submit"), args...); }
		CUSTOM_TAG(textfield) { return input(type("text"), args...); }
		CUSTOM_TAG(colorchooser) { return input(type("color"), args...); }
		CUSTOM_TAG(datepicker) { return input(type("date"), args...); }
		CUSTOM_TAG(datetimepicker) { return input(type("datetime"), args...); }
		CUSTOM_TAG(localdatetimepicker) { return input(type("datetime-local"), args...); }
		CUSTOM_TAG(emailfield) { return input(type("email"), args...); }
		CUSTOM_TAG(monthpicker) { return input(type("month"), args...); }
		CUSTOM_TAG(numberfield) { return input(type("number"), args...); }
		CUSTOM_TAG(rangeslider) { return input(type("range"), args...); }
		CUSTOM_TAG(searchfield) { return input(type("search"), args...); }
		CUSTOM_TAG(telephonefield) { return input(type("tel"), args...); }
		CUSTOM_TAG(timefield) { return input(type("time"), args...); }
		CUSTOM_TAG(urlfield) { return input(type("url"), args...); }
		CUSTOM_TAG(weekpicker) { return input(type("week"), args...); }

		SUPPORT_ATTRIBUTE(name)
		SUPPORT_ATTRIBUTE(id)
		SUPPORT_ATTRIBUTE(href)
		SUPPORT_ATTRIBUTE(type)
		SUPPORT_ATTRIBUTE(rel)
		SUPPORT_ATTRIBUTE(value)

		SUPPORT_TAG(a)
		SUPPORT_TAG(abbr)
		SUPPORT_TAG(acronym)
		SUPPORT_TAG(address)
		SUPPORT_TAG(applet)
		SUPPORT_TAG(area)
		SUPPORT_TAG(article)
		SUPPORT_TAG(aside)
		SUPPORT_TAG(audio)
		SUPPORT_TAG(b)
		SUPPORT_TAG(base)
		SUPPORT_TAG(basefont)
		SUPPORT_TAG(bdi)
		SUPPORT_TAG(bdo)
		SUPPORT_TAG(big)
		SUPPORT_TAG(blockquote)
		SUPPORT_TAG(body)
		SUPPORT_TAG(br)
		SUPPORT_TAG(button)
		SUPPORT_TAG(canvas)
		SUPPORT_TAG(caption)
		SUPPORT_TAG(center)
		SUPPORT_TAG(cite)
		SUPPORT_TAG(code)
		SUPPORT_TAG(col)
		SUPPORT_TAG(colgroup)
		SUPPORT_TAG(command)
		SUPPORT_TAG(datalist)
		SUPPORT_TAG(dd)
		SUPPORT_TAG(del)
		SUPPORT_TAG(details)
		SUPPORT_TAG(dfn)
		SUPPORT_TAG(dir)
		SUPPORT_TAG(div)
		SUPPORT_TAG(dl)
		SUPPORT_TAG(dt)
		SUPPORT_TAG(em)
		SUPPORT_TAG(embed)
		SUPPORT_TAG(fieldset)
		SUPPORT_TAG(figcaption)
		SUPPORT_TAG(figure)
		SUPPORT_TAG(font)
		SUPPORT_TAG(footer)
		SUPPORT_TAG(form)
		SUPPORT_TAG(frame)
		SUPPORT_TAG(frameset)
		SUPPORT_TAG(h1)
		SUPPORT_TAG(h2)
		SUPPORT_TAG(h3)
		SUPPORT_TAG(h4)
		SUPPORT_TAG(h5)
		SUPPORT_TAG(h6)
		SUPPORT_TAG(head)
		SUPPORT_TAG(header)
		SUPPORT_TAG(hgroup)
		SUPPORT_TAG(hr)
		SUPPORT_TAG(html)
		SUPPORT_TAG(i)
		SUPPORT_TAG(iframe)
		SUPPORT_TAG(img)
		SUPPORT_TAG(input)
		SUPPORT_TAG(ins)
		SUPPORT_TAG(keygen)
		SUPPORT_TAG(kbd)
		SUPPORT_TAG(label)
		SUPPORT_TAG(legend)
		SUPPORT_TAG(li)
		SUPPORT_TAG(link)
		SUPPORT_TAG(map)
		SUPPORT_TAG(mark)
		SUPPORT_TAG(menu)
		SUPPORT_TAG(meta)
		SUPPORT_TAG(meter)
		SUPPORT_TAG(nav)
		SUPPORT_TAG(noframes)
		SUPPORT_TAG(noscript)
		SUPPORT_TAG(object)
		SUPPORT_TAG(ol)
		SUPPORT_TAG(optgroup)
		SUPPORT_TAG(option)
		SUPPORT_TAG(output)
		SUPPORT_TAG(p)
		SUPPORT_TAG(param)
		SUPPORT_TAG(pre)
		SUPPORT_TAG(progress)
		SUPPORT_TAG(q)
		SUPPORT_TAG(rp)
		SUPPORT_TAG(rt)
		SUPPORT_TAG(ruby)
		SUPPORT_TAG(s)
		SUPPORT_TAG(samp)
		SUPPORT_TAG(script)
		SUPPORT_TAG(section)
		SUPPORT_TAG(select)
		SUPPORT_TAG(small)
		SUPPORT_TAG(source)
		SUPPORT_TAG(span)
		SUPPORT_TAG(strike)
		SUPPORT_TAG(strong)
		SUPPORT_TAG(style)
		SUPPORT_TAG(sub)
		SUPPORT_TAG(summary)
		SUPPORT_TAG(sup)
		SUPPORT_TAG(table)
		SUPPORT_TAG(tbody)
		SUPPORT_TAG(td)
		SUPPORT_TAG(textarea)
		SUPPORT_TAG(tfoot)
		SUPPORT_TAG(th)
		SUPPORT_TAG(thead)
		SUPPORT_TAG(time)
		SUPPORT_TAG(title)
		SUPPORT_TAG(tr)
		SUPPORT_TAG(track)
		SUPPORT_TAG(tt)
		SUPPORT_TAG(u)
		SUPPORT_TAG(ul)
		SUPPORT_TAG(var)
		SUPPORT_TAG(video)
		SUPPORT_TAG(wbr)
};
