#ifndef EXTENDEDGRAPHICSSCENE_H
#define EXTENDEDGRAPHICSSCENE_H

class ProvinceItem;
class CommandFactoryProvincePainter;

class ExtendedGraphicsScene : public QGraphicsScene
{
 	Q_OBJECT
public:
 	ExtendedGraphicsScene(QObject *parent = 0);
	void Init();
	/** Set m_PainterFactory */
	void SetPainterFactory( CommandFactoryProvincePainter * val);
public slots:
	void OpenProvinceDetailDialog();
	void SlotProvinceEntered( ProvinceItem* );
signals:
	void SignalProvinceEntered( ProvinceItem* );
	void SignalProvinceLeft( ProvinceItem* );
	void UpdateProvinceOwner( ProvinceItem* );
	void SignalProvinceMouseReleased( ProvinceItem* );
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	bool event(QEvent *event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent * contextMenuEvent);
private:
	QAction	*m_ActionEditProvinceDetails;
	ProvinceItem	*m_LastSelectedItem;
	CommandFactoryProvincePainter	*m_PainterFactory;
};

#include <QGraphicsSceneHoverEvent>
#include <QEvent>

class VisitorEventTranslator
{
public:
	QPointF Position( QGraphicsSceneHoverEvent *event )
	{
		return event->pos();
	}
	QPointF Position( QEvent *event )
	{
		return QPointF(0.0,0.0);
	}
};

#endif // EXTENDEDGRAPHICSSCENE_H
