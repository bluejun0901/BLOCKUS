//
//  main.c
//  BLOCKUS
//
//  Created by 김명준 on 7/31/24.
//

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "common.h"
#include "board.h"
#include "cube.h"
#include "graphics.h"
#include "camera.h"
#include "game_logic.h"

// 화면 설정
// x축: 왼쪽 방향
// y축: 위쪽 방향
// z축: 화면으로 들어가는 방향
const int fps = 60;
int screen_width = 1000; // 화면 가로 크기(px)
int screen_height = 600; // 화면 세로 크기(px)

/* 윈도우 크기가 변했을 때 실행될 함수 */
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

int tv1, tv2, tv3; // test code

/* 렌더링할 때 사용할 함수 */
void myDisplay(void) {
    glClearColor(0.5, 0.5, 0.5, 1.0); // 배경색 지정
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    game_logic_draw();
    
    // 카메라 설정
    glLoadIdentity();
    gluLookAt(-camera_x, camera_z, camera_y,               // 카메라 위치
              -board_width / 2.0, 0.0, board_height / 2.0, // 바라볼 좌표: 보드의 가운데를 바라보도록 설정
              0.0, 1.0, 0.0);                              // 위쪽을 가리키는 벡터
    
    // 게임판 그리기
    drawBoard();
    
    selected_cube_draw();
    
    glutSwapBuffers();
}

/* 키보드 입력을 받는 함수 */
void myKeyboard(unsigned char key, int x, int y) {
    game_logic_step(key);
    
    // test code
    if (key == 'a' || key == 'A') {
        tv1++;
    } else if (key == 's' || key == 'S') {
        tv2++;
    } else if (key == 'd' || key == 'D') {
        tv3++;
    }
    
    glutPostRedisplay();
}

/* 특수키 입력을 받는 함수 */
void mySpecialKey(int key, int x, int y) {
    // 방향키로 카메라 위치 조절
    if (key == GLUT_KEY_UP) {
        camera_move(INWARD, 1.0);
    } else if (key == GLUT_KEY_DOWN) {
        camera_move(OUTWARD, 1.0);
    } else if (key == GLUT_KEY_LEFT) {
        camera_move(LEFT, 1.0);
    } else if (key == GLUT_KEY_RIGHT) {
        camera_move(RIGHT, 1.0);
    }
    
    glutPostRedisplay();
}

int main(int argc, char * argv[]) {
    // 보드 초기화
    initBoard();
    
    // 큐브 데이터 초기화
    initCubeData();
    
    // 플레이어 초기화
    initPlayers();
    
    // 윈도우 생성과 초기화
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("BLOCKUS");
    glutReshapeWindow(screen_width, screen_height);
    
    glEnable(GL_DEPTH_TEST);
    
    // 콜백 설정
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKey);
    
    glutMainLoop();
    
    return 0;
}
