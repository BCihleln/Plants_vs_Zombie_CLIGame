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

//void DISPLAY::PrintLine()
//{
//	for(int i = 0;i<SCREEN_LENGTH;++i)
//		cout << "=";
//}
//void DISPLAY::PrintLine(const string& target)
//{
//	for (int i = 0; i < SCREEN_LENGTH; ++i)
//		cout << target;
//}

//coordinate DISPLAY::Map2Screen(short x,short y)
//{
//	const int store_UI_height = 11;
//	if (x > 7)
//		x = 6;
//	if (y > 5)
//		y = 4;
//	coordinate map_o = { 0,10-1 };//�؈D���Ͻ�ԭ�c
//	coordinate target = { (short)x * map_cell_length,(short)y * map_cell_width };
//	return target+map_o;
//}
//coordinate DISPLAY::Map2Screen(coordinate position)
//{
//	return Map2Screen(position.X, position.Y);
//}


void DISPLAY::RefreshStdOut()
{
	//color(white);
	SetScreenCursor(0, 0);
	//system("cls"); cls��������˲��@ģʽ�˳�
	for (int i = 0; i <= SCREEN_WIDTH; ++i)
	{
		cout << SCREEN_BUFFER[i];//����ֱ�Ӵ�ӡ������Ļ�L�ȣ�����Ҫ�քӓQ��
	}

}

void DISPLAY::CleanMapCell(coordinate target_Cell)
{
	coordinate tmp = map->Table2Screen(target_Cell);
	ReadDataFileToScreenBuff("mapcell.txt", tmp.X, tmp.Y);//TODO ����Ҫÿ��ˢ�r���x�ļ�

}

DISPLAY::DISPLAY(const Map&target_map,const Store& target_store):
	SCREEN_SIZE({0,0}),
	ScreenCursor({0,0}),
	MouseCursor({0,0}),
	map(&target_map),store(&target_store)
{
	this->hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//�@�Ø˜�ݔ�����
	
	window_init();

	GetConsoleCursorInfo(hStdOut, &this->default_cursor);// �����ʼ�����Ϣ����춻֏�
	//ScreenCursor = { 0,0 };

	HideCursor();

	//ReadInfo();
	//ReadMap();
	ReadDataFileToScreenBuff(info_file,0,0);

	ReadDataFileToScreenBuff(map_file,0,10);

	RefreshStdOut();
	//WriteScreenBuffer("Test Mode! Wakanda forever!!!",Map2Screen( 5,6));
	//CleanMapCell(5, 6);
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

//��������ȵ���ʼλ��(��Ļ)�����ؾ��к������
coordinate DISPLAY::middle(const string& target, coordinate left_side)
{
	int half_of_string = target.length() >> 1;//>>1 �ஔ�/2
	short x = left_side.X - half_of_string;

	//����߅���e�`
	x = x > 0 ? x : 0;//��߅��
	x = left_side.X + half_of_string < SCREEN_LENGTH ? x : SCREEN_LENGTH - (short)target.length();//��߅��

	return { x,left_side.Y };
}


void DISPLAY::PrintOnMouse(const string& target)
{
	//SetConsoleActiveScreenBuffer(StdOutBuf);
	RefreshStdOut();//���֮ǰ��ӡ����˴�ӡ�Ė|��
	//׌Ҫ��ӡ�����ݳ��F��ָ�����g��Ҳ����׌��ӡ���ݵ�����̎�ָ��λ��
	PrintOnXY(target, middle(target,MouseCursor));
}
void DISPLAY::PrintOnXY(const  string& target, short x, short y)
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
void DISPLAY::PrintOnXY(const  coordinate& target, short x, short y)
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


void DISPLAY::PrintStore() const
{
	
}

void DISPLAY::window_init()
{
	SetConsoleTitle(L"Plant VS Zombie"); // �O�ô��ڱ��� ǰ���L���팒�ַ�
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
	SCREEN_BUFFER = new char* [SCREEN_WIDTH+1];//������Ļݔ�����n
	for (int i = 0; i < SCREEN_WIDTH+1; ++i)
	{
		SCREEN_BUFFER[i] = new char[SCREEN_LENGTH+1];
		SCREEN_BUFFER[i][SCREEN_LENGTH] = '\0';
		for (int j = 0; j < SCREEN_LENGTH; ++j)
			SCREEN_BUFFER[i][j] = ' ';
	}
	SCREEN_BUFFER[SCREEN_WIDTH ][SCREEN_LENGTH - 1] = '\0';//����һ�е����ڶ�λ�O�Þ�\0��ֹ��ӡ�L��
}
void DISPLAY::WriteScreenBuffer(const char* target, coordinate position)
{
	int length = strlen(target);
	if (position.Y > SCREEN_WIDTH)//�v����߅��z��
	{
		color(red);
		cout << __FUNCTION__ << "Out of range" << endl;
		cout << position;
		exit(0);
	}
	for (int i = 0; i < length && i+position.X < SCREEN_LENGTH-1; ++i)//�Kֹ�l�������M����߅��z��
		this->SCREEN_BUFFER[position.Y][i+position.X] = target[i];
}

void DISPLAY::SetScreenCursor(short x, short y)
{
	ScreenCursor.X = x;
	ScreenCursor.Y = y;
	SetConsoleCursorPosition(hStdOut, ScreenCursor);
}
void DISPLAY::SetScreenCursor(coordinate target)
{
	SetScreenCursor(target.X, target.Y);
}
void DISPLAY::SetMousePosition(coordinate target)
{
	if (target == coordinate{ SCREEN_LENGTH-1, SCREEN_WIDTH })
		target = target - coordinate{1, 0};//��ֹ�����½Ǵ�ӡ�r��������W�q
	MouseCursor = target;
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


//ֻ��ֲ��Nֲ�ɹ����{��
void DISPLAY::NewPlant(coordinate screen_position, const string& name)
{
	WriteScreenBuffer(name.c_str(), middle(name, map->Screen2Cell_middle(screen_position)));

	//else
	//	PrintOnMouse("Out of Boarder!!!");
}