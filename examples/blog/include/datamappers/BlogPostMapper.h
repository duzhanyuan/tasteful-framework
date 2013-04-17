#pragma once

#include <models/BlogPost.h>

#include <DataMapper>

class BlogPostMapper : public DataMapper<BlogPostMapper, BlogPost, unsigned> {
	public:
		BlogPostMapper();
		~BlogPostMapper();
		
		void buildFromRecord(BlogPost* model, const QVariantMap& record) const;
		void buildRecordFrom(BlogPost* model, QVariantMap& record) const;
		QList<QString> selectVariables() const;
		QString identityFieldName() const;
		QString table() const;
		void saveRelationsOf(BlogPost* model);
		QString databaseId() const;
	protected:
		static QList<Tag*> findTagsFor(unsigned blogPostId);
};
