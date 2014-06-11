#pragma once

#include "ProvinceItem.h"
class TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const = 0;
};

class TimeLineDataCriteriaEnergy : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Energy <= 0;
	}
};

class TimeLineDataCriteriaMetal : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Metal <= 0;
	}
};

class TimeLineDataCriteriaCrudeOil : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_CrudeOil <= 0;
	}
};

class TimeLineDataCriteriaRareMaterial : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_RareMaterials <= 0;
	}
};

class TimeLineDataCriteriaIndustry : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Industry <= 0;
	}
};

class TimeLineDataCriteriaAirbase : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_AirBases <= 0;
	}
};

class TimeLineDataCriteriaAntiair : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_AntiAir <= 0;
	}
};

class TimeLineDataCriteriaCoastalfort : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Coastalfort <= 0;
	}
};

class TimeLineDataCriteriaInfrastructure : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Infrastructure <= 0;
	}
};

class TimeLineDataCriteriaLandfort : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Landfort <= 0;
	}
};

class TimeLineDataCriteriaNavalbase : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_NavalBase <= 0;
	}
};

class TimeLineDataCriteriaNuclear : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Nuclear <= 0;
	}
};

class TimeLineDataCriteriaRadar : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Radar <= 0;
	}
};

class TimeLineDataCriteriaRocket : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Rocket <= 0;
	}
};
