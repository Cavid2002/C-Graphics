//prototype on OPENGL
#include "Primitives.h"
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


Point2Di convert3D_to_2D(Point3Di* p)
{
    Point2Di res;
    int z = p->z + Z_NEAR;
    res.x = (p->x * Z_NEAR) / z;
    res.y = (p->y * Z_NEAR) / z;
    return res;
}

Point2Di convert2D_to_screen(Point2Di* p)
{
    Point2Di res;
    res.x = WINDOW_W * (p->x + X_MAX) / (2 * X_MAX);
    res.y = WINDOW_H * (Y_MAX - p->y) / (2 * Y_MAX); 
    return res;
}

void swap_points(Point2Di* p1, Point2Di* p2)
{
    Point2Di temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void putPixel(int px, int py)
{
    glPointSize(10);
    glBegin(GL_POINTS);

        glVertex2i(px, py);

    glEnd();
}


void draw_line_screen(int x0, int y0, int x1, int y1, ColorD* rgb) {
    int x = x0, y = y0;

    int dx = abs(x1 - x0),dy = abs(y1 - y0);
    int err = dx - dy;

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    glColor3f(rgb->R, rgb->G, rgb->B);
    while (1) {
        putPixel(x, y);
        if (x == x1 && y == y1) {
            break;
        }
        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (err2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

void draw_line(Point2Di* p1, Point2Di* p2, ColorD* rgb)
{
    Point2Di p1_res = convert2D_to_screen(p1);
    Point2Di p2_res = convert2D_to_screen(p2);
    draw_line_screen(p1_res.x, p1_res.y, p2_res.x, p2_res.y, rgb);
}

int* interpolate(Point2Di* p1, Point2Di* p2)
{
    int dx = p2->x - p1->x, dy = p2->y - p1->y;
    int steps = abs(dy);
    
    int* x_arr = malloc(sizeof(int) * (steps + 1));
    x_arr[0] = steps;

    float px = p1->x, xinc = dx / (float)steps;

    for(int i = 0; i < steps; i++)
    {
        px += xinc;
        x_arr[i + 1] = round(px);
    }

    return x_arr;
}

void draw_triangle_fill(Point2Di* p_arr, ColorD* rgb)
{
    if(p_arr[0].y > p_arr[1].y) swap_points(&p_arr[0], &p_arr[1]);
    if(p_arr[0].y > p_arr[2].y) swap_points(&p_arr[0], &p_arr[2]);
    if(p_arr[1].y > p_arr[2].y) swap_points(&p_arr[1], &p_arr[2]);
    
    Point2Di res_p[3];
    for(int i = 0; i < 3; i++)
    {
        res_p[i] = convert2D_to_screen(&p_arr[i]);
    }

    int* x_arr[3];
    x_arr[0] = interpolate(&res_p[0], &res_p[1]);
    x_arr[1] = interpolate(&res_p[1], &res_p[2]);
    x_arr[2] = interpolate(&res_p[0], &res_p[2]);

    int k = 0, size, y = res_p[0].y;
    glColor3d(rgb->R, rgb->G, rgb->B);
    for(int i = 0; i < 2; i++)
    {
        size = x_arr[i][0];
        for(int j = 1; j < size; j++, k++)
        {
            if(x_arr[i][size / 2] < x_arr[2][size / 2])
            {
                for(int x = x_arr[i][j]; x < x_arr[2][k]; x++)
                {
                    putPixel(x, y);
                }
            }
            else
            {
                for(int x = x_arr[2][k]; x < x_arr[i][j]; x++)
                {
                    putPixel(x, y);
                }
            }
            y--;
        }
    }

    for(int i = 0; i < 3; i++)
    {
        free(x_arr[i]);
    }
}

void draw_triangle_fill3D(Point3Di* p_arr, ColorD* rgb)
{
    Point2Di p2_arr[3];
    for(int i = 0; i < 3; i++)
    {
        p2_arr[i] = convert3D_to_2D(&p_arr[i]);
    }
    draw_triangle_fill(p2_arr, rgb);
}

void draw_rectangle_fill(Point2Di* p_arr, ColorD* rgb)
{
    Point2Di p_sarr[2];
    p_sarr[0] = convert2D_to_screen(&p_arr[0]);
    p_sarr[1] = convert2D_to_screen(&p_arr[1]);
    
    int ytop  = p_sarr[0].y, ybtm = p_sarr[1].y;
    if(p_sarr[0].y > p_sarr[1].y)
    {
        ytop = p_sarr[1].y;
        ybtm = p_sarr[0].y;
    }
    int xleft = p_sarr[0].x, xright = p_sarr[1].x;
    if(p_sarr[0].x > p_sarr[1].x)
    {
        xleft = p_sarr[1].x;
        xright = p_sarr[0].x;
    }    
    glColor3d(rgb->R, rgb->G, rgb->B);
    for(int y = ytop; y < ybtm; y++)
    {
        for(int x = xleft; x < xright; x++)
        {
            putPixel(x, y);
        }
    }
}

void clear_screen(ColorD* rgb)
{
    glColor3d(rgb->R, rgb->G, rgb->B);
    for(int i = 0; i < WINDOW_H; i++)
    {
        for(int j = 0; j < WINDOW_W; j++)
        {
            putPixel(j, i);
        }
    }
}

Rectangle2D create_rec(Point2Di* init, int size, ColorD* rgb)
{
    Rectangle2D rec;
    rec.p_arr[0].x = init->x; rec.p_arr[0].y = init->y;
    rec.p_arr[1].x = init->x + size; rec.p_arr[1].y = init->y + size;
    rec.rgb = *rgb;
    return rec;
}

Cube create_cube(Point3Di* init, int xl, int yl, int zl, ColorD* rgb)
{
    Cube cube;
    cube.p_arr[0].x = init->x;      cube.p_arr[0].y = init->y;      cube.p_arr[0].z = init->z;   
    cube.p_arr[1].x = init->x + xl; cube.p_arr[1].y = init->y;      cube.p_arr[1].z = init->z;
    cube.p_arr[2].x = init->x + xl; cube.p_arr[2].y = init->y + yl; cube.p_arr[2].z = init->z;
    cube.p_arr[3].x = init->x;      cube.p_arr[3].y = init->y + yl; cube.p_arr[3].z = init->z;
    cube.p_arr[4].x = init->x;      cube.p_arr[4].y = init->y;      cube.p_arr[4].z = init->z + zl;
    cube.p_arr[5].x = init->x + xl; cube.p_arr[5].y = init->y;      cube.p_arr[5].z = init->z + zl;
    cube.p_arr[6].x = init->x + xl; cube.p_arr[6].y = init->y + yl; cube.p_arr[6].z = init->z + zl;
    cube.p_arr[7].x = init->x;      cube.p_arr[7].y = init->y + yl; cube.p_arr[7].z = init->z + zl;

    cube.rgb = *rgb;
    return cube;
}

void draw_verticies(Point3Di* p_arr, int count ,ColorD* rgb)
{
    glColor3d(rgb->R, rgb->G, rgb->B);
    Point2Di temp;
    for(int i = 0; i < count; i++)
    {
        temp = convert3D_to_2D(&p_arr[i]);
        temp = convert2D_to_screen(&temp);
        putPixel(temp.x, temp.y);
    }
}

void draw_cube(Cube* cube)
{
    Point2Di res_arr[8];
    for(int i = 0; i < 8; i++)
    {
        res_arr[i] = convert3D_to_2D(&cube->p_arr[i]);
    }

    draw_line(&res_arr[0], &res_arr[1], &cube->rgb);
    draw_line(&res_arr[1], &res_arr[2], &cube->rgb);
    draw_line(&res_arr[2], &res_arr[3], &cube->rgb);
    draw_line(&res_arr[3], &res_arr[0], &cube->rgb);

    draw_line(&res_arr[4], &res_arr[5], &cube->rgb);
    draw_line(&res_arr[5], &res_arr[6], &cube->rgb);
    draw_line(&res_arr[6], &res_arr[7], &cube->rgb);
    draw_line(&res_arr[7], &res_arr[4], &cube->rgb);

    draw_line(&res_arr[0], &res_arr[4], &cube->rgb);
    draw_line(&res_arr[1], &res_arr[5], &cube->rgb);
    draw_line(&res_arr[2], &res_arr[6], &cube->rgb);
    draw_line(&res_arr[3], &res_arr[7], &cube->rgb);


}

void translate3D(Point3Di* p_arr, int size, int x, int y, int z)
{
    for(int i = 0; i < size; i++)
    {
        p_arr[i].x += x;
        p_arr[i].y += y;
        p_arr[i].z += z;
    }
}

void translate2D(Point2Di* p_arr, int count, int x, int y)
{
    for(int i = 0; i < count; i++)
    {
        p_arr[i].x += x;
        p_arr[i].y += y;
    }
}

void rotate3D(Point3Di* p_arr, int count, double alpha_deg)
{
    Point2Dd temp;
    double alpha_rad = RAD_TO_DEG * alpha_deg;
    double cos_d = cos(alpha_rad);
    double sin_d = sin(alpha_rad);
    for(int i = 0; i < count; i++)
    {
        temp.x = round(p_arr[i].x * cos_d) - round(p_arr[i].z * sin_d);
        temp.y = round(p_arr[i].x * sin_d) + round(p_arr[i].z * cos_d);

        p_arr[i].x = temp.x;
        p_arr[i].z = temp.y; 
    }
}