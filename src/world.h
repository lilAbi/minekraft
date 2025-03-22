#ifndef WORLD_H
#define WORLD_H

#include "glm/glm.hpp"
#include "absl/container/flat_hash_map.h"
#include <spdlog/spdlog.h>

#include "chunk.h"
#include "chunkBuilder.h"
#include "utility.h"

class World {
public:
  bool init();

  void tick(glm::vec3 playerPos);

  std::vector<glm::vec2> getViewableChunks();

private:
  glm::vec3 calculateChunkCoord(glm::vec3 playerPos);

private:
  //keep track of players last chunk coord they are in
  glm::vec3 playerLastChunkCoord{-1,-1, -1};
  //container for world chunks
  absl::flat_hash_map<glm::vec2, Chunk, Vec2Hasher> chunkContainer;
  //not so factory class to
  ChunkBuilder chunkBuilder;
};

#endif //WORLD_H