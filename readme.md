## 개요

이 프로젝트는 콘솔 애플리케이션에서 더블 버퍼링과 이진 공간 분할(BSP) 트리를 구현하기 위해 도움이 될 수 있는 헤더파일을 제공한다.   
작성자: **김지훈(urous3814)**

-   **DBBUF.h:** 더블 버퍼링을 통한 깜박임 없는 콘솔 출력 관리.
-   **BSP.h:** 이진 공간 분할 트리 생성을 위한 구조체와 함수.

각 헤더 파일과 관련된 자세한 정보는 해당 폴더의 README 파일에서 확인할 수 있습니다.

### DBBUF.h

`DBBUF.h` 헤더 파일은 Windows 콘솔 애플리케이션에서 더블 버퍼링을 구현하는 데 필요한 함수들을 제공합니다. 더블 버퍼링은 두 개의 화면 버퍼를 유지하고 전환함으로써 콘솔 애플리케이션의 화면 깜박임을 줄이는 데 도움을 줍니다.

#### 주요 기능:

-   화면 버퍼 초기화 및 전환
-   커서 숨기기 및 표시
-   화면 버퍼 크기 조정
-   텍스트와 배경 색상 설정
-   콘솔 출력 및 화면 초기화

#### 링크:

[DBBUF.h README](DBBUF/readme.md)

### BSP.h

`BSP.h` 헤더 파일은 이진 공간 분할(BSP) 트리를 생성하고 조작하기 위한 구조체와 함수들을 제공합니다. BSP 트리는 컴퓨터 그래픽스, 게임 개발, 절차적 콘텐츠 생성에서 공간을 서브 스페이스로 나누는 데 사용됩니다.

#### 주요 기능:

-   BSP 트리 초기화
-   공간 분할을 위한 구조체 정의
-   재귀적으로 공간을 분할하여 트리 생성
-   노드 관리 및 랜덤 분할 설정

#### 링크:

[BSP.h README](BSP/readme.md)

## 사용 예시

### DBBUF.h 사용 예시

```c
#include "dbbuf.h"

int main() {
    // 화면 버퍼 초기화
    scr_init();

    // 커서 숨기기
    removeCursor();

    // 초기 텍스트 및 배경 색상 설정
    textcolor(FOREGROUND_RED, BACKGROUND_BLUE);

    // 설정된 색상으로 화면 지우기
    scr_clear(80, 25);

    // 숨겨진 버퍼에 출력
    gotoxy(10, 10);
    printscr("안녕하세요, 더블 버퍼링!");

    // 버퍼를 전환하여 숨겨진 버퍼를 표시
    scr_switch();

    // 기타 작업 수행 후, 버퍼 해제
    scr_release();

    // 종료 전에 커서를 다시 표시
    showCursor();

    return 0;
}
```

### BSP.h 사용 예시

```c
#include "BSP.h"

int main() {
    int seed = 42;
    int maxNode = 10;
    int width = 100;
    int height = 100;
    int devideL = 30;
    int devideR = 70;

    SpaceTree* root = initBSP(seed, maxNode, width, height, devideL, devideR);
    divideSpace(root, 0);

    // BSP 트리에 대한 추가 작업...

    return 0;
}
```

## 참고 사항

-   각 헤더 파일에 포함된 함수를 적절하게 사용하여 메모리 누수를 방지하십시오.
-   더블 버퍼링을 구현할 때는 초기화 및 해제 과정을 정확히 따라야 합니다.
-   BSP 트리의 분할 범위와 재귀 깊이에 주의하여 트리 구조를 관리하십시오.

자세한 내용은 각 헤더 파일의 README를 참고하세요.
