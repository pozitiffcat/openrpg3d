#include <GL/glew.h>
#include <GL/freeglut.h>

#include <chrono>

#include "engine/renderer.h"
#include "engine/camera.h"
#include "engine/drawable.h"

std::shared_ptr<engine::renderer> renderer;
std::shared_ptr<engine::drawable> mesh_drawable;

void init() {
    renderer = std::make_shared<engine::renderer>();

    auto camera = renderer->create_camera();
    camera->set_position(0, 2, -4);
    camera->set_rotation(20, 0, 0);
    renderer->attach_camera(camera);

    std::vector<engine::vertex> cube_quad_vertices;
    cube_quad_vertices.push_back(engine::vertex { -1, -1,  1, 0, 0, 1, 0, 0 });
    cube_quad_vertices.push_back(engine::vertex { 1, -1,  1, 0, 0, 1, 0, 1 });
    cube_quad_vertices.push_back(engine::vertex { 1,  1,  1, 0, 0, 1, 1, 1 });
    cube_quad_vertices.push_back(engine::vertex { -1,  1,  1, 0, 0, 1, 1, 0 });
    cube_quad_vertices.push_back(engine::vertex { -1, -1, -1, 0, 0, -1, 0, 0 });
    cube_quad_vertices.push_back(engine::vertex { -1,  1, -1, 0, 0, -1, 0, 1 });
    cube_quad_vertices.push_back(engine::vertex { 1,  1, -1, 0, 0, -1, 1, 1 });
    cube_quad_vertices.push_back(engine::vertex { 1, -1, -1, 0, 0, -1, 1, 0 });
    cube_quad_vertices.push_back(engine::vertex { -1,  1, -1, 0, 1, 0, 0, 0 });
    cube_quad_vertices.push_back(engine::vertex { -1,  1,  1, 0, 1, 0, 0, 1 });
    cube_quad_vertices.push_back(engine::vertex { 1,  1,  1, 0, 1, 0, 1, 0 });
    cube_quad_vertices.push_back(engine::vertex { 1,  1, -1, 0, 1, 0, 1, 1 });
    cube_quad_vertices.push_back(engine::vertex { -1, -1, -1, 0, -1, 0, 0, 0 });
    cube_quad_vertices.push_back(engine::vertex { 1, -1, -1, 0, -1, 0, 0, 1 });
    cube_quad_vertices.push_back(engine::vertex { 1, -1,  1, 0, -1, 0, 1, 0 });
    cube_quad_vertices.push_back(engine::vertex { -1, -1,  1, 0, -1, 0, 1, 1 });
    cube_quad_vertices.push_back(engine::vertex { 1, -1, -1, 1, 0, 0, 0, 0 });
    cube_quad_vertices.push_back(engine::vertex { 1,  1, -1, 1, 0, 0, 0, 1 });
    cube_quad_vertices.push_back(engine::vertex { 1,  1,  1, 1, 0, 0, 1, 1 });
    cube_quad_vertices.push_back(engine::vertex { 1, -1,  1, 1, 0, 0, 1, 0 });
    cube_quad_vertices.push_back(engine::vertex { -1, -1, -1, -1, 0, 0, 0, 0 });
    cube_quad_vertices.push_back(engine::vertex { -1, -1,  1, -1, 0, 0, 0, 1 });
    cube_quad_vertices.push_back(engine::vertex { -1,  1,  1, -1, 0, 0, 1, 1 });
    cube_quad_vertices.push_back(engine::vertex { -1,  1, -1, -1, 0, 0, 1, 0 });

    engine::mesh_data cube_data;
    for (size_t i = 0; i < cube_quad_vertices.size(); i += 4) {
        cube_data.vertices.push_back(cube_quad_vertices[i + 0]);
        cube_data.vertices.push_back(cube_quad_vertices[i + 1]);
        cube_data.vertices.push_back(cube_quad_vertices[i + 2]);
        cube_data.vertices.push_back(cube_quad_vertices[i + 0]);
        cube_data.vertices.push_back(cube_quad_vertices[i + 2]);
        cube_data.vertices.push_back(cube_quad_vertices[i + 3]);
    }
    auto cube_mesh = renderer->create_mesh(cube_data);

    engine::texture_data cube_texture_data;
    cube_texture_data.width = 32;
    cube_texture_data.height = 32;
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j) {
            cube_texture_data.rgba.push_back(
                engine::rgba_data { 0, static_cast<unsigned char>(i * 8), static_cast<unsigned char>(j * 8), 255 }
            );
        }
    }

    engine::material_data cube_material;
    cube_material.diffuse_texture = renderer->create_texture(cube_texture_data);

    mesh_drawable = renderer->create_drawable();
    mesh_drawable->attach_mesh(cube_mesh);
    mesh_drawable->attach_material(cube_material);
    renderer->attach_drawable(mesh_drawable);

    {
        auto mesh_drawable = renderer->create_drawable();
        mesh_drawable->attach_mesh(cube_mesh);
        mesh_drawable->set_position(4, 0, 0);
        renderer->attach_drawable(mesh_drawable);
    }

    {
        auto mesh_drawable = renderer->create_drawable();
        mesh_drawable->attach_mesh(cube_mesh);
        mesh_drawable->set_position(-4, 0, 0);
        renderer->attach_drawable(mesh_drawable);
    }
}

void display() {
    auto now = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

    static int last_time_millis = millis;
    int delta_time_millis = millis - last_time_millis;
    last_time_millis = millis;

    static float r = 0;
    r += (delta_time_millis * 0.001 * 20); // 20 degrees per sec

    mesh_drawable->set_rotation(0, r, 0);
    renderer->render_frame();


    static int fps = 0;
    static int last_fps_time = 0;
    fps++;
    last_fps_time += delta_time_millis;

    if (last_fps_time >= 1000) {
        char window_title[128];
        sprintf(window_title, "openrpg3d FPS: %d", fps);
        glutSetWindowTitle(window_title);

        fps = 0;
        last_fps_time = 0;
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("openrpg3d");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
