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

    int size, full, ascending, pause;
    size = 10;
    full = 2 * M_PI;
    ascending = 1;
    pause = 1;
    double theta, resolutionX, resolutionY, offset;
    theta = 0;
    resolutionX = 0.5 * M_PI;
    resolutionY = 0.015625 * M_PI;
    offset = 0;
    double sphere[3] = {size, 0, 0};
    int point[3];

    while (1) {
        //move up and down
        if (pause > 40) {
            if (ascending) {
                offset += 0.1;
                if (offset > 4) {
                    ascending = 0;
                    pause = 0;
                }
            } else {
                offset -= 0.1;
                if (offset < -4) {
                    ascending = 1;
                    pause = 0;
                }
            }
        }else
            pause++;

        //draw vertical rings
        for (sphere[1] = theta; sphere[1] < theta + full; sphere[1] += resolutionX)
            for (sphere[2] = 0; sphere[2] <= M_PI; sphere[2] += resolutionY) {
                //convert to cartesian coordinate system
                point[0] = sphere[0] * sin(sphere[2]) * cos(sphere[1]);
                point[1] = sphere[0] * sin(sphere[2]) * sin(sphere[1]);
                point[2] = sphere[0] * cos(sphere[2]) + offset;
                //plot
                plot(point);
            }

        //horizontal ring
        sphere[2] = 0.5 * M_PI;
        for (sphere[1] = theta; sphere[1] < theta + 2 * M_PI; sphere[1] += 0.015625 * M_PI) {
            //convert to cartesian coordinate system
            point[0] = sphere[0] * sin(sphere[2]) * cos(sphere[1]);
            point[1] = sphere[0] * sin(sphere[2]) * sin(sphere[1]);
            point[2] = sphere[0] * cos(sphere[2]) + offset;
            //plot
            plot(point);
        }

        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
        theta += 0.05;
    }

    /*
    sphere[2] = 0.5 * M_PI;
        for (sphere[1] = theta; sphere[1] < theta + 2 * M_PI; sphere[1] += 0.015625 * M_PI){
            //convert to cartesian coordinate system
                point[0] = sphere[0] * sin(sphere[2]) * cos(sphere[1]);
                point[1] = sphere[0] * sin(sphere[2]) * sin(sphere[1]);
                point[2] = sphere[0] * cos(sphere[2]);
                //plot
                plot(point);
        }
     */

    while (1);
    return 0;
}
