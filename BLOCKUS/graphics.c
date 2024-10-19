//
//  graphics.c
//  BLOCKUS
//
//  Created by 김명준 on 8/2/24.
//

#include "graphics.h"

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include "common.h"

void drawBlock(double z, double y, double x, block_type type, double size, double delta) {
    glPushMatrix();
    glTranslated(-x, z, y);
    
    if (type == EMPTY) {
        glPopMatrix();
        return;
    }
    
    if (type == WHITE) {
        glColor3d(1.0 - delta, 1.0 - delta, 1.0 - delta);
    } else if (type == BLACK) {
        glColor3d(0.2 + delta, 0.2 + delta, 0.2 + delta);
    }
    
    glutSolidCube(size);
    glPopMatrix();
}
