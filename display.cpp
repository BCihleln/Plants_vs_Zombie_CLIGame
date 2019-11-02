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

		for (int i = 0; i < SCREEN_LENGTH; ++i)//��Q��getline�^������ӵ�\0
			if (SCREEN_BUFFER[position_y][i] == '\0')
				SCREEN_BUFFER[position_y][i] = tmp_line[i];

		position_y++;//��һ��
	}
	file.close();
	delete[] tmp_line;//ጷŕ��r��Ո���ڴ�
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
	coordinate map_o = { 0,10-1 };//�؈D���Ͻ�ԭ�c
	coordinate target = { (SHORT)x * 18,(SHORT)y * 10 };
	return target+map_o;
}


void DISPLAY::RefreshStdOut()
{
	SetScreenCursor(0, 0);
	//system("cls"); cls��������˲��@ģʽ�˳�
	for (int i = 0; i < SCREEN_WIDTH; ++i)
	{
		cout << SCREEN_BUFFER[i];
	}
}

void DISPLAY::CleanMapCell(int x, int y)
{
	coordinate tmp = Map2Screen(x, y);
	ReadDataFileToScreenBuff("mapcell.txt", tmp.X, tmp.Y);//TODO ����Ҫÿ��ˢ�r���x�ļ�
}

DISPLAY::DISPLAY():
	SCREEN_SIZE({0,0}),
	ScreenCursor({0,0}),
	MouseCursor({0,0})
{
	this->hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//�@�Ø˜�ݔ�����
	
	window_init();

	GetConsoleCursorInfo(hStdOut, &this->default_cursor);// �����ʼ�����Ϣ����춻֏�
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
	CloseHandle(this->hStdOut);   // �رձ�׼�����豸���
	ShowCursor();
}

void DISPLAY::PrintOnMouse(const string& target)
{
	//SetConsoleActiveScreenBuffer(StdOutBuf);
	RefreshStdOut();//���֮ǰ��ӡ����˴�ӡ�Ė|��
	int half_of_string = target.length() >> 1;//>>1 �ஔ�/2
	int x = MouseCursor.X - half_of_string;

	//����߅���e�`
	x = x > 0 ? x : 0;//��߅��
	x = MouseCursor.X + half_of_string < SCREEN_LENGTH ? x : SCREEN_LENGTH - target.length();//��߅��
	
	coordinate middle = { (SHORT)x,(SHORT)MouseCursor.Y };
		//׌Ҫ��ӡ�����ݳ��F��ָ�����g��Ҳ����׌��ӡ���ݵ�����̎�ָ��λ��
	PrintOnXY(target, middle);
	//SetConsoleActiveScreenBuffer(hStdOut);
	//PrintOnXY(string("MousePostion"), 0, 61); PrintOnXY(MouseCursor, 20, 61);
}
void DISPLAY::PrintOnXY(const  string& target, SHORT x, SHORT y)
{
	coordinate tmp = { x,y };
	SetConsoleCursorPosition(hStdOut, tmp);
	cout << target;
	SetConsoleCursorPosition(hStdOut, ScreenCursor);//�S�o��Ļָ�
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
	SetConsoleTitle(L"Plant VS Zombie"); // �O�ô��ڱ���
	HWND hwnd = GetForegroundWindow();

	//int cx = GetSystemMetrics(SM_CXSCREEN);//��λ������
	//int cy = GetSystemMetrics(SM_CYSCREEN);
	//LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* ��ȡ������Ϣ */
	/////* ���ô�����Ϣ ��� ȡ���߿� */
	//SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle /*| WS_POPUP*/ | WS_MAXIMIZE) /*& ~WS_CAPTION*/ & ~WS_THICKFRAME /*& ~WS_BORDER*/);

	//SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);

	ShowWindow(hwnd, SW_SHOWMAXIMIZED);//�O�ô������
	ShowScrollBar(hwnd, SB_BOTH, FALSE);//ȥ�����ܳ��F�ĝL�ӗl

	CONSOLE_SCREEN_BUFFER_INFO ScreenBuffer; // ���ڻ�������Ϣ
	/*
	typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
		COORD dwSize; ���n�^��С
		COORD dwCursorPosition; ��ǰ���λ��
		WORD  wAttributes; �ַ�����
		SMALL_RECT srWindow; ��ǰ�����@ʾ�Ĵ�С�cλ��
		COORD dwMaximumWindowSize; ��󴰿ڴ�С
	} CONSOLE_SCREEN_BUFFER_INFO;
	*/
	GetConsoleScreenBufferInfo(this->hStdOut, &ScreenBuffer);// ��ȡ���ڻ�������Ϣ
	SCREEN_SIZE = ScreenBuffer.dwMaximumWindowSize;
	SetConsoleScreenBufferSize(this->hStdOut, SCREEN_SIZE);//�O����Ļ���n�^��С��ͬ�ڴ��ڴ�С����ֹ�L��
	SCREEN_SIZE = SCREEN_SIZE - coordinate({ 0,1 });

	screen_buffer_init();
}

void DISPLAY::screen_buffer_init()
{
	SCREEN_BUFFER = new char* [SCREEN_WIDTH];//������Ļݔ�����n
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
	if (position.Y > SCREEN_WIDTH)//�v����߅��z��
		return;
	for (int i = 0; i < length && i+position.X < SCREEN_LENGTH-1; ++i)//�Kֹ�l�������M����߅��z��
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
		target.Y -= 1;//��ֹ������һ�д�ӡ�����Ļ�Ԅ��W��
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