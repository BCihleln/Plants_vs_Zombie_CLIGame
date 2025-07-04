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
	int i = start_position.Y;//SCREEN_BUFFER 访问行下标
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

		for (int j = 0; j < SCREEN_LENGTH; ++j)//替換掉getline過程中添加的\0
			if (MapLayer[i][j] == '\0')
				MapLayer[i][j] = tmp_line[j];

		//cout << SCREEN_BUFFER[position_y];
		i++;//下一行
	}
	delete[] tmp_line;//釋放暫時申請的内存
}

void Display::RefreshStdOut()
{
	//mutex.lock();
	 SetConsoleCursorPosition(hStdOut, { 0,0 });
	//system("cls"); cls會導致鼠標捕獲模式退出
	for (int i = 0; i <= SCREEN_WIDTH; ++i)
	{
		cout << DynamicLayer[i];//因爲是直接打印整個屏幕長度，不需要手動換行
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
//	{//因爲是直接打印整個屏幕長度，不需要手動換行
//		tmp.Y = i;
//		WriteConsoleOutputCharacterA(ConsoleScreenBuffer, SCREEN_BUFFER[i], SCREEN_LENGTH, tmp, &tmp2);
//	}
//}

//void Display::CleanMapCell(coordinate target_Cell)
//{
//	coordinate tmp = map->Table2Screen(target_Cell);
//	ReadDataFileToScreenBuff("mapcell.txt", tmp.X, tmp.Y);//TODO 不需要每次刷新時都讀文件
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
	this->hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//獲得標準輸出句柄
	//ConsoleScreenBuffer = CreateConsoleScreenBuffer(
	//	GENERIC_WRITE,//定義進程可以往緩衝區寫數據
	//	FILE_SHARE_WRITE,//定義緩衝區可共享寫權限
	//	NULL,
	//	CONSOLE_TEXTMODE_BUFFER,
	//	NULL
	//);

	//獲取標準輸出后才能設置窗口，順序不可顛倒
	window_init();
	screen_buffer_init();

	GetConsoleCursorInfo(hStdOut, &this->default_cursor);// 保存初始光標信息，便於恢復
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

	//更新屏幕綫程
	std::thread display_next(std::bind(&Display::next, this));//綫程綁定時傳入的是目標函數與該函數對象的地址
	
/*
之前在game_system中的bug就是忘記加取地址符，導致編譯器重新創建了一個Display的對象A，并把game_system中的display對象複製過去，然而display的SCREEN_BUFFER是主動申請的空間，A的SCREEN_BUFFER未經過初始化，指向了不該訪問的位置，導致錯誤
*/
	display_next.detach();
}

Display::~Display()
{
	continue_flag = false;
	mutex.lock();//等待其他綫程運作結束才析構對象

	for (int i = 0; i < SCREEN_WIDTH; ++i)
	{
		delete[] MapLayer[i];
		delete[] DynamicLayer[i];
	}
	delete[] MapLayer;
	delete[] DynamicLayer;
	CloseHandle(this->hStdOut);   // 关闭标准输入设备句柄
	ShowCursor();

	mutex.unlock();
}

//傳入最左側的起始位置(屏幕)，返回居中后的坐標
coordinate Display::middle(const string& target, coordinate left_side)
{
	int half_of_string = target.length() >> 1;//>>1 相當於/2
	short x = left_side.X - half_of_string;

	//避免邊角錯誤
	x = x > 0 ? x : 0;//左邊界
	x = left_side.X + half_of_string < SCREEN_LENGTH ? x : SCREEN_LENGTH - (short)target.length();//右邊界

	return { x,left_side.Y };
}


void Display::PrintOnMouse()
{
	mutex.lock();
	//SetConsoleActiveScreenBuffer(ConsoleScreenBuffer);

	RefreshStdOut();//清掉之前打印的鼠標打印的東西
	//string eraser(target.length(),' ');
	//if(last_MouseCursor_Y!=MouseCursor.Y)
		//PrintOnXY(eraser, middle(eraser, coordinate{ MouseCursor.X, last_MouseCursor_Y }));

	//讓要打印的内容出現在指標中間，也就是讓打印内容的中心處於指標位置
	SetConsoleCursorPosition(hStdOut, middle(MouseDisplay, MouseCursor));
	cout << MouseDisplay;
	SetConsoleCursorPosition(hStdOut, ScreenCursor);//維護屏幕光標

	mutex.unlock();
}
void Display::PrintOnXY(const string& target, coordinate position)
{
	if (position < coordinate{ 0,0 } || position > SCREEN_SIZE)//超界檢查
		return;
	//SetConsoleActiveScreenBuffer(ConsoleScreenBuffer);

	//mutex.lock();
	SetConsoleCursorPosition(hStdOut, coordinate{ 0,position.Y });//清理一行
	cout << MapLayer[position.Y];

	SetConsoleCursorPosition(hStdOut, position);
	cout << target;

	SetConsoleCursorPosition(hStdOut, ScreenCursor);//維護屏幕指針
}
void Display::PrintOnXY(const  coordinate& target, short x, short y)
{
	//mutex.lock();
	coordinate tmp = { x,y };
	SetConsoleCursorPosition(hStdOut, tmp);
	cout << target;
	//SetConsoleCursorPosition(hStdOut, ScreenCursor);//維護屏幕指針
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
	SetConsoleTitle(L"Plant VS Zombie"); // 設置窗口标题 前面的L代表寬字符
	HWND hwnd = GetForegroundWindow();
	
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
	//SCREEN_SIZE = SCREEN_SIZE - coordinate({ 0,1 });
	SCREEN_SIZE -= coordinate{0, 1};

}

void Display::screen_buffer_init()
{
	MapLayer = new char* [SCREEN_WIDTH+1];//建立屏幕輸出緩衝
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
	MapLayer[SCREEN_WIDTH ][SCREEN_LENGTH - 1] = '\0';//最後一行倒數第二位設置為\0防止打印滾動
	DynamicLayer[SCREEN_WIDTH ][SCREEN_LENGTH - 1] = '\0';//最後一行倒數第二位設置為\0防止打印滾動
}
void Display::WriteScreenBuffer(char* ScreenBuffer[],const char* target, coordinate position, bool middle_flag)
{
	if (middle_flag)
		position = middle(target, position);
	int length = strlen(target);
	if (position > SCREEN_SIZE || position < coordinate{0, 0})//邊界檢查
	{
		color(red);
		cout << __FUNCTION__ << " Out of range" << endl;
		cout << position;
		exit(0);
	}
	for (int i = 0; i < length && i+position.X < SCREEN_LENGTH-1; ++i)//終止條件包含橫坐標邊界檢查
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
		target = target - coordinate{1, 0};//防止最右下角打印時卷屏造成閃爍
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


//只有植物種植成功才調用
//void Display::NewPlant(coordinate screen_position, const string& name)
//{
//	//WriteScreenBuffer(DynamicLayer,name.c_str(), middle(name, map->Screen2Cell_middle(screen_position)));
//	WriteScreenBuffer(DynamicLayer,name.c_str(), map->Screen2Cell_middle(screen_position),true);
//}

void Display::UpdateStore()
{
	if (!continue_flag)//避免主綫程已經發出停止請求，副綫程卻已經進入循環的情況
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
			WriteScreenBuffer(DynamicLayer,"           ", position,true);//清空要打印的位置
			if (product_lefttime > 0)
			{
				WriteScreenBuffer(DynamicLayer,tmp, position,true);
			}
		}
}
void Display::UpdateSun()
{
	if (!continue_flag)//避免主綫程已經發出停止請求，副綫程卻已經進入循環的情況
		return;

	char tmp[10];
	sprintf(tmp, "%d", store->sun);
	WriteScreenBuffer(DynamicLayer,"              ", { 9,5 },true);
	WriteScreenBuffer(DynamicLayer,tmp, { 9,5 },true);
}
void Display::UpdateScore()
{
	if (!continue_flag)//避免主綫程已經發出停止請求，副綫程卻已經進入循環的情況
		return;

	char tmp[10];
	sprintf(tmp, "%d", *score);
	WriteScreenBuffer(DynamicLayer,tmp, { 138,4 },true);
}
void Display::UpdateZombie()
{
	if (!continue_flag)//避免主綫程已經發出停止請求，副綫程卻已經進入循環的情況
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
				WriteScreenBuffer(DynamicLayer, &MapLayer[zombie_position.Y][zombie_position.X], zombie_position,false);//清空一行
				WriteScreenBuffer(DynamicLayer,z.name().c_str(), zombie_position,false);
			}
		}
	}
	//mutex.unlock();
}
void Display::UpdatePlant()
{
	if (!continue_flag)//避免主綫程已經發出停止請求，副綫程卻已經進入循環的情況
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
				WriteScreenBuffer(DynamicLayer, eraser.c_str(), tmp, true);//清空一行
			}
		}
	}

}
void Display::UpdateBullet()
{
	if (!continue_flag)//避免主綫程已經發出停止請求，副綫程卻已經進入循環的情況
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