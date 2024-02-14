#include "Primitives.c"

Point2Di p_arr[] = {{-100, -100}, {100, 200}, {300, -150}, {50, 100}};
ColorD rgb = {1.0 , 1.0, 0.0};
ColorD rgb2 = {1.0 , 0.0, 1.0};
ColorD rgb_bg = {0.0 , 0.0, 0.0};
Rectangle2D rec;
Cube cube;
int speedx = 10, speedy = 10;

double alpha = 1;

void display()
{

    clear_screen(&rgb_bg);
    
    rotate3D(cube.p_arr, 8, alpha);
    draw_cube(&cube);

    // draw_verticies(cube.p_arr, 8, &cube.rgb);
    glutSwapBuffers();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_W, WINDOW_H, 0);
    glMatrixMode(GL_MODELVIEW);

    Point3Di p_init = {-100, -100, 1};
    //rec = create_rec(&p_init, 50, &rgb);

    cube = create_cube(&p_init, 200, 200, 200, &rgb);
}


void reshape(int l, int h)
{
    glViewport(0, 0, l, h);
    glutReshapeWindow(WINDOW_W, WINDOW_H);
}

void change_frame(int)
{
    glutPostRedisplay();
    glutTimerFunc(FPS, change_frame, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        translate3D(cube.p_arr, 8, 0, speedy, 0);
        printf("W KEY HAS BEEN PRESSED\n");
        break;
    case 's':
        translate3D(cube.p_arr, 8, 0, -speedy, 0);
        printf("S KEY HAS BEEN PRESSED\n");
        break;
    case 'a':
        translate3D(cube.p_arr, 8, -speedx, 0, 0);
        printf("A KEY HAS BEEN PRESSED\n");
        break;
    case 'd':
        translate3D(cube.p_arr, 8, speedx, 0, 0);
        printf("D KEY HAS BEEN PRESSED\n");
        break;
    default:
        break;
    }
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("New Window");
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutTimerFunc(1000, change_frame, 0);
    glutMainLoop();
    return 0;
}
