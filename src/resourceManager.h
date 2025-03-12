#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "utility.h"
#include "mesh.h"
#include "glm/glm.hpp"
#include "absl/container/flat_hash_map.h"
#include "absl/hash/hash.h"

class ResourceManager {
public:
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;
  static ResourceManager& getInstance() { static ResourceManager instance; return instance; }

  bool init();

  bool createBlockResource(glm::vec2);

  bool getBlockResource(glm::vec2);

private:
  ResourceManager() = default;
  ~ResourceManager() = default;

  absl::flat_hash_map<glm::vec2, Mesh, Vec2Hasher> meshContainer{};
  absl::flat_hash_map<glm::vec2, std::array<int, 8*8*8>, Vec2Hasher> blockContainer{};

};



#endif //RESOURCEMANAGER_H
