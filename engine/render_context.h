#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include <GL/glew.h>
#include <memory>

namespace engine {

class texture;

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
    GLint roughness_texture_uniform;
    GLint occlusion_texture_uniform;
    std::shared_ptr<texture> default_diffuse_texture;
    std::shared_ptr<texture> default_normal_texture;
    std::shared_ptr<texture> default_roughness_texture;
    std::shared_ptr<texture> default_occlusion_texture;
};

}

#endif // RENDER_CONTEXT_H
