#pragma once

#include <QImage>
class QString;

class DDSLoader
{
public:
	DDSLoader();
	~DDSLoader();
	QPixmap LoadDDSFile( const QString& file ) const;

	QImage readDDSFile(const QString &filename) const;
};

