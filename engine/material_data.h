#ifndef MATERIAL_DATA_H
#define MATERIAL_DATA_H

#include <memory>

namespace engine {

class texture;

struct material_data
{
    std::shared_ptr<texture> diffuse_texture;
};

}

#endif // MATERIAL_DATA_H
