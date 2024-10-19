//
//  game_logic.h
//  BLOCKUS
//
//  Created by 김명준 on 8/3/24.
//

#ifndef game_logic_h
#define game_logic_h

#include "common.h"
#include "cube.h"

#define player_num 2 // 플레이어 수
#define player_cube_num 5 // 플레이어 한 사람이 가질 큐브의 수
extern cube player_cubes[player_num][player_cube_num];

extern int cube_z; // 플레이어가 선택하고 있는 큐브의 위치
extern int cube_y; // 플레이어가 선택하고 있는 큐브의 위치
extern int cube_x; // 플레이어가 선택하고 있는 큐브의 위치

extern int trun_count; // 턴 횟수

/* 플레이어에게 큐브를 무작위로 분배 */
void initPlayers(void);

/* 키보드 입력을 받아 게임을 진행함 */
void game_logic_step(unsigned char key);

/* 그리기 */
void game_logic_draw(void);

#endif /* game_logic_h */
