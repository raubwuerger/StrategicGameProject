#ifndef CEDITORTOOLBOX_H
#define CEDITORTOOLBOX_H

#include <QToolBox>
class CTerrainTypeRepository;

class CEditorToolbox : public QToolBox
{
	Q_OBJECT
public:
	/** */
	CEditorToolbox(QWidget *parent);
	/** */
	~CEditorToolbox();
	/** */
	void Create( CTerrainTypeRepository *repository );
private:
	/** */
	QWidget *CreateTerrainTypeWidget(const QString &text, QButtonGroup* buttonGroup, const QString& pictureName=":GameDemonstrator/Resources/gear_run.ico" );
private slots:
		void ButtonGroupTerrainTypes(QAbstractButton *button);
private:
	QButtonGroup		*m_GroupTerrainTypes;
	QButtonGroup		*m_GroupBuildings;
};

#endif // CEDITORTOOLBOX_H
