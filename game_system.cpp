#include "game_system.h"
//�����@���r϶�l����ݔ���¼��cϵ�y��B��������������
void GAME_SYSTEM::action()
{
	//mode, mouse, mouse_position, key_stroke
	/* mode
	normal_play ���ض���ĸ������Ƅӵ��̵�^�� -> selecting mode
	selecting ��
		��������wasd�����I�x���x�
		�̵깠�������I�ҝM���x�Зl�� -> selected mode
		esc�I -> normal mode
	selected ������ϴ�ӡ�x����
		�؈D������ ���I�������x��� -> normal_play mode
		���I ȡ���x�� -> normal_play mode
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
			if (selected_plant && selected_plant->ID()!=plant_ID::None)//���x����Ʒ���ǿ�ָ�
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
			//�Nֲ�ɹ���Ԓ���������Nֲ�������
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
		//���Iȡ���Nֲ
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
	hStdin(GetStdHandle(STD_INPUT_HANDLE)),	// ��ȡ��׼��������豸���
	score(0),
	continued_flag(true),
	game_clock(0),
	mode(player_mode::normal),
	mouse(signal::move), mouse_position({ 0,0 }),
	key_stroke(0),
	selected(false), selected_plant(nullptr),
	display(map, store,&score)
{
	srand((unsigned)time(NULL));//�S�C����ʼ��

	//ò�ƛ]ʲ����̎����
	HWND hwnd = GetForegroundWindow();
	DWORD console_mode;
	//GetConsoleMode(hwnd, &console_mode);
	GetConsoleMode(hStdin, &console_mode);
	console_mode &= ~ENABLE_QUICK_EDIT_MODE;  //�Ƴ����ٱ༭ģʽ
	console_mode &= ~ENABLE_INSERT_MODE;      //�Ƴ�����ģʽ
	console_mode &= ENABLE_MOUSE_INPUT;
	//SetConsoleMode(hwnd, console_mode);
	SetConsoleMode(hStdin, console_mode);

	std::thread deal_input(std::bind(&GAME_SYSTEM::get_input,this));//�_�¾Q��
	deal_input.detach();

	//CloseHandle(hStdin);  // �رձ�׼����豸���
}

GAME_SYSTEM::~GAME_SYSTEM()
{
		//cout << "destructing GAME SYSTEM\n";
		HWND hwnd = GetForegroundWindow();
		DWORD console_mode;
		GetConsoleMode(hwnd, &console_mode);
		console_mode &= ENABLE_QUICK_EDIT_MODE;  //��ԭ���ٱ༭ģʽ
		console_mode &= ENABLE_INSERT_MODE;      //��ԭ����ģʽ
		console_mode &= ~ENABLE_MOUSE_INPUT;
		SetConsoleMode(hwnd, console_mode);

	//CloseHandle(this->hStdin);  // �رձ�׼����豸���
}

int GAME_SYSTEM::get_input()
{//TODO ����ֵ�O��

		INPUT_RECORD	InputRecord;//Input Buffer	
		DWORD				res;//IpNumbersOfEventsRead �xȡ�����Р�����

	//New Thread
	while (continued_flag)
	{
		ReadConsoleInput(hStdin, &InputRecord, 1, &res);//�������@��̖
		//PeekConsoleInput(hStdin, &InputRecord, 1, &res);
		if (InputRecord.EventType == MOUSE_EVENT)
		{
			//if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			//{
			//	if (InputRecord.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
			//	{
			//		return 0;	// ���˫�� �˳�ѭ��
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
		//FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));//���֮ǰ��ݔ�뾏�n��Ϣ
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
		game_clock +=1;//ʱ��ͬ��һ����
		clock_start = clock();

		int SunFlower_amount = map.next(game_clock);
		if (SunFlower_amount == MAXINT)//��ʬ���_�؈D�����
		{
			display.continue_flag = continued_flag = false;//�Α�Y��
		}
		store.next(game_clock, SunFlower_amount);
	}
	//display.next();
	return continued_flag;
}


char GAME_SYSTEM::interpret_key(DWORD target)
{//TODO: ����Р����̵��I�u

	/*
	esc�˳� 0
	�������� 1��2��3��4
	�̵� 5
	*/
	//target �� �I�P����a��ʽ�����I�a��
	switch (target)
	{
	case 0x11/*w*/:case 0x48://�����I�� (int)72
		display.MouseDisplay = "��";
		return 'w';
		break;
	case 0x1e/*a*/:case 0x4b://�����I�� (int)75 
		display.MouseDisplay = "��";
		return 'a';
		break;
	case 0x1f/*s*/:case 0x50://�����I��
		display.MouseDisplay = "��";
		return  's';
		break;
	case 0x20/*d*/:case 0x4d://�����I��
		display.MouseDisplay = "��";
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
	case FROM_LEFT_1ST_BUTTON_PRESSED:			// ���
		mouse = signal::left_click;
		return;

	case RIGHTMOST_BUTTON_PRESSED:				// �Ҽ�
		mouse = signal::right_click;
		return;

	default://��������¼����L݆���P���Ƅӡ�����������
		mouse = signal::move;
		return;
	}
}

void GAME_SYSTEM::mode_change()
{
	//TODO �I�P��r����
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
		else if (!in_store)//�]���x�ЁK���_�̵�^
		{
			mode = player_mode::normal;
		}
		return;
		//break;
	}
	case player_mode::map_selecting:
	{
		if (!selected)//ȡ���x��
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