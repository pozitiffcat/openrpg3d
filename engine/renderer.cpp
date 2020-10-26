#include "renderer.h"

#include "camera.h"
#include "mesh.h"
#include "drawable.h"
#include "texture.h"

#include <string.h>

namespace {

const char *debug_vertex_shader =
        "#version 330 core\n"
        "in vec3 position;\n"
        "uniform mat4 proj_view_matrix;\n"
        "uniform mat4 model_matrix;\n"
        "void main(void)\n"
        "{\n"
        "	gl_Position = proj_view_matrix * model_matrix * vec4(position, 1.0);\n"
        "}\n";

const char *debug_fragment_shader =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "	color = vec4(1.0);\n"
        "}\n";

const char *vertex_shader =
        "#version 330 core\n"
        "in vec3 position;\n"
        "in vec3 normal;\n"
        "in vec2 texcoord;\n"
        "uniform mat4 proj_matrix;\n"
        "uniform mat4 view_matrix;\n"
        "uniform mat4 model_matrix;\n"     
        "out vec3 p;\n"
        "out vec3 n;\n"
        "out vec2 t;\n"
        "void main(void)\n"
        "{\n"
        "   p = (model_matrix * vec4(position, 1.0)).xyz;\n"
        "   n = normal;\n"
        "   t = texcoord;\n"
        "	gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position, 1.0);\n"
        "}\n";

const char *fragment_shader =
        "#version 330 core\n"
        "in vec3 p;\n"
        "in vec3 n;\n"
        "in vec2 t;\n"
        "out vec4 color;\n"
        "uniform mat3 normal_matrix;\n"
        "uniform sampler2D diffuse_texture;\n"
        "void main(void)\n"
        "{\n"
        "   vec3 light_pos = vec3(0.0, 7.0, -10.0);\n"
        "   vec3 light_dir = normalize(light_pos - p);\n"
        "   float shade = dot(normal_matrix * n, light_dir);\n"
        "	color = max(shade, 0.2) * texture(diffuse_texture, t);\n"
        "}\n";

GLuint create_compiled_shader(const char *source, GLenum type)
{
    GLuint shader = glCreateShader(type);
    GLint len = strlen(source);
    GLint compileStatus;

    glShaderSource(shader, 1, &source,  &len);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == 0) {
        return 0;
    }

    return shader;
}

GLuint create_compiled_program(const char *vertex_source, const char *fragment_source)
{
    GLuint program = glCreateProgram();
    GLuint vs = create_compiled_shader(vertex_source, GL_VERTEX_SHADER);
    GLuint fs = create_compiled_shader(fragment_source, GL_FRAGMENT_SHADER);
    GLint linked;

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked ) {
        return 0;
    }

    return program;
}

}

namespace engine {

renderer::renderer()
{
    m_program = create_compiled_program(vertex_shader, fragment_shader);
//    m_program = create_compiled_program(debug_vertex_shader, debug_fragment_shader);
    m_program_context.position_attrib = glGetAttribLocation(m_program, "position");
    m_program_context.normal_attrib = glGetAttribLocation(m_program, "normal");
    m_program_context.texcoord_attrib = glGetAttribLocation(m_program, "texcoord");
    m_program_context.proj_matrix_uniform = glGetUniformLocation(m_program, "proj_matrix");
    m_program_context.view_matrix_uniform = glGetUniformLocation(m_program, "view_matrix");
    m_program_context.proj_view_matrix_uniform = glGetUniformLocation(m_program, "proj_view_matrix");
    m_program_context.model_matrix_uniform = glGetUniformLocation(m_program, "model_matrix");
    m_program_context.normal_matrix_uniform = glGetUniformLocation(m_program, "normal_matrix");
    m_program_context.diffuse_texture_uniform = glGetUniformLocation(m_program, "diffuse_texture");
}

std::shared_ptr<camera> renderer::create_camera()
{
    return std::make_shared<camera>();
}

std::shared_ptr<mesh> renderer::create_mesh(const mesh_data &data)
{
    return std::make_shared<mesh>(data);
}

std::shared_ptr<drawable> renderer::create_drawable()
{
    return std::make_shared<drawable>();
}

std::shared_ptr<texture> renderer::create_texture(const texture_data &data)
{
    return std::make_shared<texture>(data);
}

void renderer::attach_camera(const std::shared_ptr<camera> &camera)
{
    m_camera = camera;
}

void renderer::attach_drawable(const std::shared_ptr<drawable> &drawable)
{
    m_drawable_list.push_back(drawable);
}

void renderer::render_frame()
{
    glEnable(GL_DEPTH_TEST);

    glUseProgram(m_program);

    glEnableVertexAttribArray(m_program_context.position_attrib);
    glEnableVertexAttribArray(m_program_context.normal_attrib);
    glEnableVertexAttribArray(m_program_context.texcoord_attrib);

    if (m_camera != nullptr) {
        m_camera->render(m_program_context);
    }

    for (auto drawable : m_drawable_list) {
        drawable->render(m_program_context);
    }
}

}
