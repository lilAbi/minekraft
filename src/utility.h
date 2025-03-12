#ifndef UTILITY_H
#define UTILITY_H

#include "glm/glm.hpp"
#include "absl/hash/hash.h"

struct Vec2Hasher {
    size_t operator()(const glm::vec2& v) const {
        return absl::Hash<float>()(v.x) ^ absl::Hash<float>()(v.y);
    }
};

#endif //UTILITY_H
