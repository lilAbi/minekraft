#ifndef WORLD_H
#define WORLD_H

#include "glm/glm.hpp"
#include "absl/container/flat_hash_map.h"
#include "chunk.h"
#include "chunkBuilder.h"
#include "utility.h"


constexpr int WORLD_SIZE_X = 18;
constexpr int WORLD_SIZE_Z = 18;
constexpr int VIEW_DISTANCE = 9;


//#include

class World {
public:
  World() = default;

  void tick(glm::vec3 playerPos);

  bool init();

private:
  glm::vec2 calculateLastChunkCoord(glm::vec3 playerPos);

  bool mapChunkPosToContainerIndex(glm::vec2 genChunk, glm::vec2& currChunk);

private:
  //keep track of players last chunk coord they are in
  glm::vec2 playerLastChunkCoord{0,0};
  //container for world chunks
  absl::flat_hash_map<glm::vec2, Chunk, Vec2Hasher> chunkContainer;
  //not so factory class to
  ChunkBuilder chunkBuilder;
};

#endif //WORLD_H