#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include <GL/glew.h>

namespace engine {

struct render_context {
    GLint position_attrib;
    GLint normal_attrib;
    GLint tangent_attrib;
    GLint bitangent_attrib;
    GLint texcoord_attrib;
    GLint proj_matrix_uniform;
    GLint view_matrix_uniform;
    GLint proj_view_matrix_uniform;
    GLint model_matrix_uniform;
    GLint normal_matrix_uniform;
    GLint diffuse_texture_uniform;
    GLint normal_texture_uniform;
};

}

#endif // RENDER_CONTEXT_H
