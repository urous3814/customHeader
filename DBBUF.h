//double buffering

#ifndef DBBUF_H
#define DBBUF_H

#define BUF_SIZE 8192 // 버퍼 크기

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


extern int hidden_index; // Hidden 화면 번호 0 or 1
HANDLE scr_handle[2]; // 화면 버퍼 변수
extern long long frame_count = 0;

void removeCursor(void) { // 커서를 안보이게 한다

    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void showCursor(void){ // 커서를 보이게 한다

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible=1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void scr_init()
{
    int i;
    CONSOLE_CURSOR_INFO cci;

    cci.dwSize = 1;
    cci.bVisible = FALSE;
    // 화면 버퍼 2개를 만든다.
    for (i = 0; i < 2; i++) {
        scr_handle[i] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        // 커서를 숨긴다.
        SetConsoleCursorInfo(scr_handle[i], &cci);
    }
    // 0번 화면이 default
    SetConsoleActiveScreenBuffer(scr_handle[0]);
    hidden_index = 1; // 1번 화면이 Hidden Screen
}

void ChangeScreenSize(HANDLE hnd, COORD NewSize)
{
    //HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT DisplayArea = { 0, 0, 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    GetConsoleScreenBufferInfo(hnd, &SBInfo);
    DisplayArea.Bottom = NewSize.Y;
    DisplayArea.Right = NewSize.X;
    SetConsoleWindowInfo(hnd, 1, &DisplayArea);
}

void ChangeBuffSize(HANDLE hnd, COORD NewSize)
{
    SetConsoleScreenBufferSize(hnd, NewSize);
}

void scr_switch()
{
    // hidden 을 active 로 변경한다.
    SetConsoleActiveScreenBuffer(scr_handle[hidden_index]);
    // active를 hidden으로 변경한다.
    hidden_index = !hidden_index; // 0 <-> 1 toggle
}

void scr_clear(int Width, int Height)
{
    COORD Coor = { 0, 0 };
    DWORD dw;
    FillConsoleOutputCharacter(scr_handle[hidden_index], ' ', Width * Height, Coor, &dw);
}

void scr_release()
{
    CloseHandle(scr_handle[0]);
    CloseHandle(scr_handle[1]);
}

void textcolor(int fg_color, int bg_color)
{
    SetConsoleTextAttribute(scr_handle[hidden_index], fg_color | bg_color << 4);
}

// 화면 지우기고 원하는 배경색으로 설정한다.
void cls(int text_color, int bg_color)
{
    char cmd[100];
    system("cls");
    // 화면 크기 강제로 조정한다.
    sprintf(cmd, "COLOR %x%x", bg_color, text_color);
    system(cmd);
}

void gotoxy(int x, int y)
{
    DWORD dw;
    COORD CursorPosition = { x, y };
    // hidden screen에 gotoxy
    SetConsoleCursorPosition(scr_handle[hidden_index], CursorPosition);
}
 // 가변인자 처리를 위한 헤더 파일 추가

void printscr(char* format, ...) {
    va_list args;
    char buffer[BUF_SIZE];
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    DWORD dw;
    WriteFile(scr_handle[hidden_index], buffer, strlen(buffer), &dw, NULL);
}

#endif // DBBUF_H