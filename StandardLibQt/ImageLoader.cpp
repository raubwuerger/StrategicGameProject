#include "stdafx.h"
#include "ImageLoader.h"
#include "LogInterface.h"

const QImage * ImageLoader::LoadImage(const QString& imageName)
{
	if (true == imageName.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter must not be null!"));
		return nullptr;
	}

	QImage* newImage = new QImage;
	try
	{
		if (newImage->load(imageName) == false)
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to load image from file: %1").arg(imageName));
			delete newImage;
			return nullptr;
		}
		return newImage;
	}
	catch (...)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Exception during loading of image file: %1").arg(imageName));
		delete newImage;
		return nullptr;
	}
	return newImage;
}
