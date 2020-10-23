#include "camera.h"

#include "GL/glew.h"

namespace engine {

void camera::clear_screen()
{
    glClearColor(0.2, 0.3, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}
