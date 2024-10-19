//
//  common.h
//  BLOCKUS
//
//  Created by 김명준 on 8/2/24.
//

#ifndef common_h
#define common_h

// 주변 탐색을 위한 배열
extern const int delta_x[];
extern const int delta_y[];
extern const int delta_z[];

// 방향 정의
typedef enum _diraction {
    RIGHT = 0,
    LEFT,
    INWARD,
    OUTWARD,
    UP,
    DOWN
} diraction;

// 블록 종류 정의
typedef enum _block_type {
    EMPTY = 0,
    WHITE,
    BLACK
} block_type;

#endif /* common_h */
