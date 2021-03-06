#include <GL/glew.h>
#include <GL/freeglut.h>

#include <chrono>

#include "engine/renderer.h"
#include "engine/camera.h"
#include "engine/drawable.h"

std::shared_ptr<engine::renderer> renderer;
std::shared_ptr<engine::camera> camera;
std::shared_ptr<engine::drawable> mesh_drawable;

void init() {
    renderer = std::make_shared<engine::renderer>();

    camera = renderer->create_camera();
    camera->set_position(0, 2, -4);
    camera->set_rotation(20, 0, 0);
    renderer->attach_camera(camera);

//    auto assimp_mesh = renderer->load_mesh("model/model.dae");
//    engine::material_data assimp_material;
//    assimp_material.diffuse_texture = renderer->load_texture("model/textures/beekaybee_albedo.jpg");
//    assimp_material.normal_texture = renderer->load_texture("model/textures/beekaybee_normal.png");
//    assimp_material.roughness_texture = renderer->load_texture("model/textures/beekaybee_roughness.jpg");
//    mesh_drawable = renderer->create_drawable();
//    mesh_drawable->attach_mesh(assimp_mesh);
//    mesh_drawable->attach_material(assimp_material);
//    renderer->attach_drawable(mesh_drawable);
//    mesh_drawable->set_scale(3, 3, 3);

    auto assimp_mesh = renderer->load_mesh("church/Nousiainen_Church_SF.obj");
    engine::material_data assimp_material;
    assimp_material.diffuse_texture = renderer->load_texture("church/Nousiainen_Church.jpg");
    assimp_material.normal_texture = renderer->load_texture("church/Nousiainen_Church_normal.jpg");
    assimp_material.occlusion_texture = renderer->load_texture("church/Nousiainen_Church_occlusion.jpg");
    mesh_drawable = renderer->create_drawable();
    mesh_drawable->attach_mesh(assimp_mesh);
    mesh_drawable->attach_material(assimp_material);
    renderer->attach_drawable(mesh_drawable);
    mesh_drawable->set_position(0, -10, 0);
    mesh_drawable->set_scale(0.3, 0.3, 0.3);
    camera->set_position(0, 5, -8);
    camera->set_rotation(60, 0, 0);
}

void display() {
    auto now = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

    static int last_time_millis = millis;
    int delta_time_millis = millis - last_time_millis;
    last_time_millis = millis;

    static float r = 180;
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

void reshape(int w, int h) {
    camera->set_viewport(0, 0, w, h);
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
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
