#define PI 3.14159265359

#define WINDOW_W 500
#define WINDOW_H 500
#define FPS 1000 / 60
#define X_MAX 500
#define Y_MAX 500

#define PIXEL_SIZE 5

#define Z_MAX X_MAX + Y_MAX
#define Z_MIN 1

#define Z_NEAR 1000
#define Z_FAR 11

#define RAD_TO_DEG PI / 180.0

typedef struct{
    int x, y;
} Point2Di;

typedef struct{
    int x, y, z;
} Point3Di;

typedef struct{
    double x, y;
} Point2Dd;


typedef struct{
    double x, y, z;
} Point3Dd;

typedef struct{
    double R, G, B;
} ColorD; 

typedef struct{
    Point3Di p_arr[8];
    int size;
    ColorD rgb;
} Cube;

typedef struct{
    Point2Di p_arr[3];
    ColorD rgb;
} Triangle2D;

typedef struct
{
    Point2Di p_arr[2];
    ColorD rgb;
}  Rectangle2D;

