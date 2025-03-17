#include "resourceManager.h"


bool ResourceManager::init() {

    //reserve enough space
    meshContainer.reserve(9 * 9);
    blockContainer.reserve(9 * 9);


    return true;
}

bool ResourceManager::addMeshElement(glm::vec2 chunkPos, Mesh mesh) {
    meshContainer[chunkPos] = std::move(mesh);
    return true;
}

Mesh* ResourceManager::getMeshElement(glm::vec2 chunkPos) {
    //if (meshContainer.find(chunkPos));
    return &meshContainer[chunkPos];
}

BlockVec* ResourceManager::getBlockArr(glm::vec2 chunkPos) {
    return &blockContainer[chunkPos];
}
