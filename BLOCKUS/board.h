//
//  board.h
//  BLOCKUS
//
//  Created by 김명준 on 8/2/24.
//

#ifndef board_h
#define board_h

#include "common.h"

/* 게임판 좌표계 */
// x축: 오른쪽 방향
// y축: 화면으로 들어가는 방향
// z축: 위쪽 방향
// 게임판 좌표로 (x, y, z) = 화면 좌표로 (-x, z, y)

#define board_width 5  // 게임판 가로 크기
#define board_height 8 // 게임판 세로 크기
#define max_height 100 // 게임판에 놓을 수 있는 블록의 최대 높이
extern block_type board[max_height][board_height][board_width]; // board[z좌표][y좌표][x좌표]로 접근

/* 보드를 초기화하는 함수 */
void initBoard(void);

/* 보드를 그리는 함수 */
void drawBoard(void);

#endif /* board_h */
