#ifndef CEDITORTOOLBOX_H
#define CEDITORTOOLBOX_H

//================================================================================
#include <QToolBox>
class CTerrainTypeRepository;
class CConnectorButtonTerrainTypeId;
class CTerrainTypeEditor;

class CEditorToolbox : public QToolBox
{
	Q_OBJECT
public:
	/** */
	CEditorToolbox(QWidget *parent);
	/** */
	~CEditorToolbox();
	/** Erzeugt die Toolboxeinträge */
	void Create();
private:
	/** */
	QWidget *CreateTerrainTypeWidget(const QString &text, QButtonGroup* buttonGroup, CConnectorButtonTerrainTypeId *connector, const QString& pictureName=":GameDemonstrator/Resources/gear_run.ico" );
private slots:
	/** */
	void ButtonGroupTerrainTypes(QAbstractButton *button);
private:
	friend class GameDemonstrator;
	QButtonGroup		*GroupTerrainTypes;
	QButtonGroup		*GroupBuildings;
	CTerrainTypeEditor	*TerrainTypeEditor;
};

//================================================================================
class CConnectorButtonTerrainTypeId : public QObject
{
	Q_OBJECT
public:
	/** */
	CConnectorButtonTerrainTypeId( int terrainTypeId );
public slots:
	/** */
	void Trigger();
signals:
	/** */
	void TerrainTypeActive( int terrainTypeId );
private:
	int TerrainTypeId;
};

#endif // CEDITORTOOLBOX_H
