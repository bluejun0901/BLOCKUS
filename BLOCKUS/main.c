//
//  main.c
//  BLOCKUS
//
//  Created by 김명준 on 7/31/24.
//

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include <stdio.h>

// 화면 설정
// x축: 왼쪽 방향
// y축: 위쪽 방향
// z축: 화면으로 들어가는 방향
const int fps = 60;
int screen_width = 1000; // 화면 가로 크기(px)
int screen_height = 600; // 화면 세로 크기(px)

// 블록 종류 정의
typedef enum _block_type {
    EMPTY = 0,
    WHITE = 1,
    BLACK = 2
} block_type;

// 게임판 설정
// x축: 오른쪽 방향
// y축: 화면으로 들어가는 방향
// z축: 위쪽 방향
#define board_width 5  // 게임판 가로 크기
#define board_height 8 // 게임판 세로 크기
#define max_height 100 // 게임판에 놓을 수 있는 블록의 최대 높이
block_type board[max_height][board_height][board_width]; // board[z좌표][y좌표][x좌표]로 접근: 디버깅에 편리함

void myReshape(int width, int height) {
    // 투영 행렬 설정
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (double)width / (double)height, 0.1, 100.0);
    
    screen_width = width;
    screen_height = height;
    
    glutPostRedisplay();
}

void drawCube(double z, double y, double x, block_type type) {
    glPushMatrix();
    glTranslated(-x, z, y);
    
    if (type == WHITE) {
        glColor3d(1.0, 1.0, 1.0);
    } else if (type == BLACK) {
        glColor3d(0.0, 0.0, 0.0);
    } else if (type == EMPTY) {
        glPopMatrix();
        return;
    }
    
    glutSolidCube(1.0);
    glPopMatrix();
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(-8.0, 5.0, -8.0,                             // 카메라 위치
              -board_width / 2.0, 0.0, board_height / 2.0, // 바라볼 좌표
              0.0, 1.0, 0.0);                              // 위쪽을 가리키는 벡터
    
    for (int z = 0; z < max_height; z++) {
        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                drawCube(z, y, x, board[z][y][x]);
            }
        }
    }
    
    glutSwapBuffers();
}

int main(int argc, char * argv[]) {
    // 보드 초기화
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
    
    // 윈도우 생성과 초기화
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("BLOCKUS");
    glutReshapeWindow(screen_width, screen_height);
    
    glEnable(GL_DEPTH_TEST);
    
    // 콜백 설정
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    
    glutMainLoop();
    
    return 0;
}
