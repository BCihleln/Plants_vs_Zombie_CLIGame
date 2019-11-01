#include "game_system.h"

GAME_SYSTEM::GAME_SYSTEM()
{
	this->score = 0;
	//mouse_position = { 0,0 };

	// ��ȡ��׼��������豸���
	this->hStdin = GetStdHandle(STD_INPUT_HANDLE);


	//HWND hwnd = GetForegroundWindow();
	//DWORD console_mode;
	//GetConsoleMode(hwnd, &console_mode);
	//console_mode &= ~ENABLE_QUICK_EDIT_MODE;  //�Ƴ����ٱ༭ģʽ
	//console_mode &= ~ENABLE_INSERT_MODE;      //�Ƴ�����ģʽ
	//console_mode &= ENABLE_MOUSE_INPUT;
	//SetConsoleMode(hwnd, console_mode);

}

GAME_SYSTEM::~GAME_SYSTEM()
{
	//HWND hwnd = GetForegroundWindow();
	//DWORD console_mode;
	//GetConsoleMode(hwnd, &console_mode);
	//console_mode &= ENABLE_QUICK_EDIT_MODE;  //��ԭ���ٱ༭ģʽ
	//console_mode &= ENABLE_INSERT_MODE;      //��ԭ����ģʽ
	//console_mode &= ~ENABLE_MOUSE_INPUT;
	//SetConsoleMode(hwnd, console_mode);

	CloseHandle(this->hStdin);  // �رձ�׼����豸���
}

int GAME_SYSTEM::get_input()
{
	while (1)
	{
		ReadConsoleInput(hStdin, &InputRecord, 1, &res);

		if (InputRecord.EventType == MOUSE_EVENT)
		{
			//if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			//{
			//	if (InputRecord.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
			//	{
			//		return 0;	// ���˫�� �˳�ѭ��
			//	}
			//}
			//this->mouse_position = InputRecord.Event.MouseEvent.dwMousePosition;
			coordinate mouse_position = InputRecord.Event.MouseEvent.dwMousePosition;
			display.SetMousePosition(mouse_position);
			interpret_mouse(InputRecord.Event.MouseEvent.dwButtonState);
		}
		else if (InputRecord.EventType == KEY_EVENT)
		{
			switch (interpret_key(InputRecord.Event.KeyEvent.wVirtualScanCode))
			{
			case 0:
			{
				//coordinate crHome = { 0,0 };
				//SetConsoleCursorPosition(this->hStdout, crHome);//��ʼ�������Ͻǣ����˴�ӡ������Z��
				//cout << "Capture mouse Mode End!\n";
				display.PrintOnMouse("Capture mouse Mode End!");
				display.ShowCursor();
				return 0;
			}
			default: break;
			}
		}

	}
	return 0;
}


int GAME_SYSTEM::interpret_key(DWORD target)
{//TODO: ����Р�
	//target �� �I�P����a��ʽ�����I�a��
	switch (target)
	{
	case 0x11/*w*/:case 0x48://�����I�� (int)72
		display.PrintOnXY("��", 0, 1);
		break;
	case 0x1e/*a*/:case 0x4b://�����I�� (int)75 
		display.PrintOnXY("��", 0, 1);
		break;
	case 0x1f/*s*/:case 0x50://�����I��
		display.PrintOnXY("��", 0, 1);
		break;
	case 0x20/*d*/:case 0x4d://�����I��
		display.PrintOnXY("��", 0, 1);
		break;
	case 0x01: //Esc
		display.PrintOnXY("Esc", 0, 1);
		return 0;
	case 0x12: //e
		display.PrintOnXY("e", 0, 1);
	default:
		display.PrintOnXY("Undefine key", 0, 1);
		break;
	}
	return 1;
}
void GAME_SYSTEM::interpret_mouse(DWORD target)
{//TODO : Activity Fillin
	static int click_amount = 0;
	switch (target)
	{
	case FROM_LEFT_1ST_BUTTON_PRESSED:			// ���
	{
		//Take or Place Item
		//FillConsoleOutputCharacter(this->hStdout, '1', 1, display.crPos, &this->res);
		//cout << 1;
		click_amount = (click_amount + 1) % 10;
		char a[2];
		sprintf(a, "%d", click_amount);
		display.PrintOnMouse(a);
		break;
	}

	case RIGHTMOST_BUTTON_PRESSED:				// �Ҽ�
	{
		//FillConsoleOutputCharacter(this->hStdout, '0', 1, display.crPos, &this->res);
		//cout << 0; 

		click_amount = (click_amount - 1 + 10) % 10;
		char a[10];
		sprintf(a, "%d", click_amount);
		display.PrintOnMouse(a);
		break;
	}

	default:
		//FillConsoleOutputCharacter(this->hStdout, 'X', 1, crPos, &res);
		display.PrintOnMouse("|--O--|");
		//display.PrintOnMouse("X");
		break;
	}
}