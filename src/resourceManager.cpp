#include "resourceManager.h"


bool ResourceManager::init() {

    //reserve enough space
    meshContainer.reserve(9 * 9);
    blockContainer.reserve(9 * 9);


    return true;
}

bool ResourceManager::createBlockResource(glm::vec2) {
    //TerrainGenerator generator;
    //
}

