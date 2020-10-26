#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <vector>
#include "vertex.h"

namespace engine {

struct mesh_data {
    std::vector<vertex> vertices;
};

}

#endif // MESH_DATA_H
