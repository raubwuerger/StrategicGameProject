#include <iostream>
#include <fstream>
#include <vector>
#include ".\noise\noise.h"
#include "noiseutils.h"

using namespace noise;

void tutorial2()
{
	module::Perlin myModule;
	double value = myModule.GetValue(1.25, 0.75, 0.5);
	std::cout << value << std::endl;
	value = myModule.GetValue(1.2501, 0.7501, 0.5001);
	std::cout << value << std::endl;
	value = myModule.GetValue(14.50, 20.25, 75.75);
	std::cout << value << std::endl;
}

void PrintHeightMap(utils::NoiseMap& heightMap)
{
	int width = heightMap.GetWidth();
	int height = heightMap.GetHeight();
	std::vector< std::vector<float> > heightMapVector;
	for (int currentWidth = 0; currentWidth < width; currentWidth++)
	{
		std::vector<float> row;
		for (int currentHeight = 0; currentHeight < height; currentHeight++)
		{
			row.push_back(heightMap.GetValue(currentWidth,currentHeight));
		}
		heightMapVector.push_back(row);
	}

	std::ofstream heightMapFile("heigtMap.txt");
	for (std::vector< std::vector<float> >::size_type vectorIndex = 0; vectorIndex < heightMapVector.size(); vectorIndex++)
	{
		std::vector<float> row = heightMapVector[vectorIndex];
		std::ostream_iterator<float> output_iterator(heightMapFile, "; ");
		std::copy(row.begin(), row.end(), output_iterator);
		heightMapFile << "\n";
	}
}

void tutorial3()

{
	module::Perlin myModule;
	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(256, 256);
	heightMapBuilder.SetBounds(6.0, 10.0, 1.0, 5.0);
	heightMapBuilder.Build();

	PrintHeightMap(heightMap);

	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap(heightMap);
	renderer.SetDestImage(image);
	renderer.ClearGradient();
	renderer.AddGradientPoint(-1.0000, utils::Color(0, 0, 128, 255)); // deeps
	renderer.AddGradientPoint(-0.2500, utils::Color(0, 0, 255, 255)); // shallow
	renderer.AddGradientPoint(0.0000, utils::Color(0, 128, 255, 255)); // shore
	renderer.AddGradientPoint(0.0625, utils::Color(240, 240, 64, 255)); // sand
	renderer.AddGradientPoint(0.1250, utils::Color(32, 160, 0, 255)); // grass
	renderer.AddGradientPoint(0.3750, utils::Color(224, 224, 0, 255)); // dirt
	renderer.AddGradientPoint(0.7500, utils::Color(128, 128, 128, 255)); // rock
	renderer.AddGradientPoint(1.0000, utils::Color(255, 255, 255, 255)); // snow
	renderer.EnableLight();
	renderer.SetLightContrast(3.0); // Triple the contrast
	renderer.SetLightBrightness(2.0); // Double the brightness
	renderer.Render();

	utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename("tutorial3.bmp");
	writer.WriteDestFile();
}

void tutorial4()
{
	module::Perlin myModule;
	myModule.SetOctaveCount(6);
	myModule.SetFrequency(2.0);
	myModule.SetPersistence(0.5);
	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(256, 256);
	heightMapBuilder.SetBounds(6.0, 10.0, 1.0, 5.0);
	heightMapBuilder.Build();

	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap(heightMap);
	renderer.SetDestImage(image);
	renderer.ClearGradient();
	renderer.AddGradientPoint(-1.0000, utils::Color(0, 0, 128, 255)); // deeps
	renderer.AddGradientPoint(-0.2500, utils::Color(0, 0, 255, 255)); // shallow
	renderer.AddGradientPoint(0.0000, utils::Color(0, 128, 255, 255)); // shore
	renderer.AddGradientPoint(0.0625, utils::Color(240, 240, 64, 255)); // sand
	renderer.AddGradientPoint(0.1250, utils::Color(32, 160, 0, 255)); // grass
	renderer.AddGradientPoint(0.3750, utils::Color(224, 224, 0, 255)); // dirt
	renderer.AddGradientPoint(0.7500, utils::Color(128, 128, 128, 255)); // rock
	renderer.AddGradientPoint(1.0000, utils::Color(255, 255, 255, 255)); // snow
	renderer.EnableLight();
	renderer.SetLightContrast(3.0); // Triple the contrast
	renderer.SetLightBrightness(2.0); // Double the brightness
	renderer.Render();

	utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename("tutorial4.bmp");
	writer.WriteDestFile();
}

void tutorial5()
{
	module::RidgedMulti mountainTerrain;

	module::Billow baseFlatTerrain;
	baseFlatTerrain.SetFrequency(2.0);

	module::ScaleBias flatTerrain;
	flatTerrain.SetSourceModule(0, baseFlatTerrain);
	flatTerrain.SetScale(0.125);
	flatTerrain.SetBias(-0.75);

	module::Perlin terrainType;
	terrainType.SetFrequency(0.5);
	terrainType.SetPersistence(0.25);

	module::Select finalTerrain;
	finalTerrain.SetSourceModule(0, flatTerrain);
	finalTerrain.SetSourceModule(1, mountainTerrain);
	finalTerrain.SetControlModule(terrainType);
	finalTerrain.SetBounds(0.0, 1000.0);
	finalTerrain.SetEdgeFalloff(0.125);

	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(finalTerrain);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(256, 256);
	heightMapBuilder.SetBounds(6.0, 10.0, 1.0, 5.0);
	heightMapBuilder.Build();

	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap(heightMap);
	renderer.SetDestImage(image);
	renderer.ClearGradient();
	renderer.AddGradientPoint(-1.00, utils::Color(32, 160, 0, 255)); // grass
	renderer.AddGradientPoint(-0.25, utils::Color(224, 224, 0, 255)); // dirt
	renderer.AddGradientPoint(0.25, utils::Color(128, 128, 128, 255)); // rock
	renderer.AddGradientPoint(1.00, utils::Color(255, 255, 255, 255)); // snow
	renderer.EnableLight();
	renderer.SetLightContrast(3.0);
	renderer.SetLightBrightness(2.0);
	renderer.Render();

	utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename("tutorial5.bmp");
	writer.WriteDestFile();
}

int main(int argc, char** argv)
{
	tutorial2();
	tutorial3();
	tutorial4();
	tutorial5();
	return 0;
}

