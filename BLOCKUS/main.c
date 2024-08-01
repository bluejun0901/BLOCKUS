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
// 게임판 좌표로 (x, y, z) = 화면 좌표로 (-x, z, y)
#define board_width 5  // 게임판 가로 크기
#define board_height 8 // 게임판 세로 크기
#define max_height 100 // 게임판에 놓을 수 있는 블록의 최대 높이
block_type board[max_height][board_height][board_width]; // board[z좌표][y좌표][x좌표]로 접근: 디버깅에 편리함

// 카메라 설정
// TODO: 카메라 방향 등 정의
double camera_x = 0.0;
double camera_y = 0.0;
double camera_z = 5.0;

// 큐브 정의
// cube__[큐브의 회전 번호][z좌표][y좌표][x좌표]로 접근
// 아래쪽 단면(cube__[_][z + 1])이 위쪽 단면(cube__[_][z]) 위로 곂쳐지는 형태
// ex) 아래와 같이 정의된 형태를 앞에서 보면
//     7 8
//     3 4로 보임
//     {
//         { 1, 2 },
//         { 3, 4 }
//     }, {
//         { 5, 6 },
//         { 7, 8 }
//     }
//const block_type cube20[3][2][2][2] = {
//    {
//        {
//            { 1, 2 },
//            { 0, 0 }
//        }, {
//            { 0, 0 },
//            { 0, 0 }
//        }
//    }, {
//        {
//            { 1, 0 },
//            { 2, 0 }
//        }, {
//            { 0, 0 },
//            { 0, 0 }
//        }
//    }, {
//        {
//            { 1, 0 },
//            { 0, 0 }
//        }, {
//            { 2, 0 },
//            { 0, 0 }
//        }
//    }
//};

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
    glClearColor(0.5, 0.5, 0.5, 1.0); // 배경색 지정
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // 카메라 설정
    gluLookAt(-camera_x, camera_z, camera_y,               // 카메라 위치
              -board_width / 2.0, 0.0, board_height / 2.0, // 바라볼 좌표: 보드의 가운데를 바라보도록 설정
              0.0, 1.0, 0.0);                              // 위쪽을 가리키는 벡터
    
    // 게임판 그리기
    for (int z = 0; z < max_height; z++) {
        for (int y = 0; y < board_height; y++) {
            for (int x = 0; x < board_width; x++) {
                drawCube(z, y, x, board[z][y][x]);
            }
        }
    }
    
    glutSwapBuffers();
}

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
    glutPostRedisplay();
}

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
    glutKeyboardFunc(myKeyboard);
    
    glutMainLoop();
    
    return 0;
}
