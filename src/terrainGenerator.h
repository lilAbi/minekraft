#ifndef TERRAINGENERATOR_H
#define TERRAINGENERATOR_H

#include "glm/glm.hpp"
#include "FastNoise/FastNoise.h"


class TerrainGenerator {
public:
  TerrainGenerator(const TerrainGenerator&) = delete;
  TerrainGenerator& operator=(const TerrainGenerator&) = delete;
  static TerrainGenerator& getInstance() { static TerrainGenerator instance; return instance; }

  bool generateBlockData(glm::vec3 chunkLowerLeft);

private:
  TerrainGenerator();
  ~TerrainGenerator() = default;

private:
  FastNoise::SmartNode<FastNoise::Perlin> heightMapNoise{FastNoise::New<FastNoise::Perlin>()};

};



#endif //TERRAINGENERATOR_H
