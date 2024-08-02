//
//  cube.c
//  BLOCKUS
//
//  Created by 김명준 on 8/2/24.
//

#include "cube.h"

#include <string.h>
#include <stdbool.h>
#include "common.h"
#include "board.h"
#include "graphics.h"

const int fit_cube_size[cube_num] = { 2, 3, 2, 4, 2, 3, 3, 3, 2, 2, 2 };
block_type cube_data[cube_num][cube_size][cube_size][cube_size];
block_type rotated_cube_data[cube_num][4 * 4 * 4][cube_size][cube_size][cube_size];

void initCubeData(void) {
    // cube2-0
    cube_data[0][0][0][0] = WHITE;
    cube_data[0][0][0][1] = BLACK;
    
    // cube3-0
    cube_data[1][0][0][0] = WHITE;
    cube_data[1][0][0][1] = BLACK;
    cube_data[1][0][0][2] = WHITE;
    
    // cube3-1
    cube_data[2][0][0][0] = WHITE;
    cube_data[2][0][0][1] = BLACK;
    cube_data[2][0][1][0] = BLACK;
    
    // cube4-0
    cube_data[3][0][0][0] = WHITE;
    cube_data[3][0][0][1] = BLACK;
    cube_data[3][0][0][2] = WHITE;
    cube_data[3][0][0][3] = BLACK;
    
    // cube4-1
    cube_data[4][0][0][0] = BLACK;
    cube_data[4][0][0][1] = WHITE;
    cube_data[4][0][1][0] = WHITE;
    cube_data[4][0][1][1] = BLACK;
    
    // cube4-2
    cube_data[5][0][0][0] = BLACK;
    cube_data[5][0][1][0] = WHITE;
    cube_data[5][0][1][1] = BLACK;
    cube_data[5][0][1][2] = WHITE;
    
    // cube4-3
    cube_data[6][0][0][0] = BLACK;
    cube_data[6][0][1][0] = WHITE;
    cube_data[6][0][1][1] = BLACK;
    cube_data[6][0][2][1] = WHITE;
    
    // cube4-4
    cube_data[7][0][0][0] = BLACK;
    cube_data[7][0][1][0] = WHITE;
    cube_data[7][0][1][1] = BLACK;
    cube_data[7][0][2][0] = BLACK;
    
    // cube4-5
    cube_data[8][0][0][0] = WHITE;
    cube_data[8][0][1][0] = BLACK;
    cube_data[8][0][1][1] = WHITE;
    cube_data[8][1][0][0] = BLACK;
    
    // cube4-6
    cube_data[9][0][0][0] = WHITE;
    cube_data[9][0][1][0] = BLACK;
    cube_data[9][0][1][1] = WHITE;
    cube_data[9][1][1][0] = WHITE;
    
    // cube4-7
    cube_data[10][0][0][0] = WHITE;
    cube_data[10][0][1][0] = BLACK;
    cube_data[10][0][1][1] = WHITE;
    cube_data[10][1][1][1] = BLACK;
    
    for (int cube_type = 0; cube_type < cube_num; cube_type++) {
        int fit_size = fit_cube_size[cube_type];
        block_type array[cube_size][cube_size][cube_size];
        memcpy(array, cube_data[cube_type], cube_size * cube_size * cube_size * sizeof(block_type));
        
        block_type temp[cube_size][cube_size][cube_size];
        for (int x_rotation = 0; x_rotation < 4; x_rotation++) {
            for (int y_rotation = 0; y_rotation < 4; y_rotation++) {
                for (int z_rotation = 0; z_rotation < 4; z_rotation++) {
                    memcpy(rotated_cube_data[cube_type][z_rotation * 16 + y_rotation * 4 + x_rotation], array, cube_size * cube_size * cube_size * sizeof(block_type));
                    
                    memcpy(temp, array, cube_size * cube_size * cube_size * sizeof(block_type));
                    for (int x = 0; x < fit_size; x++) {
                        for (int y = 0; y < fit_size; y++) {
                            for (int z = 0; z < fit_size; z++) {
                                array[z][y][x] = temp[z][fit_size - 1 - x][y];
                            }
                        }
                    }
                }
                memcpy(temp, array, cube_size * cube_size * cube_size * sizeof(block_type));
                for (int x = 0; x < fit_size; x++) {
                    for (int y = 0; y < fit_size; y++) {
                        for (int z = 0; z < fit_size; z++) {
                            array[z][y][x] = temp[fit_size - 1 - x][y][z];
                        }
                    }
                }
            }
            memcpy(temp, array, cube_size * cube_size * cube_size * sizeof(block_type));
            for (int x = 0; x < fit_size; x++) {
                for (int y = 0; y < fit_size; y++) {
                    for (int z = 0; z < fit_size; z++) {
                        array[z][y][x] = temp[fit_size - 1 - y][z][x];
                    }
                }
            }
        }
    }
}

void* cube_getArray(cube a) {
    a.x_rotation %= 4;
    if (a.x_rotation < 0) a.x_rotation += 4;
    a.y_rotation %= 4;
    if (a.y_rotation < 0) a.y_rotation += 4;
    a.z_rotation %= 4;
    if (a.z_rotation < 0) a.z_rotation += 4;
    
    static block_type array[cube_size][cube_size][cube_size];
    for (int z = 0; z < cube_size; z++) {
        for (int y = 0; y < cube_size; y++) {
            for (int x = 0; x < cube_size; x++) {
                block_type data = rotated_cube_data[a.cube_type][a.z_rotation * 16 + a.y_rotation * 4 + a.x_rotation][z][y][x];
                if (a.color_inversion == false) {
                    array[z][y][x] = data;
                } else {
                    if (data == WHITE) {
                        array[z][y][x] = BLACK;
                    } else if (data == BLACK) {
                        array[z][y][x] = WHITE;
                    } else {
                        array[z][y][x] = EMPTY;
                    }
                }
            }
        }
    }
    
    return (void*)array;
}

bool cube_canPut(cube a, int z0, int y0, int x0) {
    block_type (*array)[cube_size][cube_size] = cube_getArray(a);
    int fit_size = fit_cube_size[a.cube_type];

    // 있는 블록과 곂치는지, 경계를 넘어가는지 확인
    for (int dz = 0; dz < fit_size; dz++) {
        for (int dy = 0; dy < fit_size; dy++) {
            for (int dx = 0; dx < fit_size; dx++) {
                if (array[dz][dy][dx] == EMPTY) continue;
                int z = z0 + dz, y = y0 + dy, x = x0 + dx;
                
                // 경계를 넘어가는지
                if (z < 0 || z >= board_width) return false;
                if (y < 0 || y >= board_height) return false;
                if (x < 0 || x >= max_height) return false;
                
                // 있는 블록과 곂치는지
                if (board[z][y][x] != EMPTY) return false;
            }
        }
    }
    
    // 공중에 떠있는지 확인
    bool flag = false;
    for (int dy = 0; dy < fit_size; dy++) {
        for (int dx = 0; dx < fit_size; dx++) {
            for (int dz = 0; dz < fit_size; dz++) {
                if (array[dz][dy][dx] == EMPTY) continue;
                int z = z0 + dz, y = y0 + dy, x = x0 + dx;
                
                flag = flag || (board[z - 1][y][x] != EMPTY);
                break; // 가장 낮은 곳만 확인하고 나감
            }
            if (flag == true) break;
        }
        if (flag == true) break;
    }
    if (flag == false) return false;
    
    // 색이 곂치는지 확인
    for (int dz = 0; dz < fit_size; dz++) {
        for (int dy = 0; dy < fit_size; dy++) {
            for (int dx = 0; dx < fit_size; dx++) {
                if (array[dz][dy][dx] == EMPTY) continue;
                int z = z0 + dz, y = y0 + dy, x = x0 + dx;
                block_type color = array[dz][dy][dx];
                
                for (int i = 0; i < 6; i++) {
                    int next_z = z + delta_z[i], next_y = y + delta_y[i], next_x = x + delta_x[i];
                    
                    // 경계를 넘어가는지
                    if (next_z < 0 || next_z >= board_width) continue;
                    if (next_y < 0 || next_y >= board_height) continue;
                    if (next_x < 0 || next_x >= max_height) continue;
                    
                    if (board[next_z][next_y][next_x] == color) return false;
                }
            }
        }
    }
    
    return true;
}

void cube_put(cube a, int z0, int y0, int x0) {
    block_type (*array)[cube_size][cube_size] = cube_getArray(a);
    int fit_size = fit_cube_size[a.cube_type];
    
    for (int dz = 0; dz < fit_size; dz++) {
        for (int dy = 0; dy < fit_size; dy++) {
            for (int dx = 0; dx < fit_size; dx++) {
                if (array[dz][dy][dx] == EMPTY) continue;
                int z = z0 + dz, y = y0 + dy, x = x0 + dx;
                block_type color = array[dz][dy][dx];
                
                if (z < 0 || z >= board_width) continue;
                if (y < 0 || y >= board_height) continue;
                if (x < 0 || x >= max_height) continue;
                
                board[z][y][x] = color;
            }
        }
    }
}

void cube_draw(cube a, double z0, double y0, double x0) {
    block_type (*array)[cube_size][cube_size] = cube_getArray(a);
    
    bool abled = cube_canPut(a, z0, y0, x0);
    
    for (int z = 0; z < cube_size; z++) {
        for (int y = 0; y < cube_size; y++) {
            for (int x = 0; x < cube_size; x++) {
                drawBlock(z0 + z, y0 + y, x0 + x, array[z][y][x], (abled ? 0.1 : 0.3));
            }
        }
    }
}
