#include "game_system.h"

//#define TEST

int main(void)
{
	//TODO ��Q��
	GAME_SYSTEM game_system;
	//std::thread thrd(std::bind(&GAME_SYSTEM::get_input,game_system));
	//thrd.detach();
	while (true)
	{
		//int code = game_system.get_input();

		game_system.next();

		//if (code == 0)
		//	break;
	}


	return 0;
	//game_system.~GAME_SYSTEM();
	//exit(0);
		/*
		2019 11 02 return 0�e�`
		���r���@�����
		emmm ��return 0 ��Ԓ
			��return ֮ǰ����game_system��~game_system��
				�{��35��plant[5][7]������������
				֮�����������������ɆT
			�������ص�main �Kreturn 0
			���������Ҫ�˳��r�ƺ��z����game_system�ė��Ƿ񳬽磬
			Ȼ��͈��e���硭��
				Ŀǰ�^�쵽��game_system�������plants[5][7]�@��ɆT��Űl���@�ӵ��e�`
					ԭ���Ԡ�����ጷ��@���ɆT�r���{�������������^��35��
					���{ԇ��l�F�{�ôΔ�����
					��֪�����}������
			���ܵ�ԒҪ���R���Z����

		2019 11 03
		return 0 �֛]���e�`�ˡ�������Ī��������
		*/
}