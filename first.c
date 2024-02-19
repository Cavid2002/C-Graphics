#include "Primitives.c"

Point2Di p_arr[] = {{-100, -100}, {100, 200}, {300, -150}, {50, 100}};
ColorD rgb = {1.0 , 1.0, 0.0};
ColorD rgb2 = {1.0 , 0.0, 1.0};
ColorD rgb_bg = {0.0 , 0.0, 0.0};
Rectangle2D rec;
Cube cube;
Cube cube2;
int speedx = 10, speedy = 10;

double alpha = 1;

void display()
{

    clear_screen(&rgb_bg);
    
    translate3D(speedx, speedy, 0);
    //rotate3D(cube.p_arr, 8, alpha);
    draw_cube(&cube);
    draw_cube(&cube2);

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
    Point3Di p_init2 = {-300, -300, 1};
    //rec = create_rec(&p_init, 50, &rgb);

    cube = create_cube(&p_init, 200, 200, 200, &rgb);
    cube2 = create_cube(&p_init2, 100, 100, 100, &rgb2);
}


void reshape(int l, int h)
{
    glViewport(0, 0, l, h);
    glutReshapeWindow(WINDOW_W, WINDOW_H);
}

void change_frame(int t)
{
    glutPostRedisplay();
    glutTimerFunc(FPS, change_frame, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        speedy += 5;
        printf("W KEY HAS BEEN PRESSED\n");
        break;
    case 's':
        speedy -= 5;
        printf("S KEY HAS BEEN PRESSED\n");
        break;
    case 'a':
        speedx -= 5;
        printf("A KEY HAS BEEN PRESSED\n");
        break;
    case 'd':
        speedx += 5;
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
