#include "display.h"

inline void DISPLAY::ReadDataFileToScreenBuff(const char* filepath, int position_x, int position_y)
{
	ifstream file;
	file.open(filepath);
	char* tmp_line = new char[SCREEN_LENGTH+1];
	while (!file.eof())
	{
		strcpy(tmp_line, SCREEN_BUFFER[position_y]);
		file.getline(&SCREEN_BUFFER[position_y][position_x], SCREEN_LENGTH);

		for (int i = 0; i < SCREEN_LENGTH; ++i)//替換掉getline過程中添加的\0
			if (SCREEN_BUFFER[position_y][i] == '\0')
				SCREEN_BUFFER[position_y][i] = tmp_line[i];

		position_y++;//下一行
	}
	file.close();
	delete[] tmp_line;//釋放暫時申請的内存
}

void DISPLAY::PrintLine()
{
	for(int i = 0;i<SCREEN_LENGTH;++i)
		cout << "=";
}
void DISPLAY::PrintLine(const string& target)
{
	for (int i = 0; i < SCREEN_LENGTH; ++i)
		cout << target;
}

coordinate DISPLAY::Map2Screen(int x,int y)
{
	const int store_UI_height = 11;
	if (x > 7)
		x = 6;
	if (y > 5)
		y = 4;
	coordinate map_o = { 0,10-1 };//地圖左上角原點
	coordinate target = { (SHORT)x * 18,(SHORT)y * 10 };
	return target+map_o;
}


void DISPLAY::RefreshStdOut()
{
	SetScreenCursor(0, 0);
	//system("cls"); cls會導致鼠標捕獲模式退出
	for (int i = 0; i < SCREEN_WIDTH; ++i)
	{
		cout << SCREEN_BUFFER[i];
	}
}

void DISPLAY::CleanMapCell(int x, int y)
{
	coordinate tmp = Map2Screen(x, y);
	ReadDataFileToScreenBuff("mapcell.txt", tmp.X, tmp.Y);//TODO 不需要每次刷新時都讀文件
}

DISPLAY::DISPLAY():
	SCREEN_SIZE({0,0}),
	ScreenCursor({0,0}),
	MouseCursor({0,0})
{
	this->hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//獲得標準輸出句柄
	
	window_init();

	GetConsoleCursorInfo(hStdOut, &this->default_cursor);// 保存初始光標信息，便於恢復
	//ScreenCursor = { 0,0 };

	HideCursor();

	//ReadInfo();
	//ReadMap();
	ReadDataFileToScreenBuff("info.txt",0,0);

	ReadDataFileToScreenBuff("map.txt",0,10);

	RefreshStdOut();
	WriteScreenBuffer("Test Mode! Wakanda forever!!!",Map2Screen( 5,6));
	CleanMapCell(5, 6);
	//RefreshStdOut();
}

DISPLAY::~DISPLAY()
{
	for (int i = 0; i < SCREEN_WIDTH; ++i)
		delete[] SCREEN_BUFFER[i];
	delete SCREEN_BUFFER;
	CloseHandle(this->hStdOut);   // 关闭标准输入设备句柄
	ShowCursor();
}

void DISPLAY::PrintOnMouse(const string& target)
{
	//SetConsoleActiveScreenBuffer(StdOutBuf);
	RefreshStdOut();//清掉之前打印的鼠標打印的東西
	int half_of_string = target.length() >> 1;//>>1 相當於/2
	int x = MouseCursor.X - half_of_string;

	//避免邊角錯誤
	x = x > 0 ? x : 0;//左邊界
	x = MouseCursor.X + half_of_string < SCREEN_LENGTH ? x : SCREEN_LENGTH - target.length();//右邊界
	
	coordinate middle = { (SHORT)x,(SHORT)MouseCursor.Y };
		//讓要打印的内容出現在指標中間，也就是讓打印内容的中心處於指標位置
	PrintOnXY(target, middle);
	//SetConsoleActiveScreenBuffer(hStdOut);
	//PrintOnXY(string("MousePostion"), 0, 61); PrintOnXY(MouseCursor, 20, 61);
}
void DISPLAY::PrintOnXY(const  string& target, SHORT x, SHORT y)
{
	coordinate tmp = { x,y };
	SetConsoleCursorPosition(hStdOut, tmp);
	cout << target;
	SetConsoleCursorPosition(hStdOut, ScreenCursor);//維護屏幕指針
}
void DISPLAY::PrintOnXY(const string& target, coordinate position)
{
	PrintOnXY(target, position.X, position.Y);
}
void DISPLAY::PrintOnXY(const  coordinate& target, SHORT x, SHORT y)
{
	coordinate tmp = { x,y };
	SetConsoleCursorPosition(hStdOut, tmp);
	cout << target;
	SetConsoleCursorPosition(hStdOut, ScreenCursor);
}
void DISPLAY::PrintOnXY(const coordinate& target, coordinate position)
{
	PrintOnXY(target, position.X, position.Y);
}


void DISPLAY::window_init()
{
	SetConsoleTitle(L"Plant VS Zombie"); // 設置窗口标题
	HWND hwnd = GetForegroundWindow();

	//int cx = GetSystemMetrics(SM_CXSCREEN);//單位：像素
	//int cy = GetSystemMetrics(SM_CYSCREEN);
	//LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* 获取窗口信息 */
	/////* 设置窗口信息 最大化 取消边框 */
	//SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle /*| WS_POPUP*/ | WS_MAXIMIZE) /*& ~WS_CAPTION*/ & ~WS_THICKFRAME /*& ~WS_BORDER*/);

	//SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);

	ShowWindow(hwnd, SW_SHOWMAXIMIZED);//設置窗口最大化
	ShowScrollBar(hwnd, SB_BOTH, FALSE);//去除可能出現的滾動條

	CONSOLE_SCREEN_BUFFER_INFO ScreenBuffer; // 窗口缓冲区信息
	/*
	typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
		COORD dwSize; 緩衝區大小
		COORD dwCursorPosition; 當前光標位置
		WORD  wAttributes; 字符屬性
		SMALL_RECT srWindow; 當前窗口顯示的大小與位置
		COORD dwMaximumWindowSize; 最大窗口大小
	} CONSOLE_SCREEN_BUFFER_INFO;
	*/
	GetConsoleScreenBufferInfo(this->hStdOut, &ScreenBuffer);// 获取窗口缓冲区信息
	SCREEN_SIZE = ScreenBuffer.dwMaximumWindowSize;
	SetConsoleScreenBufferSize(this->hStdOut, SCREEN_SIZE);//設置屏幕緩衝區大小相同于窗口大小，防止滾動
	SCREEN_SIZE = SCREEN_SIZE - coordinate({ 0,1 });

	screen_buffer_init();
}

void DISPLAY::screen_buffer_init()
{
	SCREEN_BUFFER = new char* [SCREEN_WIDTH];//建立屏幕輸出緩衝
	for (int i = 0; i < SCREEN_WIDTH; ++i)
	{
		SCREEN_BUFFER[i] = new char[SCREEN_LENGTH+1];
		SCREEN_BUFFER[i][SCREEN_LENGTH] = '\0';
		for (int j = 0; j < SCREEN_LENGTH; ++j)
			SCREEN_BUFFER[i][j] = ' ';
	}
}

void DISPLAY::WriteScreenBuffer(const char* target, coordinate position)
{
	int length = strlen(target);
	if (position.Y > SCREEN_WIDTH)//縱坐標邊界檢查
		return;
	for (int i = 0; i < length && i+position.X < SCREEN_LENGTH-1; ++i)//終止條件包含橫坐標邊界檢查
		this->SCREEN_BUFFER[position.Y][i+position.X] = target[i];
}

void DISPLAY::SetScreenCursor(int x, int y)
{
	ScreenCursor.X = x;
	ScreenCursor.Y = y;
	SetConsoleCursorPosition(hStdOut, ScreenCursor);
}
void DISPLAY::SetMousePosition(coordinate target)
{
	if (target.Y > SCREEN_WIDTH - 1)
		target.Y -= 1;//防止在最下一行打印造成屏幕捲動閃屏
	MouseCursor = target;
}
void DISPLAY::SetScreenCursor(coordinate target)
{
	SetScreenCursor(target.X, target.Y);
}

void DISPLAY::HideCursor()
{
	CONSOLE_CURSOR_INFO hide_cursor = { 1, 0 };
	SetConsoleCursorInfo(hStdOut, &hide_cursor);
}
void DISPLAY::ShowCursor()
{
	SetConsoleCursorInfo(hStdOut, &default_cursor);
}