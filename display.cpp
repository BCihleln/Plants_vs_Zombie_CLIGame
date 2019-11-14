#include "display.h"

inline void Display::ReadDataFileToScreenBuff(const char* filepath, coordinate start_position)
{
	ifstream file;
	file.open(filepath);
	char* tmp_line = new char[SCREEN_LENGTH+1];
	if (!file.is_open())
	{
		color(red);
		cout << filepath << "open failed" << endl;
		getchar();
		exit(0);
	}

	int i = start_position.Y;//SCREEN_BUFFER �������±�
	while (!file.eof())
	{
		if (i > SCREEN_WIDTH)
		{
			color(red);
			cout << __FUNCTION__ << endl<< 
				"Write Screen Buffer out of range"<< endl 
				<< filepath ;
			getchar();
			exit(0);
		}
		strcpy(tmp_line, SCREEN_BUFFER[i]);
		file.getline(&SCREEN_BUFFER[i][start_position.X], SCREEN_LENGTH);

		for (int j = 0; j < SCREEN_LENGTH; ++j)//��Q��getline�^������ӵ�\0
			if (SCREEN_BUFFER[i][j] == '\0')
				SCREEN_BUFFER[i][j] = tmp_line[j];

		//cout << SCREEN_BUFFER[position_y];
		i++;//��һ��
	}
	file.close();
	delete[] tmp_line;//ጷŕ��r��Ո���ڴ�
}

void Display::RefreshStdOut()const
{
	 SetConsoleCursorPosition(hStdOut, { 0,0 });
	//system("cls"); cls��������˲��@ģʽ�˳�
	for (int i = 0; i <= SCREEN_WIDTH; ++i)
	{
		cout << SCREEN_BUFFER[i];//����ֱ�Ӵ�ӡ������Ļ�L�ȣ�����Ҫ�քӓQ��
	}
}

//void Display::CleanMapCell(coordinate target_Cell)
//{
//	coordinate tmp = map->Table2Screen(target_Cell);
//	ReadDataFileToScreenBuff("mapcell.txt", tmp.X, tmp.Y);//TODO ����Ҫÿ��ˢ�r���x�ļ�
//
//}

Display::Display(const Map&target_map,const Store& target_store,int* score):
	SCREEN_SIZE({0,0}),
	ScreenCursor({0,0}),
	MouseCursor({0,0}),
	map(&target_map),store(&target_store),
	score(score)
{
	this->hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//�@�Ø˜�ݔ�����
	
	window_init();

	GetConsoleCursorInfo(hStdOut, &this->default_cursor);// �����ʼ�����Ϣ����춻֏�
	//ScreenCursor = { 0,0 };

	HideCursor();

	//ReadInfo();
	//ReadMap();
	ReadDataFileToScreenBuff(info_file, { 0,0 });
	ReadDataFileToScreenBuff(map_file, { 0,10 });
	ReadStoreInfo();

	RefreshStdOut();
	//WriteScreenBuffer("Test Mode! Wakanda forever!!!",Map2Screen( 5,6));
	//CleanMapCell(5, 6);
	//RefreshStdOut();
}

Display::~Display()
{
	for (int i = 0; i < SCREEN_WIDTH; ++i)
		delete[] SCREEN_BUFFER[i];
	delete SCREEN_BUFFER;
	CloseHandle(this->hStdOut);   // �رձ�׼�����豸���
	ShowCursor();
}

//��������ȵ���ʼλ��(��Ļ)�����ؾ��к������
coordinate Display::middle(const string& target, coordinate left_side)
{
	int half_of_string = target.length() >> 1;//>>1 �ஔ�/2
	short x = left_side.X - half_of_string;

	//����߅���e�`
	x = x > 0 ? x : 0;//��߅��
	x = left_side.X + half_of_string < SCREEN_LENGTH ? x : SCREEN_LENGTH - (short)target.length();//��߅��

	return { x,left_side.Y };
}


void Display::PrintOnMouse(const string& target)
{
	RefreshStdOut();//���֮ǰ��ӡ����˴�ӡ�Ė|��
	//TODO ������˴�ӡЧ��
	//SetScreenCursor(0, last_MouseCursor_Y);
	//cout << SCREEN_BUFFER[last_MouseCursor_Y];
	//SetScreenCursor(0, 0);

	//׌Ҫ��ӡ�����ݳ��F��ָ�����g��Ҳ����׌��ӡ���ݵ�����̎�ָ��λ��
	PrintOnXY(target, middle(target,MouseCursor));
}
void Display::PrintOnXY(const  string& target, short x, short y)
{
	coordinate tmp = { x,y };
	SetConsoleCursorPosition(hStdOut, tmp);
	cout << target;
	SetConsoleCursorPosition(hStdOut, ScreenCursor);//�S�o��Ļָ�
}
void Display::PrintOnXY(const string& target, coordinate position)
{
	PrintOnXY(target, position.X, position.Y);
}
void Display::PrintOnXY(const  coordinate& target, short x, short y)
{
	coordinate tmp = { x,y };
	SetConsoleCursorPosition(hStdOut, tmp);
	cout << target;
	SetConsoleCursorPosition(hStdOut, ScreenCursor);
}
void Display::PrintOnXY(const coordinate& target, coordinate position)
{
	PrintOnXY(target, position.X, position.Y);
}


void Display::ReadStoreInfo()
{
	for (short i = 0; i < store_row; ++i)
		for (short j = 0; j < store_column; ++j)
		{
			//string product_name = store->table[i][j].plant.name();
			product& target = store->table[i][j];
			string product_name = target.plant.name();
			if(product_name != "None")
			{
				coordinate position = middle(product_name, store->Table2Screen({ j,i })) ;
				WriteScreenBuffer(product_name.c_str(), position- coordinate{ 0,2 });
				char tmp[15];
				sprintf(tmp, "cost : %d", target.plant.cost());
				WriteScreenBuffer(tmp, position - coordinate{ 0,1 });
			}
		}
}

void Display::window_init()
{
	SetConsoleTitle(L"Plant VS Zombie"); // �O�ô��ڱ��� ǰ���L���팒�ַ�
	HWND hwnd = GetForegroundWindow();
	
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
	//SCREEN_SIZE = SCREEN_SIZE - coordinate({ 0,1 });
	SCREEN_SIZE -= coordinate{0, 1};

	screen_buffer_init();
}

void Display::screen_buffer_init()
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
void Display::WriteScreenBuffer(const char* target, coordinate position)
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

void Display::SetScreenCursor(short x, short y)
{
	ScreenCursor.X = x;
	ScreenCursor.Y = y;
	SetConsoleCursorPosition(hStdOut, ScreenCursor);
}
void Display::SetScreenCursor(coordinate target)
{
	SetScreenCursor(target.X, target.Y);
}
void Display::SetMousePosition(coordinate target)
{
	if (target.Y != last_MouseCursor_Y)
		last_MouseCursor_Y = MouseCursor.Y;
	if (target == coordinate{ SCREEN_LENGTH-1, SCREEN_WIDTH })
		target = target - coordinate{1, 0};//��ֹ�����½Ǵ�ӡ�r��������W�q
	MouseCursor = target;
}

void Display::HideCursor()
{
	CONSOLE_CURSOR_INFO hide_cursor = { 1, 0 };
	SetConsoleCursorInfo(hStdOut, &hide_cursor);
}
void Display::ShowCursor()
{
	SetConsoleCursorInfo(hStdOut, &default_cursor);
}


//ֻ��ֲ��Nֲ�ɹ����{��
void Display::NewPlant(coordinate screen_position, const string& name)
{
	WriteScreenBuffer(name.c_str(), middle(name, map->Screen2Cell_middle(screen_position)));
}

void Display::UpdateStore()
{
	for (short i = 0; i < store_row; ++i)
		for (short j = 0; j < store_column; ++j)
		{
			product target = store->table[i][j];
			int product_lefttime =target.left_time;
			int product_cost = target.plant.cost();
			char tmp[10];
			float percentage = (float)product_lefttime / (float)target.plant.cool_time() * (float)100;
			sprintf(tmp, "(%d%%)", 100-(int)percentage);
			coordinate position = middle(tmp, store->Table2Screen({ j,i }) + coordinate{ 0,1 });
			WriteScreenBuffer("           ", middle("           ", position));
			if (product_lefttime > 0)
			{
				WriteScreenBuffer(tmp, position);
			}
		}
}

void Display::UpdateSun()
{
	char tmp[10];
	sprintf(tmp, "%d", store->sun);
	WriteScreenBuffer("              ", middle("              ", { 9,5 }));
	WriteScreenBuffer(tmp, middle(tmp, { 9,5 }));
}

void Display::UpdateScore()
{
	char tmp[10];
	sprintf(tmp, "%d", *score);
	WriteScreenBuffer(tmp, middle(tmp, { 138,4 }));
}

void Display::UpdateZombie()
{
	for (int i = 0; i < map_row; ++i)
	{
		for(int j = 0;j< map->zombies[i].size();++j)
		{
			coordinate zombie_position = map->zombies[i][j].screen;
			PrintOnXY(map->zombies[i][j].zombie.name(), zombie_position);
		}
	}
}

void Display::next()
{
	//new thread
	while(true)
	{
		UpdateStore();
		UpdateSun();
		UpdateScore();
	}
}

//void Display::next()
//{
//		UpdateStore();
//		UpdateSun();
//		UpdateScore();
//}