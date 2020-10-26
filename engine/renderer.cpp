#include "renderer.h"

#include <FreeImage.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <string.h>

#include "camera.h"
#include "mesh.h"
#include "drawable.h"
#include "texture.h"

namespace {

const char *vertex_shader =
        "#version 330 core\n"
        "in vec3 position;\n"
        "in vec3 normal;\n"
        "in vec3 tangent;\n"
        "in vec3 bitangent;\n"
        "in vec2 texcoord;\n"
        "uniform mat4 proj_matrix;\n"
        "uniform mat4 view_matrix;\n"
        "uniform mat4 model_matrix;\n"     
        "out vec3 p;\n"
        "out vec2 t;\n"
        "out mat3 TBN;\n"
        "out vec3 view_dir;\n"
        "void main(void)\n"
        "{\n"
        "   p = (model_matrix * vec4(position, 1.0)).xyz;\n"
        "   t = texcoord;\n"
        "   vec3 T = normalize(vec3(model_matrix * vec4(tangent,   0.0)));\n"
        "   vec3 B = normalize(vec3(model_matrix * vec4(bitangent, 0.0)));\n"
        "   vec3 N = normalize(vec3(model_matrix * vec4(normal,    0.0)));\n"
        "   TBN = mat3(T, B, N);\n"
        "	gl_Position = proj_matrix * view_matrix * model_matrix * vec4(position, 1.0);\n"
        "   view_dir = vec3(0.0, 0.0, 1.0);//-vec3(view_matrix * model_matrix * vec4(position, 1.0));\n"
        "}\n";

const char *fragment_shader =
        "#version 330 core\n"
        "in vec3 p;\n"
        "in vec2 t;\n"
        "in mat3 TBN;\n"
        "in vec3 view_dir;\n"
        "out vec4 color;\n"
        "uniform sampler2D diffuse_texture;\n"
        "uniform sampler2D normal_texture;\n"
        "uniform sampler2D roughness_texture;\n"
        "uniform sampler2D occlusion_texture;\n"
        "void main(void)\n"
        "{\n"
        "   vec3 light_pos = vec3(0.0, 0.0, -10.0);\n"
        "   vec3 light_dir = normalize(light_pos - p);\n"
        "   vec3 normal = texture(normal_texture, t).xyz * 2.0 - 1.0;\n"
        "   normal = normalize(TBN * normal);\n"
        "   float shade = dot(normal, light_dir);\n"
        "   float shininess_factor = 32.0;\n"
        "   float roughness = texture(roughness_texture, t).x;\n"
        "   vec3 reflect_dir = reflect(light_dir, normal);\n"
        "   float shininess = (pow((1.0 - roughness) * 1.5, 3.0) * shininess_factor);\n"
        "   float specular = pow(max(0.0, dot(view_dir, reflect_dir)), shininess) * (shininess / shininess_factor);\n"
        "   vec4 ambient = vec4(0.04, 0.08, 0.16, 1.0) * (1.0 - shade);\n"
        "	color = ambient + shade * texture(diffuse_texture, t) * texture(occlusion_texture, t) + specular;\n"
//        "   color = vec4(shininess) / shininess_factor;\n"
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
    m_program_context.position_attrib = glGetAttribLocation(m_program, "position");
    m_program_context.normal_attrib = glGetAttribLocation(m_program, "normal");
    m_program_context.tangent_attrib = glGetAttribLocation(m_program, "tangent");
    m_program_context.bitangent_attrib = glGetAttribLocation(m_program, "bitangent");
    m_program_context.texcoord_attrib = glGetAttribLocation(m_program, "texcoord");
    m_program_context.proj_matrix_uniform = glGetUniformLocation(m_program, "proj_matrix");
    m_program_context.view_matrix_uniform = glGetUniformLocation(m_program, "view_matrix");
    m_program_context.proj_view_matrix_uniform = glGetUniformLocation(m_program, "proj_view_matrix");
    m_program_context.model_matrix_uniform = glGetUniformLocation(m_program, "model_matrix");
    m_program_context.normal_matrix_uniform = glGetUniformLocation(m_program, "normal_matrix");
    m_program_context.diffuse_texture_uniform = glGetUniformLocation(m_program, "diffuse_texture");
    m_program_context.normal_texture_uniform = glGetUniformLocation(m_program, "normal_texture");
    m_program_context.roughness_texture_uniform = glGetUniformLocation(m_program, "roughness_texture");
    m_program_context.occlusion_texture_uniform = glGetUniformLocation(m_program, "occlusion_texture");

    {
        texture_data data;
        data.width = 32;
        data.height = 32;
        for (int i = 0; i < 32 * 32; ++i)
            data.rgba.push_back(rgba_data { 255, 255, 255, 255 });
        m_program_context.default_diffuse_texture = create_texture(data);
    }

    {
        texture_data data;
        data.width = 32;
        data.height = 32;
        for (int i = 0; i < 32 * 32; ++i)
            data.rgba.push_back(rgba_data { 127, 127, 255, 255 });
        m_program_context.default_normal_texture = create_texture(data);
    }

    {
        texture_data data;
        data.width = 32;
        data.height = 32;
        for (int i = 0; i < 32 * 32; ++i)
            data.rgba.push_back(rgba_data { 255, 255, 255, 255 });
        m_program_context.default_roughness_texture = create_texture(data);
    }

    {
        texture_data data;
        data.width = 32;
        data.height = 32;
        for (int i = 0; i < 32 * 32; ++i)
            data.rgba.push_back(rgba_data { 255, 255, 255, 255 });
        m_program_context.default_occlusion_texture = create_texture(data);
    }
}

std::shared_ptr<camera> renderer::create_camera()
{
    return std::make_shared<camera>();
}

std::shared_ptr<mesh> renderer::create_mesh(const mesh_data &data)
{
    return std::make_shared<mesh>(data);
}

std::shared_ptr<mesh> renderer::load_mesh(const char *name)
{
    mesh_data data;

    Assimp::Importer importer;
    auto scene = importer.ReadFile(name, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

    for (size_t i = 0; i < scene->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[i];
        for (size_t j = 0; j < mesh->mNumVertices; ++j) {
            const auto &v = mesh->mVertices[j];
            const auto &n = mesh->mNormals[j];
            const auto &tg = mesh->mTangents[j];
            const auto &bt = mesh->mBitangents[j];
            if (mesh->GetNumUVChannels() >= 1) {
                const auto &t = mesh->mTextureCoords[0][j];
                data.vertices.push_back(
                    vertex {
                        v.x, v.y, v.z,
                        n.x, n.y, n.z,
                        tg.x, tg.y, tg.z,
                        bt.x, bt.y, bt.z,
                        t.x, t.y
                    }
                );
            }
        }
    }

    return create_mesh(data);
}

std::shared_ptr<drawable> renderer::create_drawable()
{
    return std::make_shared<drawable>();
}

std::shared_ptr<texture> renderer::create_texture(const texture_data &data)
{
    return std::make_shared<texture>(data);
}

std::shared_ptr<texture> renderer::load_texture(const char *name)
{
    FREE_IMAGE_FORMAT free_image_format = FreeImage_GetFileType(name, 0);
    FIBITMAP* fibitmap = FreeImage_Load(free_image_format, name);
    FIBITMAP* temp = fibitmap;
    fibitmap = FreeImage_ConvertTo32Bits(fibitmap);
    FreeImage_Unload(temp);

    int width = FreeImage_GetWidth(fibitmap);
    int height = FreeImage_GetHeight(fibitmap);
    char* pixels = (char*)FreeImage_GetBits(fibitmap);

    texture_data data;
    data.width = width;
    data.height = height;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int offset = width * i * 4 + j * 4;
            data.rgba.push_back(
                rgba_data {
                    static_cast<unsigned char>(pixels[offset + 2]),
                    static_cast<unsigned char>(pixels[offset + 1]),
                    static_cast<unsigned char>(pixels[offset + 0]),
                    static_cast<unsigned char>(pixels[offset + 3])
                }
            );
        }
    }

    FreeImage_Unload(fibitmap);

    return create_texture(data);
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
    glEnableVertexAttribArray(m_program_context.tangent_attrib);
    glEnableVertexAttribArray(m_program_context.bitangent_attrib);
    glEnableVertexAttribArray(m_program_context.texcoord_attrib);

    if (m_camera != nullptr) {
        m_camera->render(m_program_context);
    }

    for (auto drawable : m_drawable_list) {
        drawable->render(m_program_context);
    }
}

}
