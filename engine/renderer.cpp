#include "renderer.h"

#include "camera.h"
#include "mesh.h"
#include "drawable.h"

#include <string.h>

namespace {

const char *vertex_shader =
        "#version 330 core\n" \
        "in vec3 position;\n" \
        "void main(void)\n" \
        "{\n" \
        "	gl_Position   = vec4 ( position, 1.0 );\n" \
        "}\n";

const char *fragment_shader =
        "#version 330 core\n" \
        "out vec4 color;\n"   \
        "void main(void)\n"   \
        "{\n"                 \
        "	color = vec4 ( 1.0);\n" \
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

    if (m_camera != nullptr)
        m_camera->clear_screen();

    glUseProgram(m_program);

    render_context context;
    context.position_attrib = glGetAttribLocation (m_program, "position");
    glEnableVertexAttribArray(context.position_attrib);

    for (auto drawable : m_drawable_list) {
        drawable->render(context);
    }
}

}
