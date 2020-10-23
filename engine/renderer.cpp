#include "renderer.h"

#include "camera.h"
#include "mesh.h"
#include "drawable.h"

#include <string.h>

namespace {

const char *vertex_shader =
        "#version 330 core\n"
        "in vec3 position;\n"
        "in vec3 normal;\n"
        "uniform mat4 proj_matrix;\n"
        "uniform mat4 view_matrix;\n"
        "uniform mat4 model_matrix;\n"
        "out vec3 p;\n"
        "out vec3 n;\n"
        "void main(void)\n"
        "{\n"
        "   p = (model_matrix * vec4(position, 1.0)).xyz;\n"
        "   n = normal;\n"
        "	gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position, 1.0);\n"
        "}\n";

const char *fragment_shader =
        "#version 330 core\n"
        "in vec3 p;\n"
        "in vec3 n;\n"
        "out vec4 color;\n"
        "uniform mat3 normal_matrix;\n"
        "void main(void)\n"
        "{\n"
        "   vec3 light_pos = vec3(0.0, 7.0, -10.0);\n"
        "   vec3 light_dir = normalize(light_pos - p);\n"
        "   float shade = dot(normal_matrix * n, light_dir);\n"
        "	color = max(shade, 0.2) * vec4(1.0);\n"
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
}

std::shared_ptr<camera> renderer::create_camera()
{
    return std::make_shared<camera>();
}

std::shared_ptr<mesh> renderer::create_mesh(const mesh_def &def)
{
    return std::make_shared<mesh>(def);
}

std::shared_ptr<drawable> renderer::create_drawable()
{
    return std::make_shared<drawable>();
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

    render_context context;
    context.position_attrib = glGetAttribLocation(m_program, "position");
    context.normal_attrib = glGetAttribLocation(m_program, "normal");
    context.proj_matrix_uniform = glGetUniformLocation(m_program, "proj_matrix");
    context.view_matrix_uniform = glGetUniformLocation(m_program, "view_matrix");
    context.model_matrix_uniform = glGetUniformLocation(m_program, "model_matrix");
    context.normal_matrix_uniform = glGetUniformLocation(m_program, "normal_matrix");

    glEnableVertexAttribArray(context.position_attrib);
    glEnableVertexAttribArray(context.normal_attrib);

    if (m_camera != nullptr) {
        m_camera->render(context);
    }

    for (auto drawable : m_drawable_list) {
        drawable->render(context);
    }
}

}
