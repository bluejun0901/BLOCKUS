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

int cube_z;
int cube_y;
int cube_x;

int trun_count;

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
