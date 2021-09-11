#ifndef COLORCREATORPERCENTAGE_H
#define COLORCREATORPERCENTAGE_H

class ColorCreatorPercentage
{
public:
	/** */
	ColorCreatorPercentage();
	/** */
	static QColor Create(double value);
private:
	double		BorderGreen;
	double		BorderRed;
	QColor		LightRed;
	QColor		LightYellow;
	QColor		LightGreen;

};

#endif // COLORCREATORPERCENTAGE_H