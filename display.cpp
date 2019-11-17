#include "display.h"

inline void Display::ReadDataFileToScreenBuff(ifstream& file, coordinate start_position)
{
	if (!file.is_open())
	{
		system("cls");
		color(red);
		cout <<  "file open failed" << endl;
		getchar();
		exit(0);
	}

	char* tmp_line = new char[SCREEN_LENGTH+1];
	int i = start_position.Y;//SCREEN_BUFFER �������±�
	while (!file.eof())
	{
		if (i > SCREEN_WIDTH)
		{
			system("cls");
			color(red);
			cout << __FUNCTION__ << endl<< 
				"Write Screen Buffer out of range"<< endl;
			getchar();
			exit(0);
		}
		strcpy(tmp_line, MapLayer[i]);
		file.getline(&MapLayer[i][start_position.X], SCREEN_LENGTH);

		for (int j = 0; j < SCREEN_LENGTH; ++j)//��Q��getline�^������ӵ�\0
			if (MapLayer[i][j] == '\0')
				MapLayer[i][j] = tmp_line[j];

		//cout << SCREEN_BUFFER[position_y];
		i++;//��һ��
	}
	delete[] tmp_line;//ጷŕ��r��Ո���ڴ�
}

void Display::RefreshStdOut()
{
	//mutex.lock();
	 SetConsoleCursorPosition(hStdOut, { 0,0 });
	//system("cls"); cls��������˲��@ģʽ�˳�
	for (int i = 0; i <= SCREEN_WIDTH; ++i)
	{
		cout << DynamicLayer[i];//����ֱ�Ӵ�ӡ������Ļ�L�ȣ�����Ҫ�քӓQ��
	}
	//mutex.unlock();
}
inline void Display::RefreshLayer()
{
	for (int i = 0; i <= SCREEN_WIDTH; ++i)
	{
		strcpy(DynamicLayer[i],MapLayer[i]);
	}
}

//void Display::RefreshConsoleScreenBuffer()
//{
//	coordinate tmp = { 0,0 };
//	DWORD tmp2=0;
//	for (int i = 0; i <= SCREEN_WIDTH; ++i)
//	{//����ֱ�Ӵ�ӡ������Ļ�L�ȣ�����Ҫ�քӓQ��
//		tmp.Y = i;
//		WriteConsoleOutputCharacterA(ConsoleScreenBuffer, SCREEN_BUFFER[i], SCREEN_LENGTH, tmp, &tmp2);
//	}
//}

//void Display::CleanMapCell(coordinate target_Cell)
//{
//	coordinate tmp = map->Table2Screen(target_Cell);
//	ReadDataFileToScreenBuff("mapcell.txt", tmp.X, tmp.Y);//TODO ����Ҫÿ��ˢ�r���x�ļ�
//
//}

Display::Display(
	const Map&target_map,const Store& target_store,
	ifstream& map_file,
	ifstream& info_file, int* score
):
	SCREEN_SIZE({0,0}),
	ScreenCursor({0,0}),
	MouseCursor({0,0}),
	map(&target_map),
	store(&target_store),
	score(score),
	continue_flag(true),
	MouseDisplay("+")
{
	this->hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//�@�Ø˜�ݔ�����
	//ConsoleScreenBuffer = CreateConsoleScreenBuffer(
	//	GENERIC_WRITE,//���x�M�̿��������n�^������
	//	FILE_SHARE_WRITE,//���x���n�^�ɹ��팑����
	//	NULL,
	//	CONSOLE_TEXTMODE_BUFFER,
	//	NULL
	//);

	//�@ȡ�˜�ݔ��������O�ô��ڣ���򲻿��
	window_init();
	screen_buffer_init();

	GetConsoleCursorInfo(hStdOut, &this->default_cursor);// �����ʼ�����Ϣ����춻֏�
	//ScreenCursor = { 0,0 };

	HideCursor();

	//ReadInfo();
	//ReadMap();
	ReadDataFileToScreenBuff(info_file, { 0,0 });
	ReadDataFileToScreenBuff(map_file, { 0,10 });
	ReadStoreInfo();

	RefreshStdOut();
	RefreshLayer();
	//RefreshConsoleScreenBuffer();
	//WriteScreenBuffer("Test Mode! Wakanda forever!!!",Map2Screen( 5,6));
	//CleanMapCell(5, 6);
	//RefreshStdOut();

	//������Ļ�Q��
	std::thread display_next(std::bind(&Display::next, this));//�Q�̽����r�������Ŀ�˺����cԓ��������ĵ�ַ
	
/*
֮ǰ��game_system�е�bug������ӛ��ȡ��ַ�������¾��g����������һ��Display�Č���A������game_system�е�display�����}�u�^ȥ��Ȼ��display��SCREEN_BUFFER��������Ո�Ŀ��g��A��SCREEN_BUFFERδ���^��ʼ����ָ���˲�ԓ�L����λ�ã������e�`
*/
	display_next.detach();
}

Display::~Display()
{
	continue_flag = false;
	mutex.lock();//�ȴ������Q���\���Y������������

	for (int i = 0; i < SCREEN_WIDTH; ++i)
	{
		delete[] MapLayer[i];
		delete[] DynamicLayer[i];
	}
	delete[] MapLayer;
	delete[] DynamicLayer;
	CloseHandle(this->hStdOut);   // �رձ�׼�����豸���
	ShowCursor();

	mutex.unlock();
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


void Display::PrintOnMouse()
{
	mutex.lock();
	//SetConsoleActiveScreenBuffer(ConsoleScreenBuffer);

	RefreshStdOut();//���֮ǰ��ӡ����˴�ӡ�Ė|��
	//string eraser(target.length(),' ');
	//if(last_MouseCursor_Y!=MouseCursor.Y)
		//PrintOnXY(eraser, middle(eraser, coordinate{ MouseCursor.X, last_MouseCursor_Y }));

	//׌Ҫ��ӡ�����ݳ��F��ָ�����g��Ҳ����׌��ӡ���ݵ�����̎�ָ��λ��
	SetConsoleCursorPosition(hStdOut, middle(MouseDisplay, MouseCursor));
	cout << MouseDisplay;
	SetConsoleCursorPosition(hStdOut, ScreenCursor);//�S�o��Ļ���

	mutex.unlock();
}
void Display::PrintOnXY(const string& target, coordinate position)
{
	if (position < coordinate{ 0,0 } || position > SCREEN_SIZE)//����z��
		return;
	//SetConsoleActiveScreenBuffer(ConsoleScreenBuffer);

	//mutex.lock();
	SetConsoleCursorPosition(hStdOut, coordinate{ 0,position.Y });//����һ��
	cout << MapLayer[position.Y];

	SetConsoleCursorPosition(hStdOut, position);
	cout << target;

	SetConsoleCursorPosition(hStdOut, ScreenCursor);//�S�o��Ļָ�
}
void Display::PrintOnXY(const  coordinate& target, short x, short y)
{
	//mutex.lock();
	coordinate tmp = { x,y };
	SetConsoleCursorPosition(hStdOut, tmp);
	cout << target;
	//SetConsoleCursorPosition(hStdOut, ScreenCursor);//�S�o��Ļָ�
	//SetConsoleCursorPosition(hStdOut, coordinate{ 0,0 });
	//mutex.unlock();
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
				coordinate position = middle(product_name, store->Table2Screen({ i,j })) ;
				WriteScreenBuffer(MapLayer,product_name.c_str(), position- coordinate{ 0,2 },false);
				char tmp[15];
				sprintf(tmp, "cost : %d", target.plant.cost());
				WriteScreenBuffer(MapLayer,tmp, position - coordinate{ 0,1 },false );
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

}

void Display::screen_buffer_init()
{
	MapLayer = new char* [SCREEN_WIDTH+1];//������Ļݔ�����n
	DynamicLayer = new char* [SCREEN_WIDTH + 1];
	for (int i = 0; i < SCREEN_WIDTH+1; ++i)
	{
		MapLayer[i] = new char[SCREEN_LENGTH+1];
		MapLayer[i][SCREEN_LENGTH] = '\0';

		DynamicLayer[i] = new char[SCREEN_LENGTH + 1];
		DynamicLayer[i][SCREEN_LENGTH] = '\0';
		for (int j = 0; j < SCREEN_LENGTH; ++j)
		{
			MapLayer[i][j] = ' ';
			DynamicLayer[i][j] = ' ';
		}
	}
	MapLayer[SCREEN_WIDTH ][SCREEN_LENGTH - 1] = '\0';//����һ�е����ڶ�λ�O�Þ�\0��ֹ��ӡ�L��
	DynamicLayer[SCREEN_WIDTH ][SCREEN_LENGTH - 1] = '\0';//����һ�е����ڶ�λ�O�Þ�\0��ֹ��ӡ�L��
}
void Display::WriteScreenBuffer(char* ScreenBuffer[],const char* target, coordinate position, bool middle_flag)
{
	if (middle_flag)
		position = middle(target, position);
	int length = strlen(target);
	if (position > SCREEN_SIZE || position < coordinate{0, 0})//߅��z��
	{
		color(red);
		cout << __FUNCTION__ << " Out of range" << endl;
		cout << position;
		exit(0);
	}
	for (int i = 0; i < length && i+position.X < SCREEN_LENGTH-1; ++i)//�Kֹ�l�������M����߅��z��
		ScreenBuffer[position.Y][i+position.X] = target[i];
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
//void Display::NewPlant(coordinate screen_position, const string& name)
//{
//	//WriteScreenBuffer(DynamicLayer,name.c_str(), middle(name, map->Screen2Cell_middle(screen_position)));
//	WriteScreenBuffer(DynamicLayer,name.c_str(), map->Screen2Cell_middle(screen_position),true);
//}

void Display::UpdateStore()
{
	if (!continue_flag)//�������Q���ѽ��l��ֹͣՈ�󣬸��Q�̅s�ѽ��M��ѭ�h����r
		return;

	for (short i = 0; i < store_row; ++i)
		for (short j = 0; j < store_column; ++j)
		{
			product target = store->table[i][j];
			int product_lefttime =target.left_time;
			int product_cost = target.plant.cost();
			char tmp[10];
			float percentage = (float)product_lefttime / (float)target.plant.cool_time() * (float)100;
			sprintf(tmp, "(%d%%)", 100-(int)percentage);
			coordinate position = store->Table2Screen({ i,j }) + coordinate{ 0,1 };
			WriteScreenBuffer(DynamicLayer,"           ", position,true);//���Ҫ��ӡ��λ��
			if (product_lefttime > 0)
			{
				WriteScreenBuffer(DynamicLayer,tmp, position,true);
			}
		}
}
void Display::UpdateSun()
{
	if (!continue_flag)//�������Q���ѽ��l��ֹͣՈ�󣬸��Q�̅s�ѽ��M��ѭ�h����r
		return;

	char tmp[10];
	sprintf(tmp, "%d", store->sun);
	WriteScreenBuffer(DynamicLayer,"              ", { 9,5 },true);
	WriteScreenBuffer(DynamicLayer,tmp, { 9,5 },true);
}
void Display::UpdateScore()
{
	if (!continue_flag)//�������Q���ѽ��l��ֹͣՈ�󣬸��Q�̅s�ѽ��M��ѭ�h����r
		return;

	char tmp[10];
	sprintf(tmp, "%d", *score);
	WriteScreenBuffer(DynamicLayer,tmp, { 138,4 },true);
}
void Display::UpdateZombie()
{
	if (!continue_flag)//�������Q���ѽ��l��ֹͣՈ�󣬸��Q�̅s�ѽ��M��ѭ�h����r
		return;

	//mutex.lock();
	for (int i = 0; i < map_row; ++i)
	{
		for(int j = 0;j< map->zombies[i].size();++j)
		{
			const Zombie& z = map->zombies[i][j].zombie;
			const coordinate& zombie_position = map->zombies[i][j].screen;
			if(zombie_position < SCREEN_SIZE )
			{
				WriteScreenBuffer(DynamicLayer, &MapLayer[zombie_position.Y][zombie_position.X], zombie_position,false);//���һ��
				WriteScreenBuffer(DynamicLayer,z.name().c_str(), zombie_position,false);
			}
		}
	}
	//mutex.unlock();
}
void Display::UpdatePlant()
{
	if (!continue_flag)//�������Q���ѽ��l��ֹͣՈ�󣬸��Q�̅s�ѽ��M��ѭ�h����r
		return;

	for (short i = 0; i < map_row; ++i)
	{
		for (short j = 0; j < map_column; ++j)
		{
			Plant& target = map->yard[coordinate{ i, j }];
			coordinate tmp = map->yard.Table2Screen(coordinate{ i,j });

			if (target.ID() != plant_ID::None)
			{
				WriteScreenBuffer(DynamicLayer, target.name().c_str(), tmp, true);
			}
			else
			{
				string eraser(map_cell_length - 2, ' ');
				WriteScreenBuffer(DynamicLayer, eraser.c_str(), tmp, true);//���һ��
			}
		}
	}

}
void Display::UpdateBullet()
{
	if (!continue_flag)//�������Q���ѽ��l��ֹͣՈ�󣬸��Q�̅s�ѽ��M��ѭ�h����r
		return;
}

void Display::next()
{
	//new thread
	while(continue_flag)
	{
		PrintOnMouse();

		UpdateBullet();
		UpdatePlant();
		UpdateZombie();

		UpdateSun();
		UpdateStore();
		UpdateScore();

	}
}

//void Display::next()
//{
//		UpdateStore();
//		UpdateSun();
//		UpdateScore();
//}