#include "game_system.h"
//根據這個時隙發生的輸入事件與系統狀態，做出相應動作
void GAME_SYSTEM::action()
{
	//mode, mouse, mouse_position, key_stroke
	/* mode
	normal_play ：特定字母、鼠標移動到商店區域 -> selecting mode
	selecting ：
		上下左右wasd、左鍵選擇選項
		商店範圍内左鍵且滿足選中條件 -> selected mode
		esc鍵 -> normal mode
	selected ：鼠標上打印選中物
		地圖範圍内 左鍵（放置選中物） -> normal_play mode
		右鍵 取消選中 -> normal_play mode
	*/
	switch (mouse)
	{
	case signal::move:
	{
		if (mode == player_mode::map_selecting)
		{
			//cout << "mode : player_mode::selected" << endl;
			
			display.MouseDisplay = selected_plant->name();
		}
		else
		{
			//cout << "mode : player_mode::normal_play" << endl;
			display.MouseDisplay = "+";
		}

	break;
	}
	case signal::left_click:
	{
		if (mode == player_mode::normal)
		{
			display.MouseDisplay = "+";
		}
		else if (mode == player_mode::store_selecting)
		{
			selected_plant = store.SelectProducts(mouse_position);
			if (selected_plant && selected_plant->ID()!=plant_ID::None)//有選到商品，非空指針
			{
				selected = true;
				display.MouseDisplay = selected_plant->name();
			}
			//else
			//	display.MouseDisplay = "+";
		}
		else//map_selecting
		{
			string Plant_State = map.PlantOnXY(selected_plant, mouse_position);
			//種植成功的話會返回所種植物的名字
			if (Plant_State != "Out of Border" &&
				Plant_State != "Place already plant")
			{
				store.buy();
				display.NewPlant(mouse_position, Plant_State);
				selected = false;
				mode = player_mode::normal;
				selected_plant = nullptr;
			}
			else
			{
				display.MouseDisplay = Plant_State;
			}
		}
		break;
	}
	case signal::right_click:
	{
		//右鍵取消種植
		if (mode == player_mode::map_selecting)
		{
			selected = false;
			selected_plant = nullptr;
		}
		break;
	}
	}
}

GAME_SYSTEM::GAME_SYSTEM() :
	hStdin(GetStdHandle(STD_INPUT_HANDLE)),	// 获取标准输入输出设备句柄
	score(0),
	continued_flag(true),
	game_clock(0),
	mode(player_mode::normal),
	mouse(signal::move), mouse_position({ 0,0 }),
	key_stroke(0),
	selected(false), selected_plant(nullptr),
	display(map, store,&score)
{
	srand((unsigned)time(NULL));//隨機數初始化

	//貌似沒什麽用處……
	HWND hwnd = GetForegroundWindow();
	DWORD console_mode;
	//GetConsoleMode(hwnd, &console_mode);
	GetConsoleMode(hStdin, &console_mode);
	console_mode &= ~ENABLE_QUICK_EDIT_MODE;  //移除快速编辑模式
	console_mode &= ~ENABLE_INSERT_MODE;      //移除插入模式
	console_mode &= ENABLE_MOUSE_INPUT;
	//SetConsoleMode(hwnd, console_mode);
	SetConsoleMode(hStdin, console_mode);

	std::thread deal_input(std::bind(&GAME_SYSTEM::get_input,this));//開新綫程
	deal_input.detach();

	//CloseHandle(hStdin);  // 关闭标准输出设备句柄
}

GAME_SYSTEM::~GAME_SYSTEM()
{
		//cout << "destructing GAME SYSTEM\n";
		HWND hwnd = GetForegroundWindow();
		DWORD console_mode;
		GetConsoleMode(hwnd, &console_mode);
		console_mode &= ENABLE_QUICK_EDIT_MODE;  //復原快速编辑模式
		console_mode &= ENABLE_INSERT_MODE;      //復原插入模式
		console_mode &= ~ENABLE_MOUSE_INPUT;
		SetConsoleMode(hwnd, console_mode);

	//CloseHandle(this->hStdin);  // 关闭标准输出设备句柄
}

int GAME_SYSTEM::get_input()
{//TODO 返回值設定

		INPUT_RECORD	InputRecord;//Input Buffer	
		DWORD				res;//IpNumbersOfEventsRead 讀取到的行爲數量

	//New Thread
	while (continued_flag)
	{
		ReadConsoleInput(hStdin, &InputRecord, 1, &res);//阻塞捕獲信號
		//PeekConsoleInput(hStdin, &InputRecord, 1, &res);
		if (InputRecord.EventType == MOUSE_EVENT)
		{
			//if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			//{
			//	if (InputRecord.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
			//	{
			//		return 0;	// 左键双击 退出循环
			//	}
			//}
			mouse_position = InputRecord.Event.MouseEvent.dwMousePosition;
			mode_change();
			display.SetMousePosition(mouse_position);
			interpret_mouse(InputRecord.Event.MouseEvent.dwButtonState);

			//break;
		}
		else if (InputRecord.EventType == KEY_EVENT)
		{
			key_stroke = interpret_key(InputRecord.Event.KeyEvent.wVirtualScanCode);
			switch (key_stroke)
			{
			case 0:
			{
				display.MouseDisplay="Capture mouse Mode End!";
				display.ShowCursor();
				display.continue_flag = continued_flag = false;
			}
			default:
				break;
			}
		}
		//action();
		//FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));//清掉之前的輸入緩衝信息
	}
	//should never be reach
	return 0;
}

bool GAME_SYSTEM::next()
{
	action();
	static clock_t clock_start = clock();

	clock_t duration = clock() - clock_start;
	if(duration>game_speed)
	{
		game_clock +=1;//时钟同步一毫秒
		clock_start = clock();

		int SunFlower_amount = map.next(game_clock);
		if (SunFlower_amount == MAXINT)//僵尸抵達地圖最左側
		{
			display.continue_flag = continued_flag = false;//游戲結束
		}
		store.next(game_clock, SunFlower_amount);
	}
	//display.next();
	return continued_flag;
}


char GAME_SYSTEM::interpret_key(DWORD target)
{//TODO: 填充行爲，商店買賣

	/*
	esc退出 0
	上下左右 1、2、3、4
	商店 5
	*/
	//target 為 鍵盤掃描碼形式（非鍵碼）
	switch (target)
	{
	case 0x11/*w*/:case 0x48://方向鍵上 (int)72
		display.MouseDisplay = "↑";
		return 'w';
		break;
	case 0x1e/*a*/:case 0x4b://方向鍵左 (int)75 
		display.MouseDisplay = "←";
		return 'a';
		break;
	case 0x1f/*s*/:case 0x50://方向鍵下
		display.MouseDisplay = "↓";
		return  's';
		break;
	case 0x20/*d*/:case 0x4d://方向鍵右
		display.MouseDisplay = "→";
		return 'd';
		break;
	case 0x01: //Esc
		display.MouseDisplay = "Esc";
		return '\0';
	case 0x12: //e
		display.MouseDisplay = "e";
		return 'e';
	default:
		display.MouseDisplay = "Undefine key";
		return MAXCHAR;
	}
	return 0;
}
void GAME_SYSTEM::interpret_mouse(DWORD target)
{
	switch (target)
	{
	case FROM_LEFT_1ST_BUTTON_PRESSED:			// 左键
		mouse = signal::left_click;
		return;

	case RIGHTMOST_BUTTON_PRESSED:				// 右键
		mouse = signal::right_click;
		return;

	default://其他鼠標事件（滾輪相關、移動、其他案件）
		mouse = signal::move;
		return;
	}
}

void GAME_SYSTEM::mode_change()
{
	//TODO 鍵盤狀況加入
	//cout << "Last mode : " << (int)mode<<endl;

	bool in_store = store.in_table(mouse_position);
	//bool in_map = map.in_table(mouse_position);
	switch (mode)
	{
	case player_mode::normal:
	{
		if (in_store || key_stroke=='e')
			mode = player_mode::store_selecting;
		return;
		//break;
	}
	case player_mode::store_selecting:
	{
		if (selected)
			mode = player_mode::map_selecting;
		else if (!in_store)//沒有選中並移開商店區
		{
			mode = player_mode::normal;
		}
		return;
		//break;
	}
	case player_mode::map_selecting:
	{
		if (!selected)//取消選擇
			mode = player_mode::normal;
		return;
		//break;
	}
	}
	//cout << "Change to : " << (int)mode<<endl;
	//cout << "selected : " << selected << endl;
	//cout << "selected Plant : " << (int)selected_plant;
	//Sleep(500);
}