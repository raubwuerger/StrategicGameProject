#ifndef CREATENEWMAP_H
#define CREATENEWMAP_H

#include <QObject>

class CreateNewMap : public QObject
{
	Q_OBJECT
public:
	/** */
	CreateNewMap(QObject *parent);
	/** */
	~CreateNewMap();
public slots:
	void DoCreateNewMap();
};

#endif // CREATENEWMAP_H
