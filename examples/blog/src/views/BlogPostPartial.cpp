#include <views/BlogPostPartial>

#include <controllers/BlogPostController>
#include <controllers/AllBlogPostController>

BlogPostPartial::BlogPostPartial(DomNode node, Session* session) : Partial(node), session(session), blogPost(nullptr), blogPostId(0) {
	addTransform("id", &BlogPostPartial::id);
	addTransform("title", &BlogPostPartial::title);
	addTransform("text", &BlogPostPartial::text);
	addTransform("shorttext", &BlogPostPartial::shortText);
	addTransform("showlink", &BlogPostPartial::showLink);
	addTransform("editlink", &BlogPostPartial::editLink);
	addTransform("deletelink", &BlogPostPartial::deleteLink);
}

void BlogPostPartial::setData(BlogPost* blogPost, unsigned blogPostId) {
	this->blogPost = blogPost;
	this->blogPostId = blogPostId;
}

void BlogPostPartial::id(DomNode& node) const {
	node.inner() = QString::number(blogPostId);
}

void BlogPostPartial::title(DomNode& node) const {
	node.inner() = blogPost->getTitle();
}

void BlogPostPartial::text(DomNode& node) const {
	node.inner() = blogPost->getText();
}

void BlogPostPartial::shortText(DomNode& node) const {
	node.inner() = blogPost->getText();
}

void BlogPostPartial::showLink(DomNode& node) const {
	if (session->isLoggedIn() && blogPost->getAuthor() == session->author) {
		node("href") = url(&BlogPostController::show, { { "id", blogPostId } });
	} else {
		node("href") = url(&AllBlogPostController::show, { { "id", blogPostId } });
	}
}

void BlogPostPartial::editLink(DomNode& node) const {
	node("href") = url(&BlogPostController::edit, { { "id", blogPostId } });
}

void BlogPostPartial::deleteLink(DomNode& node) const {
	node("href") = url(&BlogPostController::remove, { { "id", blogPostId } });
}
