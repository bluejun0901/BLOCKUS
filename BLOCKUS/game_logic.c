//
//  game_logic.c
//  BLOCKUS
//
//  Created by 김명준 on 8/3/24.
//

#include "game_logic.h"

#include <stdlib.h>
#include <time.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include "graphics.h"

cube player_cubes[player_num][player_cube_num];

int cube_z = 1.0;
int cube_y = 1.0;
int cube_x = 1.0;

int turn_count;

bool selected = false;
cube selected_cube;

void initPlayers(void) {
    srandom((unsigned int)time(NULL));
    
    for (int player = 0; player < player_num; player++) {
        for (int i = 0; i < player_cube_num; i++) {
            cube t = { random() % cube_num, 0, 0, 0, false };
            player_cubes[player][i] = t;
        }
    }
}

void game_logic_step(unsigned char key) {
    if (turn_count == 0) {
        if (key - '0' >= 1 && key - '0' <= player_cube_num) {
            selected = true;
            selected_cube = player_cubes[0][key - '0'];
        }
        
        if (key == 'a' || key == 'A') {
            cube_x++;
        } else if (key == 's' || key == 'S') {
            cube_y++;
        } else if (key == 'd' || key == 'D') {
            cube_z++;
        } else if (key == 'q' || key == 'Q') {
            cube_x--;
        } else if (key == 'w' || key == 'W') {
            cube_y--;
        } else if (key == 'e' || key == 'e') {
            cube_z--;
        }
        
        if (key == ' ') {
            if (cube_canPut(selected_cube, cube_z, cube_y, cube_x) == true) {
                cube_put(selected_cube, cube_z, cube_y, cube_x);
                selected = false;
                turn_count++;
            }
        }
    } else if (turn_count == 1) {
        if (key - '0' >= 1 && key - '0' <= player_cube_num) {
            selected = true;
            selected_cube = player_cubes[1][key - '0'];
        }
        
        if (key == 'a' || key == 'A') {
            cube_x++;
        } else if (key == 's' || key == 'S') {
            cube_y++;
        } else if (key == 'd' || key == 'D') {
            cube_z++;
        } else if (key == 'q' || key == 'Q') {
            cube_x--;
        } else if (key == 'w' || key == 'W') {
            cube_y--;
        } else if (key == 'e' || key == 'e') {
            cube_z--;
        }
        
        if (key == ' ') {
            if (cube_canPut(selected_cube, cube_z, cube_y, cube_x) == true) {
                cube_put(selected_cube, cube_z, cube_y, cube_x);
                selected = false;
                turn_count++;
            }
        }
    }
}

void game_logic_draw(void) {
    glPushMatrix();
    
    for (int player = 0; player < player_num; player++) {
        for (int i = 0; i < player_cube_num; i++) {
            cube t = player_cubes[player][i];
            
            glLoadIdentity();
            glTranslated(0.7 - 1.4 * player, -0.4 + 0.2 * i, 0.0);
            gluLookAt(1.0, 1.0, -1.0,
                      0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0);
            
            cube_draw(t, 0.0, 0.0, 0.0, 0.05, true);
        }
    }
    
    glPopMatrix();
}

void selected_cube_draw(void) {
    if (selected == true) {
        cube_draw(selected_cube, cube_z, cube_y, cube_x, 1.0, cube_canPut(selected_cube, cube_z, cube_y, cube_x));
    }
}
