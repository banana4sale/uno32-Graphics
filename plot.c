#include <math.h>

#include "BOARD.h"
#include "Oled.h"
#include "OledDriver.h"

void plot(int point[3]);

void plot(int point[3])
{
    int result[2];
    int center[2] = {OLED_DRIVER_PIXEL_COLUMNS / 2, OLED_DRIVER_PIXEL_ROWS / 2};
    double viewingAngle;
    
    //changes field of view
    viewingAngle = 0.90 * M_PI;
    
    //translateX
    result[0] = point[0] * cos(viewingAngle);
    result[1] = point[0] * sin(viewingAngle);
    //reflect theta across y axis
    viewingAngle = M_PI - viewingAngle;
    //translateY
    result[0] += point[1] * cos(viewingAngle);
    result[1] += point[1] * sin(viewingAngle);
    //translateZ
    result[1] += point[2];
    
    //invert image
    result[0] = OLED_DRIVER_PIXEL_COLUMNS - (result[0] + center[0]);
    result[1] = OLED_DRIVER_PIXEL_ROWS - (result[1] + center[1]);
    
    OledSetPixel(result[0], result[1], OLED_COLOR_WHITE);
}