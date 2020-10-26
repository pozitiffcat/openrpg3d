#ifndef TEXTURE_DATA_H
#define TEXTURE_DATA_H

#include <vector>
#include "rgba_data.h"

namespace engine {

struct texture_data {
    unsigned short width, height;
    std::vector<rgba_data> rgba;
};

}

#endif // TEXTURE_DATA_H
