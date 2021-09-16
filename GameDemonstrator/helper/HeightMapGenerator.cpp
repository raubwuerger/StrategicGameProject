#include "stdafx.h"
#include "HeightMapGenerator.h"
#include "mapCreator\GameMapCreatorHeightMapData.h"
#include "..\libnoise\noise\noise.h"
#include "..\libnoise\noiseutils.h"

bool CreateHeightMapVector(utils::NoiseMap& heightMap, std::vector< std::vector<float> > &heightMapVector)
{
	int width = heightMap.GetWidth();
	int height = heightMap.GetHeight();
	for (int currentWidth = 0; currentWidth < width; currentWidth++)
	{
		std::vector<float> row;
		for (int currentHeight = 0; currentHeight < height; currentHeight++)
		{
			row.push_back(heightMap.GetValue(currentHeight, currentWidth));
		}
		heightMapVector.push_back(row);
	}
	return heightMapVector.size() != 0;
}

bool HeightMapGenerator::GenerateHeightMap(const GameMapCreatorHeightMapData& mapCreationData, std::vector< std::vector<float> >& heightMapVector)
{
	module::Perlin myModule;
	
	bool useOctaveCount = mapCreationData.OctaveCount <= 0 ? false : true;
	if (true == useOctaveCount)
	{ 
		int octaveCount = mapCreationData.OctaveCount;
		if (octaveCount < 1)
		{
			octaveCount = 1;
		}
		if (octaveCount >= noise::module::PERLIN_MAX_OCTAVE)
		{
			octaveCount = noise::module::PERLIN_MAX_OCTAVE;
		}

		myModule.SetOctaveCount(octaveCount);
	}

	bool useFrequency = mapCreationData.Frequency <= 0 ? false : true;
	if (true == useFrequency)
	{ 
		myModule.SetFrequency(mapCreationData.Frequency);
	}

	bool usePersistence = mapCreationData.Persistence <= 0 ? false : true;
	if (true == usePersistence)
	{
		double persistence = mapCreationData.Persistence;
		if (persistence > 1)
		{
			persistence = 1.0;
		}
		myModule.SetPersistence(persistence);

	}

	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(mapCreationData.MapSizeX, mapCreationData.MapSizeY);
	heightMapBuilder.SetBounds(mapCreationData.LowerXBound, mapCreationData.UpperXBound, mapCreationData.LowerZBound, mapCreationData.UpperZBound);
	heightMapBuilder.Build();

	if (true)
	{
		utils::RendererImage renderer;
		utils::Image image;
		renderer.SetSourceNoiseMap(heightMap);
		renderer.SetDestImage(image);
		renderer.ClearGradient();
		renderer.AddGradientPoint(-0.2500, utils::Color(0, 0, 128, 255)); // ocean
		renderer.AddGradientPoint(0.0000, utils::Color(0, 128, 255, 255)); // plain
		renderer.AddGradientPoint(0.0625, utils::Color(240, 240, 64, 255)); // wood
		renderer.AddGradientPoint(0.1250, utils::Color(32, 160, 0, 255)); // hill
		renderer.AddGradientPoint(0.7500, utils::Color(128, 128, 128, 255)); // rock
		renderer.EnableLight();
		renderer.SetLightContrast(3.0); // Triple the contrast
		renderer.SetLightBrightness(2.0); // Double the brightness
		renderer.Render();

		utils::WriterBMP writer;
		writer.SetSourceImage(image);
		writer.SetDestFilename("HeightMap.bmp");
		writer.WriteDestFile();
	}

	return CreateHeightMapVector(heightMap, heightMapVector);
}
