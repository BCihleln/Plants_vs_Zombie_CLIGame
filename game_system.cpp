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
			
			display.PrintOnMouse(selected_plant->name);
		}
		else//menu
		{
			//cout << "mode : player_mode::normal_play" << endl;
			display.PrintOnMouse("+");
		}
	/*TODO ����ģʽ�ГQ����Ƅӕr���@ʾ�Ė|��
	menu��player_mode::normal_play���@ʾ��+��
	player_mode::selecting���@ʾָ��ֲ���cost -> ��Ϣ�ˆΣ�ֲ�ﺆ�顢cost
	player_mode::selected���ڷN��ֲ��ǰ
						�؈D������ʼ�K�@ʾ�x�е�ֲ������
						�؈D�������@ʾout border
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
			if (store.in_table(mouse_position))//���̵깠�������I�x��ֲ��
			{
				selected_plant = store.SelectProducts(mouse_position);
				if (selected_plant->name != "None")//���x����Ʒ
				{
					//mode = player_mode::map_selecting;
					selected = true;//-> �����r϶��mode_change�����Е�����ģʽ
				}
			}
		}
		else//map_selecting
		{
			string Plant_State = map.PlantOnXY(selected_plant, mouse_position);//�Nֲ�ɹ���Ԓ���������Nֲ�������
				//TODO �޸�ֲ����s�r�g
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


		//if (store.in_table(mouse_position))//���̵깠��
		//{
		//	if (mode == player_mode::store_selecting)
		//	{
		//		selected_plant = store.SelectProducts(mouse_position);
		//		if (selected_plant != plant_ID::None)//���x����Ʒ
		//		{
		//			mode = player_mode::map_selecting;
		//			selected = true;
		//		}
		//	}
		//}
		//else if (map.in_table(mouse_position))//�ڵ؈D����
		//{
		//	if (mode == player_mode::map_selecting)
		//	{
		//		string Plant_State = map.PlantOnXY(selected_pllant, mouse_position);//�Nֲ�ɹ���Ԓ���������Nֲ�������
		//		//TODO �޸�ֲ����s�r�g
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
	score(0), clock(0),
	mode(player_mode::normal),
	mouse(signal::move), mouse_position({ 0,0 }),
	key_stroke(0),
	display(map, store)
{
	// ��ȡ��׼��������豸���
	this->hStdin = GetStdHandle(STD_INPUT_HANDLE);

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
		//console_mode &= ENABLE_QUICK_EDIT_MODE;  //��ԭ���ٱ༭ģʽ
		//console_mode &= ENABLE_INSERT_MODE;      //��ԭ����ģʽ
		//console_mode &= ~ENABLE_MOUSE_INPUT;
		//SetConsoleMode(hwnd, console_mode);

	CloseHandle(this->hStdin);  // �رձ�׼����豸���
}

int GAME_SYSTEM::get_input()
{//TODO ����ֵ�O��
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
		display.PrintOnMouse("��");
		return 1;
		break;
	case 0x1e/*a*/:case 0x4b://�����I�� (int)75 
		display.PrintOnMouse("��");
		return 3;
		break;
	case 0x1f/*s*/:case 0x50://�����I��
		display.PrintOnMouse("��");
		return  2;
		break;
	case 0x20/*d*/:case 0x4d://�����I��
		display.PrintOnMouse("��");
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
{//TODO : ����Р�����Ҫ�Дஔǰģʽ�����̵��I�u���P

 //static int click_amount = 0; 
	//switch (target)
	//{
	//case FROM_LEFT_1ST_BUTTON_PRESSED:			// ���
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
	//case RIGHTMOST_BUTTON_PRESSED:				// �Ҽ�
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

	//TODO �Д������̎����
	switch (target)
	{
	case FROM_LEFT_1ST_BUTTON_PRESSED:			// ���
	{

		mouse = signal::left_click;

		//�Nֲ��ģ�K
		//TODO �����̵����x��N������ֲ��
		//string Plant_State = map.PlantOnXY(Sun_Flower, position);//�Nֲ�ɹ���Ԓ���������Nֲ�������
		//if (Plant_State != "Out of Border" && 
		//	Plant_State != "Place already plant")
		//	display.NewPlant(position, Plant_State);
		//else
		//{
		//	display.PrintOnMouse(Plant_State); 
		//}

		//�̵��x��ģ�K
		//string tmp = store.SelectProducts(position);
		//display.PrintOnMouse(tmp);
		break;
	}
	case RIGHTMOST_BUTTON_PRESSED:				// �Ҽ�
	{
		display.PrintOnMouse("Right Click");
		mouse = signal::right_click;
		break;
	}
	default://��������¼����L݆���P���Ƅӡ�����������
	{
		mouse = signal::move;

		break;
	}
	}
	return 1;
}

//����position �����Д�������څ^���̵�^���؈D�^��������
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
		if (in_store)
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
	//		else//���̵����_��ȡ���x��
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
	//else//�����؅^
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