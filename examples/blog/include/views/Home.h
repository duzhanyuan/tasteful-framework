#pragma once

#include <views/BlogView>
#include <models/BlogPost>
#include <QList>

class Home : public BlogView {
	public:
		Home(Session* session, QList<BlogPost*> blogPosts);
		
		void recentPosts(DomNode& node) const;
	private:
		QList<BlogPost*> blogPosts;
};
