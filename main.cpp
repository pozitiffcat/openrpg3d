#include <GL/glew.h>
#include <GL/freeglut.h>

#include "engine/renderer.h"
#include "engine/camera.h"
#include "engine/drawable.h"

std::shared_ptr<engine::renderer> renderer;

void init() {
    renderer = std::make_shared<engine::renderer>();

    auto camera = renderer->create_camera();
    camera->set_position(0, 0, -5);
    renderer->attach_camera(camera);

    engine::mesh_def triangle_def;
    triangle_def.vertices.push_back(engine::vertex { -1, 0, 0, 0, 0, -1 });
    triangle_def.vertices.push_back(engine::vertex { 0, 1, 0, 0, 0, -1 });
    triangle_def.vertices.push_back(engine::vertex { 0, 0, 1, 0, 0, -1 });
    auto mesh = renderer->create_mesh(triangle_def);

    auto mesh_drawable = renderer->create_drawable();
    mesh_drawable->attach_mesh(mesh);
    renderer->attach_drawable(mesh_drawable);
}

void display() {
    renderer->render_frame();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("RPG");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
