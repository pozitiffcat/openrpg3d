#ifndef CAMERA_H
#define CAMERA_H

#include "movable.h"

namespace engine {

class camera : public movable
{
public:
    void clear_screen();
};

}

#endif // CAMERA_H
