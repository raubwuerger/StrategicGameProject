#pragma once

#include "ProvinceItem.h"
class TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const = 0;
};

class TimeLineDataCriteriaEnergy : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::energy.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaMetal : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::metal.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaCrudeOil : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::crude_oil.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaRareMaterial : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::rare_materials.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaIndustry : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::industry.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaAirbase : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::air_base.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaAntiair : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::anti_air.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaCoastalfort : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::coastal_fort.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaInfrastructure : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::infra.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaLandfort : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::land_fort.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaNavalbase : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::naval_base.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaNuclear : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::nuclear_reactor.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaRadar : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::radar_station.GetName() ).value().GetData().toDouble() <= 0;
	}
};

class TimeLineDataCriteriaRocket : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const QMap<QString,ItemData>& timeLineData ) const
	{
		return timeLineData.find( ProvinceItemPrototypeRepository::rocket_test.GetName() ).value().GetData().toDouble() <= 0;
	}
};
