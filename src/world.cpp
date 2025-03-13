

#include "world.h"

bool World::init() {

    chunkContainer.reserve(WORLD_SIZE_X*WORLD_SIZE_Z);

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
                //if the chunk position falls under the view distance then load it
                if (std::sqrt(x*x + z*z) < VIEW_DISTANCE) {
                    //calculate the index
                    glm::vec2 index = genChunk - currChunkCoord;
                    //grab the chunk
                    auto& chunk = chunkContainer[index];

                    if (chunk.chunkStatus == ChunkStatus::UNLOADED) {
                        //try to fetch check from somewhere and load it, also load the meshID and blockIDs
                        //chunkBuilder.buildChunk(chunk)
                        //calculate blocks
                    } else if (chunk.chunkStatus == ChunkStatus::LOADED) {
                        //unload the current chunk
                        //generate new chunk
                        //replace element with the newly
                    }


                }
            }
        }

    } else {

    }

}

glm::vec2 World::calculateLastChunkCoord(glm::vec3 playerPos) {
    return glm::vec2{std::floor(playerPos.x/WORLD_SIZE_X), std::floor(playerPos.z/WORLD_SIZE_Z) };
}

bool World::mapChunkPosToContainerIndex(glm::vec2 genChunk, glm::vec2 &currChunk) {



}
