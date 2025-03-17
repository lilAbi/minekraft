#include "chunkBuilder.h"

#include <spdlog/spdlog.h>

void ChunkBuilder::buildChunk(glm::vec3 chunkPos) {
    //generate block data
    generateBlockData(chunkPos);
    //generate mesh
    generateMeshNaive(chunkPos);
}

void ChunkBuilder::generateBlockData(glm::vec3 chunkPos) {
    //grab the block data array from the resource manager
    BlockVec* blockVec = ResourceManager::getInstance().getBlockArr(glm::vec2(chunkPos.x, chunkPos.z));
    //create a container to hold the noise value
    std::array<float, CHUNK_WIDTH * CHUNK_LENGTH> noiseValues{};
    //generate noise values into container
    perlinNoise->GenUniformGrid2D(noiseValues.data(),
        static_cast<int>(chunkPos.x),
        static_cast<int>(chunkPos.z),
        CHUNK_LENGTH, CHUNK_WIDTH, 0.01, 1337);
    //create height map using noise values and generate block data in the array
    for (int y{0}; y<CHUNK_HEIGHT; y++ ) {
        for (int z{0}; z<CHUNK_WIDTH; z++) {
            for (int x{0}; x<CHUNK_LENGTH; x++) {
                //get the max height for the particular (x,z) noise value
                int maxHeight = std::abs(static_cast<int>(noiseValues[x + (z * CHUNK_WIDTH)]));
                (*blockVec)[x + (z * CHUNK_WIDTH) + (y * CHUNK_WIDTH * CHUNK_LENGTH)] = (y < maxHeight ? 1 : 0);
            }
        }
    }

}

void ChunkBuilder::generateMeshGreedy(glm::vec3 chunkPos) {
    //iterate through all the dimensions
    BlockVec* blockVec = ResourceManager::getInstance().getBlockArr(glm::vec2(chunkPos.x, chunkPos.z));

    for (int dimension{0}; dimension < 6; dimension++) {

        //a copy of a slice of the chunk currently iterating over
        std::vector<int> mask;
        int maxAxis = 0, maxWidth = 0, maxLength = 0;
        //correlates to positions inside the axis array
        int slice = 0, side = 0, bottom = 0;
        //axis[x,y,z]
        int axis[3]{0};

        //generate a mask for the particular dimension
        if (dimension == 0) {
            //iterate though the y axis facing +y
            mask.resize(CHUNK_WIDTH * CHUNK_LENGTH);
            maxLength = CHUNK_LENGTH; maxAxis = CHUNK_HEIGHT; maxWidth = CHUNK_WIDTH;
            bottom = 0; slice = 1; side = 2;
        } else if (dimension == 1) {
            //iterate though the y axis facing -y
            mask.resize(CHUNK_WIDTH * CHUNK_LENGTH);
            maxLength = CHUNK_LENGTH; maxAxis = CHUNK_HEIGHT; maxWidth = CHUNK_WIDTH;
            bottom = 0; slice = 1; side = 2;
        } else if (dimension == 2) {
            //iterate though the z axis facing +z
            mask.resize(CHUNK_WIDTH * CHUNK_HEIGHT);
            maxLength = CHUNK_LENGTH; maxAxis = CHUNK_WIDTH; maxWidth = CHUNK_HEIGHT;
            bottom = 0; slice = 2; side = 1;
        } else if (dimension == 3) {
            //iterate though the z axis facing -z
            mask.resize(CHUNK_WIDTH * CHUNK_HEIGHT);
            maxLength = CHUNK_LENGTH; maxAxis = CHUNK_WIDTH; maxWidth = CHUNK_HEIGHT;
            bottom = 0; slice = 2; side = 1;
        } else if (dimension == 4) {
            //iterate though the x axis facing +x
            mask.resize(CHUNK_LENGTH * CHUNK_HEIGHT);
            maxLength = CHUNK_WIDTH; maxAxis = CHUNK_LENGTH; maxWidth = CHUNK_HEIGHT;
            bottom = 2; slice = 0; side = 1;
        } else if (dimension == 5) {
            //iterate though the x axis facing -x
            mask.resize(CHUNK_LENGTH * CHUNK_HEIGHT);
            maxLength = CHUNK_WIDTH; maxAxis = CHUNK_LENGTH; maxWidth = CHUNK_HEIGHT;
            bottom = 2; slice = 0; side = 1;
        }

        //per the dimension
        for (axis[slice] = 0; axis[slice] < maxAxis; axis[slice]++) {   //iterate over slice

            //for this slice, compute the mask
            //make a copy of the slice
            int m[3]{0};
            for (m[side] = 0; m[side] < maxWidth; m[side]++) {
                for (m[bottom] = 0; m[bottom] < maxLength; m[bottom]++) {
                    mask[m[bottom] + (m[side] * maxWidth)] = (*blockVec)[(axis[0] + m[0]) + ((axis[2] + m[2]) * maxWidth) + ((axis[1] + m[1]) * maxLength * maxWidth)];
                }
            }

            for (axis[side] = 0; axis[side] < maxWidth; axis[side]++) { //iterate over bottom to top
                for (axis[bottom] = 0; axis[bottom] < maxLength; axis[bottom]++) { //iterate left to right

                    //if the block is empty continue to the next
                    if (mask[axis[bottom] + (axis[side] * maxWidth)] == 0)
                        continue;



                }
            }

            mask.clear();
        }



    }


}

void ChunkBuilder::generateMeshNaive(glm::vec3 chunkPos) {
    //grab the block data vector from resource manager
    const BlockVec* blockVec = ResourceManager::getInstance().getBlockArr(glm::vec2(chunkPos.x, chunkPos.z));
    //generate world chunk position coordinates
    float chunkPosX = chunkPos.x * CHUNK_WIDTH;
    float chunkPosY = chunkPos.y * CHUNK_HEIGHT;
    float chunkPosZ = chunkPos.z * CHUNK_LENGTH;
    //container for the vertex data about to make
    std::vector<glm::vec3> vertexData;

    //iterate through the block data array
    for (int y{0}; y < CHUNK_HEIGHT; ++y) {
        for (int z{0}; z < CHUNK_WIDTH; ++z) {
            for (int x{0}; x < CHUNK_LENGTH; ++x) {
                //check if the block is empty- if so skip
                if(const int currBlockID = (*blockVec)[x + (z * CHUNK_WIDTH) + ( y * CHUNK_LENGTH * CHUNK_WIDTH)]; currBlockID == 0){
                    continue;
                }
                // looking at z face from the front ----
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));

                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));

                // looking at z face from the back ----
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);

                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);

                // looking at x face from the right ----
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);

                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));

                //looking at the x face from the left
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));

                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);


                //looking at the y face from the top
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);

                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));

                //looking at the y face from the bottom
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));

                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);

            }
        }
    }

    ResourceManager::getInstance().addMeshElement({chunkPos.x, chunkPos.z}, {std::move(vertexData)});

}
