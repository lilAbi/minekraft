#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "glm/glm.hpp"
#include "absl/container/flat_hash_map.h"
#include "absl/hash/hash.h"
#include "utility.h"
#include "mesh.h"

typedef std::array<int, CHUNK_HEIGHT*CHUNK_WIDTH*CHUNK_LENGTH> BlockVec;

class Renderer;

class ResourceManager {
public:
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;
  static ResourceManager& getInstance() { static ResourceManager instance; return instance; }

  //initialize subsystems and reserve space
  bool init();

  //adds a mesh element, ideally already contains the data
  bool addMeshElement(glm::vec2 chunkPos, Mesh mesh);

  //returns the mesh element at key vec
  Mesh* getMeshElement(glm::vec2 chunkPos);

  //returns the array object containing these
  BlockVec* getBlockArr(glm::vec2 chunkPos);

private:
  friend Renderer;
  ResourceManager() { meshContainer.reserve(WORLD_SIZE_X * WORLD_SIZE_Z); blockContainer.reserve(WORLD_SIZE_X * WORLD_SIZE_Z); }
  ~ResourceManager() = default;

  //should be storing indices to the chunk position, which is basically value/chunk_size
  absl::flat_hash_map<glm::vec2, Mesh, Vec2Hasher> meshContainer{};
  absl::flat_hash_map<glm::vec2, BlockVec, Vec2Hasher> blockContainer{};
};



#endif //RESOURCEMANAGER_H
