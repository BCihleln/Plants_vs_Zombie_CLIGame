#include "game_system.h"

GAME_SYSTEM::GAME_SYSTEM() :
	score(0), clock(0),
	mode(normal_play)//TODO 暫時先初始化為普通游玩
{
	// 获取标准输入输出设备句柄
	this->hStdin = GetStdHandle(STD_INPUT_HANDLE);

	//貌似沒什麽用處……
	//HWND hwnd = GetForegroundWindow();
	//DWORD console_mode;
	//GetConsoleMode(hwnd, &console_mode);
	//console_mode &= ~ENABLE_QUICK_EDIT_MODE;  //移除快速编辑模式
	//console_mode &= ~ENABLE_INSERT_MODE;      //移除插入模式
	//console_mode &= ENABLE_MOUSE_INPUT;
	//SetConsoleMode(hwnd, console_mode);
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
		coordinate mouse_position = InputRecord.Event.MouseEvent.dwMousePosition;
		interpret_position_set_mode(mouse_position);
		display.SetMousePosition(mouse_position);
		interpret_mouse(InputRecord.Event.MouseEvent.dwButtonState,mouse_position);
		return 1;
	}
	else if (InputRecord.EventType == KEY_EVENT)
	{
		switch (interpret_key(InputRecord.Event.KeyEvent.wVirtualScanCode))
		{
		case 0:
		{
			display.PrintOnMouse("Capture mouse Mode End!");
			display.ShowCursor();
			return 0;
		}
		default: break;
		}
		return 1;
	}
	return 1;
}


int GAME_SYSTEM::interpret_key(DWORD target)
{//TODO: 填充行爲，商店買賣
	//target 為 鍵盤掃描碼形式（非鍵碼）
	switch (target)
	{
	case 0x11/*w*/:case 0x48://方向鍵上 (int)72
		display.PrintOnMouse("↑");
		break;
	case 0x1e/*a*/:case 0x4b://方向鍵左 (int)75 
		display.PrintOnMouse("←");
		break;
	case 0x1f/*s*/:case 0x50://方向鍵下
		display.PrintOnMouse("↓");
		break;
	case 0x20/*d*/:case 0x4d://方向鍵右
		display.PrintOnMouse("→");
		break;
	case 0x01: //Esc
		display.PrintOnMouse("Esc");
		return 0;
	case 0x12: //e
		display.PrintOnMouse("e");
	default:
		display.PrintOnMouse("Undefine key");
		break;
	}
	return 1;
}
int GAME_SYSTEM::interpret_mouse(DWORD target,coordinate position)
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

	switch (target)
	{
	case FROM_LEFT_1ST_BUTTON_PRESSED:			// 左键
	{
		//display.PrintOnMouse("Left Click");
		map.PlantOnXY(Sun_Flower,position);
		
		display.NewPlant(Sun_Flower,position );
		break;
	}

	case RIGHTMOST_BUTTON_PRESSED:				// 右键
	{
		display.PrintOnMouse("Right Click");
		break;
	}

	default:
	{
		display.PrintOnMouse("O");
		break;
	}
	}	
	return 1;
}
void GAME_SYSTEM::interpret_position_set_mode(coordinate position)//傳入position 用以判斷鼠標所在區域（商店區、地圖區、其他）
{
	if (position.X < 127 && position.Y < 10)//TODO 待用變量形式更替
	{
		mode = selecting;
		store.select(position);
	}
	else if(position.X <127 && position.Y <60)
	{
		mode = normal_play;
		map.select(position);
		//display.PrintOnMouse("normal_play mode");
	}
}