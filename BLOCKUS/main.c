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

// 큐브 모양 정의
// cube_data[_][z좌표][y좌표][x좌표]로 접근
// rotated_cube_data[_][z축 회전 * 16 + y축 회전 * 4 + x축 회전][z좌표][y좌표][x좌표]로 접근
#define cube_size 4 // 하나의 큐브를 저장하는 데 사용되는 공간
#define cube_num 11 // 큐브 종류의 수
const int fit_cube_size[cube_num] = { 2, 3, 2, 4, 2, 3, 3, 3, 2, 2, 2 }; // 큐브가 차지하는 실제 공간
const block_type cube_data[cube_num][cube_size][cube_size][cube_size] = {
    { // cube2-0
        {
            { 1, 2, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }, { // cube3-0
        {
            { 1, 2, 1, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }, { // cube 3-1
        {
            { 1, 2, 0, 0 },
            { 2, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }, { // cube 4-0
        {
            { 1, 2, 1, 2 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }, { // cube 4-1
        {
            { 2, 1, 0, 0 },
            { 1, 2, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }, { // cube 4-2
        {
            { 2, 0, 0, 0 },
            { 1, 2, 1, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }, { // cube 4-3
        {
            { 2, 0, 0, 0 },
            { 1, 2, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }, { // cube 4-4
        {
            { 2, 0, 0, 0 },
            { 1, 2, 0, 0 },
            { 2, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }, { // cube 4-5
        {
            { 1, 0, 0, 0 },
            { 2, 1, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 2, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }, { // cube 4-6
        {
            { 1, 0, 0, 0 },
            { 2, 1, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 1, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }, { // cube 4-7
        {
            { 1, 0, 0, 0 },
            { 2, 1, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 2, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }, {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }
};
block_type rotated_cube_data[cube_num][4 * 4 * 4][cube_size][cube_size][cube_size]; // main함수에서 전처리

// 큐브 정의
typedef struct _cube {
    int cube_type;        // cube_data의 인덱스를 가리킴
    int x_rotation;       // x축을 기준으로 회전한 횟수
    int y_rotation;       // y축을 기준으로 회전한 횟수
    int z_rotation;       // z축을 기준으로 회전한 횟수
    bool color_inversion; // 색 반전 여부
} cube;

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

void cube_draw(cube a, double z0, double y0, double x0) {
    block_type (*array)[cube_size][cube_size] = cube_getArray(a);
    
    for (int z = 0; z < cube_size; z++) {
        for (int y = 0; y < cube_size; y++) {
            for (int x = 0; x < cube_size; x++) {
                drawCube(z0 + z, y0 + y, x0 + x, array[z][y][x]);
            }
        }
    }
}

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

int test_variable = 0; // test code

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
    
    // test code
    cube t = { 8, 0, test_variable, 0, false };
    cube_draw(t, 3, 3, 3);
    // test code
    
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
    // test code
    else if (key == 'q' || key == 'Q') {
        test_variable++;
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
    
    // 회전된 큐브 데이터 초기화
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
