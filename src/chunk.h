#ifndef CHUNK_H
#define CHUNK_H

#include "glm/glm.hpp"
#include "resourceManager.h"
#include <vector>

constexpr int CHUNK_LENGTH = 8;
constexpr int CHUNK_WIDTH = 8;
constexpr int CHUNK_HEIGHT = 8 * 3;


enum class  ChunkStatus {
    UNLOADED = 0,
    LOADED,

};

class Chunk {
public:

public:
    ChunkStatus chunkStatus{ChunkStatus::UNLOADED};
private:
    glm::vec3 chunkPos{};
};



#endif //CHUNK_H
