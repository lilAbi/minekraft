#include "world.h"

bool World::init() {
    chunkContainer.reserve(WORLD_SIZE_X*WORLD_SIZE_Z);
    return true;
}

void World::tick(glm::vec3 playerPos) {
    //--CHUNK GENERATION--
    //calculate the chunk coordinate relative to the players position
    //if the player is not in the chunk coordinate as last frame then generate the surrounding chunks around the player
    if (const auto currChunkCoord{calculateChunkCoord(playerPos)}; currChunkCoord != playerLastChunkCoord) {
        spdlog::info("Current chunk coordinate {} {} {}", currChunkCoord.x, currChunkCoord.y, currChunkCoord.z);

        //iterate over square region defined by view distance
        for (int x{-VIEW_DISTANCE}; x <= VIEW_DISTANCE; x++) {
            for (int z{-VIEW_DISTANCE}; z <= VIEW_DISTANCE; z++) {
                //calculate the chunk's coordinate point to generate
                glm::vec3 genChunk{currChunkCoord.x + static_cast<float>(x), 0, currChunkCoord.z + static_cast<float>(z)};

                //if the chunk falls under the view distance, generate or load it
                if (std::sqrt(x*x + z*z) < VIEW_DISTANCE) {
                    //calculate the index of the chunk in the container
                    const glm::vec3 index = genChunk - currChunkCoord;
                    //grab a ref to the chunk object
                    auto& chunk = chunkContainer[glm::vec2(index.x, index.z)];
                    //if the chunk is 'unloaded' try to load it from cache or generate chunk data
                    if (chunk.chunkStatus == ChunkStatus::UNLOADED) {
                        //generate chunk data from scratch
                        chunkBuilder.buildChunk(genChunk);
                    }
                }

            }
        }

        //update the player's last chunk coordinate they were in to the current chunk coordinate
        playerLastChunkCoord = currChunkCoord;
    }

}

std::vector<glm::vec2> World::getViewableChunks() {
    //container to hold coordinates of the viewable chunks
    std::vector<glm::vec2> viewableChunks;
    viewableChunks.reserve(size_t{WORLD_SIZE_X*WORLD_SIZE_Z});

    //iterate over square region defined by view distance
    for (int x{-VIEW_DISTANCE}; x <= VIEW_DISTANCE; x++) {
        for (int z{-VIEW_DISTANCE}; z <= VIEW_DISTANCE; z++) {
            //calculate the chunk's coordinate point to generate
            glm::vec3 genChunk{playerLastChunkCoord.x + static_cast<float>(x), 0, playerLastChunkCoord.z + static_cast<float>(z)};

            //if the chunk falls under the view distance, generate or load it
            if (std::sqrt(x*x + z*z) < VIEW_DISTANCE) {
                //calculate the index of the chunk in the container
                const glm::vec3 index = genChunk - playerLastChunkCoord;
                //add coordinate to the container
                viewableChunks.emplace_back(index.x, index.z);

            }

        }
    }

    //nrvo should be invoked here
    return viewableChunks;
}

glm::vec3 World::calculateChunkCoord(glm::vec3 playerPos) {
    return glm::vec3{std::floor(playerPos.x/CHUNK_LENGTH), 0,std::floor(playerPos.z/CHUNK_WIDTH) };
}