

#ifndef CHUNKBUILDER_H
#define CHUNKBUILDER_H

#include "FastNoise/FastNoise.h"
#include "chunk.h"

//Class
class ChunkBuilder {
public:
  void buildChunk(glm::vec3 chunkPos);

private:
  void generateBlockData(glm::vec3 chunkPos);
  void generateMesh(glm::vec3 chunkPos);
private:
  FastNoise::SmartNode<FastNoise::Perlin> perlinNoise{FastNoise::New<FastNoise::Perlin>()};

};



#endif //CHUNKBUILDER_H
