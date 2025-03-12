

#include "world.h"

bool World::init() {

    chunkContainer.reserve(CHUNK_SIZE_X*CHUNK_SIZE_Z);

    return true;
}

void World::tick(glm::vec3 playerPos) {
    //--CHUNK GENERATION--
    //calculate the chunk coord of the player they are currently in
    if (const auto currChunkCoord{calculateLastChunkCoord(playerPos)}; currChunkCoord != playerLastChunkCoord) {
        //iterate over square region defined by view distance
        for (int x{-VIEW_DISTANCE}; x <= VIEW_DISTANCE; x++) {
            for (int z{-VIEW_DISTANCE}; z <= VIEW_DISTANCE; z++) {
                //calculate the chunk we are going to generate
                auto genChunk{currChunkCoord.x + x, currChunkCoord.y + z};
                if (std::sqrt(x*x + z*z) < VIEW_DISTANCE) {
                    //grab a reference to the chunk object from the container

                    //calculate the index
                    glm::vec2 index = genChunk - currChunkCoord;
                    chunkContainer[index];


                }
            }
        }

    } else {

    }

}

glm::vec2 World::calculateLastChunkCoord(glm::vec3 playerPos) {
    return glm::vec2{std::floor(playerPos.x/CHUNK_SIZE_X), std::floor(playerPos.z/CHUNK_SIZE_Z) };
}

bool World::mapChunkPosToContainerIndex(glm::vec2 genChunk, glm::vec2 &currChunk) {



}
