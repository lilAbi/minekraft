#ifndef CHUNK_H
#define CHUNK_H

#include "glm/glm.hpp"

enum class  ChunkStatus {
    UNLOADED = 0,
    LOADED,

};

class Chunk {
public:

public:
    ChunkStatus chunkStatus{ChunkStatus::UNLOADED};
    glm::vec3 chunkPos{};
};



#endif //CHUNK_H
