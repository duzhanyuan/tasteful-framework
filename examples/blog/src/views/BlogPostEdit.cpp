#include <views/BlogPostEdit>
#include <controllers/BlogPostController>

BlogPostEdit::BlogPostEdit(Session* session, BlogPost* blogPost, unsigned id) : BlogView(session), blogPost(blogPost), id(id) {
	setFilename("blogpostedit.html");
	
	addTransform("blogeditform", &BlogPostEdit::blogEditForm);
	addTransform("blogpostid", &BlogPostEdit::blogPostId);
	addTransform("blogposttitle", &BlogPostEdit::blogPostTitle);
	addTransform("blogposttext", &BlogPostEdit::blogPostText);
	addTransform("savebuttontext", &BlogPostEdit::saveButtonText);
	addTransform("backurl", &BlogPostEdit::backUrl);
}

void BlogPostEdit::backUrl(DomNode& node) const {
	node("href") = url(&BlogPostController::index);
}

void BlogPostEdit::blogEditForm(DomNode& node) const {
	node("action") = url(&BlogPostController::save);
}

void BlogPostEdit::blogPostId(DomNode& node) const {
	node("value") = id;
}

void BlogPostEdit::blogPostTitle(DomNode& node) const {
	if (blogPost) {
		node("value") = blogPost->getTitle();
	} else {
		node("value") = "Insert title here";
	}
}

void BlogPostEdit::blogPostText(DomNode& node) const {
	if (blogPost) {
		node.inner() = blogPost->getText();
	} else {
		node.inner() = " ";
	}
}

void BlogPostEdit::saveButtonText(DomNode& node) const {
	node("value") = (id == 0) ? "Create" : "Save";
}
