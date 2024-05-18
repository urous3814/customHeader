# 더블 버퍼링 라이브러리 - README

## 개요

이 라이브러리는 Windows 콘솔 애플리케이션에서 더블 버퍼링을 쉽게 구현할 수 있도록 하는 함수들을 제공합니다. 더블 버퍼링은 두 개의 화면 버퍼를 유지하고 전환함으로써 깜박임을 줄이는 데 도움을 줍니다.

## 헤더 파일: `dbbuf.h`

### 정의 및 포함 파일

-   **BUF_SIZE:** `printscr` 함수에서 사용되는 버퍼의 크기 (8192 바이트).
-   **hidden_index:** 숨겨진 화면 버퍼의 인덱스 (0 또는 1).
-   **scr_handle:** 두 개의 화면 버퍼 핸들을 저장하는 배열.
-   **frame_count:** 렌더링된 프레임의 수를 세는 카운터.

### 함수들

#### 커서 가시성

-   **removeCursor()**: 콘솔 커서를 숨깁니다.

```c
void removeCursor(void);
```

-   **showCursor()**: 콘솔 커서를 보이게 합니다.

```c
void showCursor(void);
```

#### 화면 버퍼 초기화

-   **scr_init()**: 화면 버퍼를 초기화하고 더블 버퍼링 메커니즘을 설정합니다.

```c
void scr_init();
```

#### 화면 버퍼 크기 및 창 크기 관리

-   **ChangeScreenSize(HANDLE hnd, COORD NewSize)**: 콘솔 창의 크기를 변경합니다.

```c
void ChangeScreenSize(HANDLE hnd, COORD NewSize);
```

-   **ChangeBuffSize(HANDLE hnd, COORD NewSize)**: 콘솔 화면 버퍼의 크기를 변경합니다.

```c
void ChangeBuffSize(HANDLE hnd, COORD NewSize);
```

#### 화면 버퍼 전환 및 초기화

-   **scr_switch()**: 활성 화면 버퍼를 숨겨진 버퍼로 전환합니다.

```c
void scr_switch();
```

-   **scr_clear(int Width, int Height)**: 숨겨진 화면 버퍼를 초기화합니다.

```c
void scr_clear(int Width, int Height);
```

#### 화면 버퍼 해제

-   **scr_release()**: 화면 버퍼의 핸들을 해제합니다.

```c
void scr_release();
```

#### 텍스트 및 화면 조작

-   **textcolor(int fg_color, int bg_color)**: 숨겨진 화면 버퍼의 텍스트와 배경 색상을 설정합니다.

```c
void textcolor(int fg_color, int bg_color);
```

-   **cls(int text_color, int bg_color)**: 화면을 지우고 텍스트와 배경 색상을 설정합니다.

```c
void cls(int text_color, int bg_color);
```

-   **gotoxy(int x, int y)**: 숨겨진 화면 버퍼에서 커서를 지정된 위치로 이동시킵니다.

```c
void gotoxy(int x, int y);
```

#### 화면 출력

-   **printscr(char\* format, ...)**: 가변 인자를 사용하여 숨겨진 화면 버퍼에 형식화된 텍스트를 출력합니다.

```c
void printscr(char* format, ...);
```

## 사용 예제

다음은 더블 버퍼링 메커니즘의 초기화, 사용 및 정리를 보여주는 기본 예제입니다:

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

이 예제는 더블 버퍼링 시스템을 초기화하고, 커서를 숨기며, 텍스트와 배경 색상을 설정하고, 숨겨진 버퍼를 초기화한 후, 메시지를 출력하고, 버퍼를 전환하여 숨겨진 버퍼를 표시한 다음, 리소스를 해제하기 전에 커서를 다시 표시합니다.

## 결론

이 더블 버퍼링 라이브러리는 콘솔 애플리케이션에서 깜박임을 줄이고 시각적 성능을 향상시키기 위해 더블 버퍼링을 관리하고 활용하는 데 필요한 기본적인 함수들을 제공합니다. 버퍼를 초기화하고 적절하게 해제하여 리소스 누수를 방지하십시오.
