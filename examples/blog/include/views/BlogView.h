#pragma once

#include <LayoutedTemplateView>
#include <session/Session>
#include <views/Layout>

class BlogView : public LayoutedTemplateView {
	public:
		BlogView(Session* session);
	protected:
		const TemplatedLayout& getLayout() const;
		Layout layout;
};
