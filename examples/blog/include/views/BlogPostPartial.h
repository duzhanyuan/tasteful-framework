#pragma once

#include <Partial>
#include <models/BlogPost>

class BlogPostPartial : public Partial {
	public:
		BlogPostPartial(DomNode node);
	
		void setData(BlogPost* blogPost, unsigned blogPostId);
		
		void id(DomNode& node) const;
		void title(DomNode& node) const;
		void text(DomNode& node) const;
		void shortText(DomNode& node) const;
		void showLink(DomNode& node) const;
		void editLink(DomNode& node) const;
		void deleteLink(DomNode& node) const;
	private:
		BlogPost* blogPost;
		unsigned blogPostId;
};
