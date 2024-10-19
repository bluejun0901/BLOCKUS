//
//  camera.c
//  BLOCKUS
//
//  Created by 김명준 on 8/2/24.
//

#include "camera.h"

double camera_x = 0.0;
double camera_y = 0.0;
double camera_z = 5.0;

void camera_move(diraction dir, double amout) {
    // TODO: 자연스러운 움직임 구현
    camera_z += delta_z[dir] * amout;
    camera_y += delta_y[dir] * amout;
    camera_x += delta_x[dir] * amout;
}
