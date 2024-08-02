//
//  board.c
//  BLOCKUS
//
//  Created by 김명준 on 8/2/24.
//

#include "board.h"

#include "common.h"
#include "graphics.h"

block_type board[max_height][board_height][board_width];

void initBoard(void) {
    for (int z = 0; z < max_height; z++) {
        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                if (z == 0) {
                    board[z][y][x] = ((x + y) % 2 == 0 ? WHITE : BLACK);
                } else {
                    board[z][y][x] = EMPTY;
                }
            }
        }
    }
}

void drawBoard(void) {
    for (int z = 0; z < max_height; z++) {
        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                drawBlock(z, y, x, board[z][y][x], 0.0);
            }
        }
    }
}
