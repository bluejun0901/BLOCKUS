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

// 화면 설정
// x축: 왼쪽 방향
// y축: 위쪽 방향
// z축: 화면으로 들어가는 방향
const int fps = 60;
int screen_width = 1000; // 화면 가로 크기(px)
int screen_height = 600; // 화면 세로 크기(px)

// 카메라 설정
// TODO: 카메라 방향 등 정의
double camera_x = 0.0;
double camera_y = 0.0;
double camera_z = 5.0;

int test_variable = 0; // test code
int tv2 = 0; // test code
int tv3 = 0; // test code
cube t = { 8, 0, 0, 0, false }; // test code

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

/* 배경을 렌더링할 때 사용할 함수 */
void myDisplay(void) {
    glClearColor(0.5, 0.5, 0.5, 1.0); // 배경색 지정
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // 카메라 설정
    gluLookAt(-camera_x, camera_z, camera_y,               // 카메라 위치
              -board_width / 2.0, 0.0, board_height / 2.0, // 바라볼 좌표: 보드의 가운데를 바라보도록 설정
              0.0, 1.0, 0.0);                              // 위쪽을 가리키는 벡터
    
    // 게임판 그리기
    drawBoard();
    
    // test code
    cube_draw(t, test_variable, tv2, tv3);
    // test code
    
    glutSwapBuffers();
}

/* 키보드 입력을 받는 함수 */
void myKeyboard(unsigned char key, int x, int y) {
    // wasd키로 카메라 위치 조절
    // 임시 코드로 자연스럽이 않음
    // 한글 키로 바뀌어 있으면 작동하지 않음
    // TODO: 카메라가 자연스럽게 움직이도록 코드 변경
    if (key == 'w' || key == 'W') {
        camera_y += 1.0;
    } else if (key == 's' || key == 'S') {
        camera_y -= 1.0;
    } else if (key == 'a' || key == 'A') {
        camera_x -= 1.0;
    } else if (key == 'd' || key == 'D') {
        camera_x += 1.0;
    }
    // test code
    else if (key == 'r' || key == 'R') {
        test_variable++;
    } else if (key == 't' || key == 'T') {
        tv2++;
    } else if (key == 'y' || key == 'Y') {
        tv3++;
    } else if (key == ' ') {
        cube_put(t, test_variable, tv2, tv3);
    }
    
    glutPostRedisplay();
}

/* 특수키 입력을 받는 함수 */
void mySpecialKey(int key, int x, int y) {
    // 방향키로 카메라 위치 조절
    // 임시 코드로 자연스럽이 않음
    // TODO: 카메라가 자연스럽게 움직이도록 코드 변경
    if (key == GLUT_KEY_UP) {
        camera_y += 1.0;
    } else if (key == GLUT_KEY_DOWN) {
        camera_y -= 1.0;
    } else if (key == GLUT_KEY_LEFT) {
        camera_x -= 1.0;
    } else if (key == GLUT_KEY_RIGHT) {
        camera_x += 1.0;
    }
}

int main(int argc, char * argv[]) {
    // 보드 초기화
    initBoard();
    
    // 큐브 데이터 초기화
    initCubeData();
    
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
    
    glutMainLoop();
    
    return 0;
}
