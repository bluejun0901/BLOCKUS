//
//  camera.h
//  BLOCKUS
//
//  Created by 김명준 on 8/2/24.
//

#ifndef camera_h
#define camera_h

#include "common.h"

// 카메라 정보
// TODO: 카메라 방향 등 정의
extern double camera_x;
extern double camera_y;
extern double camera_z;

// dir: common.h에 정의된 방향
// amout: 움직일 정도
void camera_move(diraction dir, double amout);

#endif /* camera_h */
