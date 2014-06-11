#include "stdafx.h"
#include "DDSLoader.h"

#include <QGLWidget>
#include <QGLPixelBuffer>

DDSLoader::DDSLoader()
{
}


DDSLoader::~DDSLoader()
{
}

QPixmap DDSLoader::LoadDDSFile( const QString& filename ) const
{
	QGLWidget glWidget;
	glWidget.makeCurrent();
	
	QString file("E:/temp/icon_rarematerial_big.dds");
	GLuint texture = glWidget.bindTexture(file);
	if( texture == false )
	{
		return QPixmap();
	}

	// Determine the size of the DDS image
	GLint width, height;
	glBindTexture(GL_TEXTURE_2D, texture);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

	if (width == 0 || height == 0)
	{
		return QPixmap();
	}

	QGLPixelBuffer pbuffer(QSize(width, height), glWidget.format(), &glWidget);
	if( pbuffer.makeCurrent() == false )
	{
		return QPixmap();
	}

	pbuffer.drawTexture(QRectF(-1, -1, 2, 2), texture);

	QPixmap pixmap;
	pixmap.convertFromImage( pbuffer.toImage() );
	return pixmap;
}
