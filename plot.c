#include <math.h>

#include "BOARD.h"
#include "Oled.h"
#include "OledDriver.h"

void plotPoint(int point[3]);
void plotLine(int point0[3], int point1[3]);

void plotPoint(int point[3])
{
    int result[2];
    int center[2] = {OLED_DRIVER_PIXEL_COLUMNS / 2, OLED_DRIVER_PIXEL_ROWS / 2};
    double theta, fov, viewingAngle;

    //viewing angle
    viewingAngle = 0;
    
    //changes field of view
    fov = 100;

    //how steep the angle is depending on z
    theta = (M_PI * (point[2] / fov)) - viewingAngle;

    //translateX
    result[0] = point[0] * cos(theta);
    result[1] = point[0] * sin(theta);
    //reflect theta across y axis
    theta = M_PI - theta;
    //translateY
    result[0] += point[1] * cos(theta);
    result[1] += point[1] * sin(theta);
    //translateZ
    result[1] += point[2];

    //invert image
    result[0] = OLED_DRIVER_PIXEL_COLUMNS - (result[0] + center[0]);
    result[1] = OLED_DRIVER_PIXEL_ROWS - (result[1] + center[1]);

    OledSetPixel(result[0], result[1], OLED_COLOR_WHITE);
}

void plotLine(int point0[3], int point1[3])
{
    //equation of line
    double line[3] = {
        point1[0] - point0[0],
        point1[1] - point0[1],
        point1[2] - point0[2]
    };
    int point[3];
    
    //distance formula
    int magnitude = sqrt(pow(line[0], 2) + pow(line[1], 2) + pow(line[2], 2));
    int i, j;
    
    for (j = 0; j < 3; j++)
            line[j] /= magnitude;

    //draw line
    for (i = 0; i < magnitude; i++) {
        for (j = 0; j < 3; j++)
            point[j] = point0[j] + (i * line[j]);
        printf("%d, %d, %d\n", point[0], point[1], point[2]);
        plotPoint(point);
    }
}