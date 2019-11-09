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
			
			display.PrintOnMouse(selected_plant->name);
		}
		else//menu
		{
			//cout << "mode : player_mode::normal_play" << endl;
			display.PrintOnMouse("+");
		}
	/*TODO 根據模式切換鼠標移動時所顯示的東西
	menu、player_mode::normal_play：顯示“+”
	player_mode::selecting：顯示指標植物的cost -> 信息菜單：植物簡介、cost
	player_mode::selected：在種下植物前
						地圖範圍内始終顯示選中的植物名，
						地圖範圍外顯示out border
	*/

	break;
	}
	case signal::left_click:
	{
		if (mode == player_mode::normal)
		{
			//do nothing
		}
		else if (mode == player_mode::store_selecting)
		{
			if (store.in_table(mouse_position))//在商店範圍内左鍵選擇植物
			{
				selected_plant = store.SelectProducts(mouse_position);
				if (selected_plant->name != "None")//有選到商品
				{
					//mode = player_mode::map_selecting;
					selected = true;//-> 在下個時隙的mode_change函數中會更改模式
				}
			}
		}
		else//map_selecting
		{
			string Plant_State = map.PlantOnXY(selected_plant, mouse_position);//種植成功的話會返回所種植物的名字
				//TODO 修改植物冷卻時間
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
				display.PrintOnMouse(Plant_State);
			}
		}


		//if (store.in_table(mouse_position))//在商店範圍
		//{
		//	if (mode == player_mode::store_selecting)
		//	{
		//		selected_plant = store.SelectProducts(mouse_position);
		//		if (selected_plant != plant_ID::None)//有選到商品
		//		{
		//			mode = player_mode::map_selecting;
		//			selected = true;
		//		}
		//	}
		//}
		//else if (map.in_table(mouse_position))//在地圖範圍
		//{
		//	if (mode == player_mode::map_selecting)
		//	{
		//		string Plant_State = map.PlantOnXY(selected_pllant, mouse_position);//種植成功的話會返回所種植物的名字
		//		//TODO 修改植物冷卻時間
		//		if (Plant_State != "Out of Border" &&
		//			Plant_State != "Place already plant")
		//		{
		//			display.NewPlant(mouse_position, Plant_State);
		//			selected = false;
		//			mode = player_mode::normal;
		//			selected_plant = plant_ID::None;
		//		}
		//		else
		//		{
		//			display.PrintOnMouse(Plant_State);
		//		}
		//	}
		//}
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
	score(0), clock(0),
	mode(player_mode::normal),
	mouse(signal::move), mouse_position({ 0,0 }),
	key_stroke(0),
	display(map, store)
{
	// 获取标准输入输出设备句柄
	this->hStdin = GetStdHandle(STD_INPUT_HANDLE);

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
}

GAME_SYSTEM::~GAME_SYSTEM()
{
	//#ifdef DEBUG
	//	Sleep(1000);
	//	system("cls");
	//#endif
		//cout << "destructing GAME SYSTEM\n";
		//HWND hwnd = GetForegroundWindow();
		//DWORD console_mode;
		//GetConsoleMode(hwnd, &console_mode);
		//console_mode &= ENABLE_QUICK_EDIT_MODE;  //復原快速编辑模式
		//console_mode &= ENABLE_INSERT_MODE;      //復原插入模式
		//console_mode &= ~ENABLE_MOUSE_INPUT;
		//SetConsoleMode(hwnd, console_mode);

	CloseHandle(this->hStdin);  // 关闭标准输出设备句柄
}

int GAME_SYSTEM::get_input()
{//TODO 返回值設定
	ReadConsoleInput(hStdin, &InputRecord, 1, &res);

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
		return 1;
	}
	else if (InputRecord.EventType == KEY_EVENT)
	{
		key_stroke = interpret_key(InputRecord.Event.KeyEvent.wVirtualScanCode);
		switch (key_stroke)
		{
		case 0:
		{
			display.PrintOnMouse("Capture mouse Mode End!");
			display.ShowCursor();
			return 0;
		}
		default:
			break;
		}
		return 1;
	}
	return 1;
}

void GAME_SYSTEM::next()
{
	action();
	store.next();
	map.next();
	clock++;
}


int GAME_SYSTEM::interpret_key(DWORD target)
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
		display.PrintOnMouse("↑");
		return 1;
		break;
	case 0x1e/*a*/:case 0x4b://方向鍵左 (int)75 
		display.PrintOnMouse("←");
		return 3;
		break;
	case 0x1f/*s*/:case 0x50://方向鍵下
		display.PrintOnMouse("↓");
		return  2;
		break;
	case 0x20/*d*/:case 0x4d://方向鍵右
		display.PrintOnMouse("→");
		return 4;
		break;
	case 0x01: //Esc
		display.PrintOnMouse("Esc");
		return 0;
	case 0x12: //e
		display.PrintOnMouse("e");
		return 5;
	default:
		display.PrintOnMouse("Undefine key");
		return MAXINT;
	}
	return 0;
}
int GAME_SYSTEM::interpret_mouse(DWORD target)
{//TODO : 填充行爲（需要判斷當前模式）：商店買賣相關

 //static int click_amount = 0; 
	//switch (target)
	//{
	//case FROM_LEFT_1ST_BUTTON_PRESSED:			// 左键
	//{
	//	//Take or Place Item
	//	//FillConsoleOutputCharacter(this->hStdout, '1', 1, display.crPos, &this->res);
	//	//cout << 1;
	//	click_amount = (click_amount + 1) % 10;
	//	char a[2];
	//	sprintf(a, "%d", click_amount);
	//	display.PrintOnMouse(a);
	//	break;
	//}
	//
	//case RIGHTMOST_BUTTON_PRESSED:				// 右键
	//{
	//	//FillConsoleOutputCharacter(this->hStdout, '0', 1, display.crPos, &this->res);
	//	//cout << 0; 
	//
	//	click_amount = (click_amount - 1 + 10) % 10;
	//	char a[10];
	//	sprintf(a, "%d", click_amount);
	//	display.PrintOnMouse(a);
	//	break;
	//}
	//
	//default:
	//	//FillConsoleOutputCharacter(this->hStdout, 'X', 1, crPos, &res);
	//	display.PrintOnMouse("|--O--|");
	//	//display.PrintOnMouse("X");
	//	break;
	//}
	//return 1;

	//TODO 判斷鼠標所處範圍
	switch (target)
	{
	case FROM_LEFT_1ST_BUTTON_PRESSED:			// 左键
	{

		mouse = signal::left_click;

		//種植物模塊
		//TODO 根據商店所選擇種下相應植物
		//string Plant_State = map.PlantOnXY(Sun_Flower, position);//種植成功的話會返回所種植物的名字
		//if (Plant_State != "Out of Border" && 
		//	Plant_State != "Place already plant")
		//	display.NewPlant(position, Plant_State);
		//else
		//{
		//	display.PrintOnMouse(Plant_State); 
		//}

		//商店選擇模塊
		//string tmp = store.SelectProducts(position);
		//display.PrintOnMouse(tmp);
		break;
	}
	case RIGHTMOST_BUTTON_PRESSED:				// 右键
	{
		display.PrintOnMouse("Right Click");
		mouse = signal::right_click;
		break;
	}
	default://其他鼠標事件（滾輪相關、移動、其他案件）
	{
		mouse = signal::move;

		break;
	}
	}
	return 1;
}

//傳入position 用以判斷鼠標所在區域（商店區、地圖區、其他）
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
		if (in_store)
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

	//if (store.in_table(mouse_position))
	//{
	//	if (mode == player_mode::normal)
	//		mode = player_mode::store_selecting;
	//	//normal_selecting --> store_selecting
	//	//store_selecting --> store_selecting
	//	//map_selecting --> map_selecting (Out of Border)
	//	//cout << "mode : player_mode::selecting" << endl;
	//	//store.SelectProducts(position);
	//}
	//else if (map.in_table(mouse_position))
	//{
	//	if (mode == player_mode::store_selecting )//store_selecting or map_selecting
	//	{
	//		if (selected)//==true
	//			mode = player_mode::map_selecting;
	//		else//從商店移開，取消選擇
	//			mode = player_mode::normal;
	//	}
	//	
	//	//map_selecting --> map_selecting
	//	//normal --> normal
	//	//store_selecting+ selected(false) --> normal
	//	//store_selecting+ selected(true) --> map_selecting
	//
	//	//display.PrintOnMouse("player_mode::normal_play mode");
	//}
	//else//其他地區
	//{
	//	//normal --> normal
	//	//store_selecting+selected(false) --> normal
	//	//store_selecting+selected(true) --> map_selecting(Out of Border)
	//	//map_selecting --> map_selecting
	//	if (mode == player_mode::store_selecting && selected==false)
	//		mode = player_mode::normal;
	//}
	//cout << "Change to : " << (int)mode<<endl;
	//cout << "selected : " << selected << endl;
	//cout << "selected Plant : " << (int)selected_plant;
	//Sleep(500);
}