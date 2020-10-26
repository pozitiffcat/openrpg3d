#ifndef VERTEX_H
#define VERTEX_H

namespace engine {

struct vertex {
    float x, y, z;          // posiitons
    float nx, ny, nz;       // normals
    float tx, ty, tz;       // tangent
    float bx, by, bz;       // bitangent
    float tu, tv;           // UV texcoords
};

}

#endif // VERTEX_H
