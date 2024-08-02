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

// 블록 종류 정의
typedef enum _block_type {
    EMPTY = 0,
    WHITE = 1,
    BLACK = 2
} block_type;

#endif /* common_h */
