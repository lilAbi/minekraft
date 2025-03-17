#ifndef UTILITY_H
#define UTILITY_H

#include "glm/glm.hpp"
#include "absl/hash/hash.h"

constexpr int WORLD_SIZE_X = 18;
constexpr int WORLD_SIZE_Z = 18;
constexpr int VIEW_DISTANCE = 9;

constexpr int CHUNK_LENGTH = 8;
constexpr int CHUNK_WIDTH = 8;
constexpr int CHUNK_HEIGHT = 8 * 3;

struct Vec2Hasher {
    size_t operator()(const glm::vec2& v) const {
        return absl::Hash<float>()(v.x) ^ absl::Hash<float>()(v.y);
    }
};

#endif //UTILITY_H
