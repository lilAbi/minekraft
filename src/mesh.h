#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>

class Mesh {
public:
    void reset();
private:
    std::vector<glm::vec3> vecs;
};



#endif //MESH_H
