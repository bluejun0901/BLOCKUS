//
//  cube.h
//  BLOCKUS
//
//  Created by 김명준 on 8/2/24.
//

#ifndef cube_h
#define cube_h

#include <stdio.h>
#include <stdbool.h>

#include "common.h"

#define cube_size 4 // 하나의 큐브를 저장하는 데 사용되는 공간의 크기 = 가장 큰 큐브의 크기
#define cube_num 11 // 큐브 종류의 수
extern const int fit_cube_size[cube_num]; // 큐브가 차지하는 실제 공간의 크기
extern block_type cube_data[cube_num][cube_size][cube_size][cube_size]; // [_][z좌표][y좌표][x좌표]로 접근
extern block_type rotated_cube_data[cube_num][4 * 4 * 4][cube_size][cube_size][cube_size]; // [_][z축 회전 * 16 + y축 회전 * 4 + x축 회전][z좌표][y좌표][x좌표]로 접근

/* cube_data, rotated_cube_data를 초기화하는 함수 */
void initCubeData(void);

typedef struct _cube {
    int cube_type;        // 0 ~ cube_num - 1의 정수 값을 가지며 큐브의 모양을 가리킴
    int x_rotation;       // x축을 기준으로 회전한 횟수
    int y_rotation;       // y축을 기준으로 회전한 횟수
    int z_rotation;       // z축을 기준으로 회전한 횟수
    bool color_inversion; // 색 반전 여부
} cube;

/* 큐브를 받아 큐브의 최종 형태를 반환하는 함수 */
/* a: 큐브 구조체 */
/* return: 큐브의 형태를 나타내는 cube_size * cube_size * cube_size크기의 3차원 배열을 가리키는 포인터 */
void* cube_getArray(cube a);

/* 큐브를 특정 위치에 놓을 수 있는지 여뷰를 반환하는 함수 */
/* a: 큐브 구조체 */
/* z0, y0, x0: 보드 좌표계에서 큐브의 왼쪽 아래 앞 꼭짓점의 위치 */
/* return: 큐브를 특정 위치에 놓을 수 있는지 여부 */
bool cube_canPut(cube a, int z0, int y0, int x0);

/* 큐브를 보드에 놓는 함수 */
/* a: 큐브 구조체 */
/* z0, y0, x0: 보드 좌표계에서 큐브의 왼쪽 아래 앞 꼭짓점의 위치 */
void cube_put(cube a, int z0, int y0, int x0);

/* 큐브를 특정 위치에 그리는 함수 */
/* a: 큐브 구조체 */
/* z0, y0, x0: 보드 좌표계에서 큐브의 왼쪽 아래 앞 꼭짓점의 위치 */
/* size: 큐브의 크기 */
void cube_draw(cube a, double z0, double y0, double x0, double size, bool abled);

#endif /* cube_h */
