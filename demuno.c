#include <math.h>
#include <stdio.h>

#include "Graphics.h"

#include "BOARD.h"
#include "Oled.h"
#include "OledDriver.h"

int main(void)
{
    BOARD_Init();
    OledInit();

    int size = 8;
    double theta = 0;
    double sphere[3] = {size, 0, 0};
    int point[3];

    while (1) {
        //draw vertical rings
        for (sphere[1] = theta; sphere[1] < theta + (2 * M_PI); sphere[1] += 0.5 * M_PI)
            for (sphere[2] = 0; sphere[2] <= M_PI; sphere[2] += 0.015625 * M_PI) {
                //convert to cartesian coordinate system
                point[0] = sphere[0] * sin(sphere[2]) * cos(sphere[1]);
                point[1] = sphere[0] * sin(sphere[2]) * sin(sphere[1]);
                point[2] = sphere[0] * cos(sphere[2]);
                //move to foreground
                point[0] += size;
                point[1] += size;
                //plot
                plotPoint(point);
            }
        
        //draw horizontal ring
        //for (sphere[2] = 0.35 * M_PI; sphere[2] <= 0.66 * M_PI; sphere[2] += 0.15 * M_PI)
        sphere[2] = 0.5 * M_PI;
        for (sphere[1] = theta; sphere[1] < theta + 2 * M_PI; sphere[1] += 0.125 * M_PI){
            //convert to cartesian coordinate system
                point[0] = sphere[0] * sin(sphere[2]) * cos(sphere[1]);
                point[1] = sphere[0] * sin(sphere[2]) * sin(sphere[1]);
                point[2] = sphere[0] * cos(sphere[2]);
                //move to foreground
                point[0] += size;
                point[1] += size;
                //plot
                plotPoint(point);
        }
        
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
        theta += 0.01;
        sphere[2] = 0;
    }

    //x=?sin?cos?,y=?sin?sin?,z=?cos?
    while (1);
    return 0;
}
