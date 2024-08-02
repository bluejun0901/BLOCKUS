//
//  graphics.h
//  BLOCKUS
//
//  Created by 김명준 on 8/2/24.
//

#ifndef graphics_h
#define graphics_h

#include "common.h"

/* 단위 정육면체를 그리는 함수 */
/* z, y, x: 보드 좌표계에서 정육면체의 왼쪽 아래 앞 꼭짓점의 위치 */
/* type: 정육면체의 종류 */
/* delta: 0.0 ~ 0.5의 실수값을 가지며, 블록의 색이 회색에 가까울 정도를 나타냄 */
void drawBlock(double z, double y, double x, block_type type, double delta);

#endif /* graphics_h */
