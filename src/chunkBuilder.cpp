#include "chunkBuilder.h"

void ChunkBuilder::buildChunk(glm::vec3 chunkPos) {
    //grab the block data array
    generateBlockData(chunkPos);
    generateMesh(chunkPos);
}

void ChunkBuilder::generateBlockData(glm::vec3 chunkPos) {

    BlockVec& blockVec = ResourceManager::getInstance().getBlockArr(glm::vec2(chunkPos.x, chunkPos.z));

    std::array<float, CHUNK_WIDTH * CHUNK_LENGTH> noiseValues{};

    perlinNoise->GenUniformGrid2D(noiseValues.data(),
        static_cast<int>(chunkPos.x),
        static_cast<int>(chunkPos.z),
        CHUNK_LENGTH, CHUNK_WIDTH, 0.01, 1337);

    for (int y{0}; y<CHUNK_HEIGHT; y++ ) {
        for (int z{0}; z<CHUNK_WIDTH; z++) {
            for (int x{0}; x<CHUNK_LENGTH; x++) {
                //get the max height for the particular (x,z) noise value
                int maxHeight = std::abs(static_cast<int>(noiseValues[x + (z * CHUNK_WIDTH)]));
                blockVec[x + (z * CHUNK_WIDTH) + (y * CHUNK_WIDTH * CHUNK_LENGTH)] = y < maxHeight ? 1 : 0;
            }
        }
    }

}

void ChunkBuilder::generateMesh(glm::vec3 chunkPos) {


}
