#include <GL/glew.h>
#include <GL/freeglut.h>

#include "engine/renderer.h"
#include "engine/camera.h"

engine::renderer renderer;

void init() {
    auto camera = renderer.create_camera();
    camera->set_position(0, 0, -5);
    renderer.attach_camera(camera);
}

void display() {
    renderer.render_frame();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("RPG");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
