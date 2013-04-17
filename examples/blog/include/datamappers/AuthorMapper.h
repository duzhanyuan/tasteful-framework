#pragma once

#include <models/Author.h>

#include <DataMapper>

class AuthorMapper : public DataMapper<AuthorMapper, Author, unsigned> {
	public:
		AuthorMapper();
		~AuthorMapper();
		
		void buildFromRecord(Author* model, const QVariantMap& record) const;
		void buildRecordFrom(Author* model, QVariantMap& record) const;
		QList<QString> selectVariables() const;
		QString identityFieldName() const;
		QString table() const;
		QString databaseId() const;
};
