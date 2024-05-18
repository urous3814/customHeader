# BSP.h README

## 개요

`BSP.h` 헤더 파일은 이진 공간 분할 (Binary Space Partitioning, BSP) 트리를 생성하고 조작하기 위한 구조체와 함수들을 제공합니다. 이 트리는 컴퓨터 그래픽스, 게임 개발, 절차적 콘텐츠 생성에서 공간을 서브 스페이스로 나누기 위해 사용됩니다.

## 구조체

### spaceType

`spaceType` 구조체는 직사각형 공간을 나타내며, 다음과 같은 속성을 가집니다:

-   `int x`: 공간의 왼쪽 위 모서리의 x좌표.
-   `int y`: 공간의 왼쪽 위 모서리의 y좌표.
-   `int width`: 공간의 너비.
-   `int height`: 공간의 높이.

### SpaceTree

`SpaceTree` 구조체는 BSP 트리의 노드를 나타내며, 다음을 포함합니다:

-   `spaceType space`: 이 노드가 나타내는 공간.
-   `SpaceTree* left`: 왼쪽 자식 노드에 대한 포인터.
-   `SpaceTree* right`: 오른쪽 자식 노드에 대한 포인터.

## 전역 변수

-   `int eMAX_NODE`: BSP 트리의 최대 노드 수.
-   `int eSeed`: 랜덤 숫자 생성을 위한 시드.
-   `int devideL`: 공간 분할의 최소값.
-   `int devideR`: 공간 분할의 최대값.

## 함수

SpaceTree\* initBSP(int seed, int maxNode, int width, int height, int devideL, int devideR)
루트 노드로 BSP 트리를 초기화하고 후속 작업을 위한 전역 변수를 설정합니다.

매개변수:
int seed: 랜덤 숫자 생성을 위한 시드.
int maxNode: 트리의 최대 노드 수.
int width: 초기 공간의 너비.
int height: 초기 공간의 높이.
int devideL: 공간 분할의 최소값.
int devideR: 공간 분할의 최대값.
반환값: 초기화된 BSP 트리의 루트 노드에 대한 포인터.

### SpaceTree\* initBSP(int seed, int maxNode, int width, int height, int devideL, int devideR)

루트 노드로 BSP 트리를 초기화하고 후속 작업을 위한 전역 변수를 설정합니다.

-   **매개변수**:
    -   `int seed`: 랜덤 숫자 생성을 위한 시드.
    -   `int maxNode`: 트리의 최대 노드 수.
    -   `int width`: 초기 공간의 너비.
    -   `int height`: 초기 공간의 높이.
    -   `int devideL`: 공간 분할의 최소값.
    -   `int devideR`: 공간 분할의 최대값.
-   **반환값**: 초기화된 BSP 트리의 루트 노드에 대한 포인터.

### SpaceTree* divideSpace(SpaceTree* node, int n)

최대 노드 수에 도달할 때까지 주어진 공간을 작은 서브 스페이스로 재귀적으로 나눕니다.

-   **매개변수**:
    -   `SpaceTree* node`: 분할할 현재 노드에 대한 포인터.
    -   `int n`: 재귀의 현재 깊이, 0부터 시작.
-   **반환값**: 분할 후의 루트 노드에 대한 포인터.

## 사용 예시

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

-   `divideSpace` 함수는 `[devideL, devideR]` 범위 내의 랜덤 값을 10으로 나눈 값을 사용하여 공간을 나눕니다.
-   `divideSpace` 함수의 초기 호출은 항상 `n = 0`으로 시작해야 합니다.
-   사용 후 할당된 메모리를 해제하여 메모리 누수를 방지하십시오.
