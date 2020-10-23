#ifndef MESH_DEF_H
#define MESH_DEF_H

#include <vector>
#include "vertex.h"

namespace engine {

struct mesh_def {
    std::vector<vertex> vertices;
};

}

#endif // MESH_DEF_H
