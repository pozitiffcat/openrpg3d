#ifndef CAMERA_H
#define CAMERA_H

#include "movable.h"

namespace engine {

class renderer;

class camera : public movable
{
    friend class renderer;
private:
    void clear_screen();
};

}

#endif // CAMERA_H
