#include "game_system.h"
#include <thread>
//C++ 11�˜�

#define TEST

#ifndef TEST
int main(void)
{
	//TODO ��Q��
	GAME_SYSTEM game_system;
	while (true)
	{
		int code = game_system.get_input();

		game_system.next();

		if (code == 0)
			break;
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
#else

void HI(int i)
{
	cout << i << endl;
}


int main()
{
	//thread t{ HI };

	//t.detach();//�ӾQ����C++�\�Еr����ƣ����Q�̛]�п��ƙ�
	/*
	������Ҫע��ĵط�
		���߳̽���֮�����߳̿����������У����������Ϊ�ػ��̣߳���
		���߳̽�����������Դ���٣���Ҫ��֤���߳�û��������Щ��Դ��
	*/

	//t.join() // �ӾQ�������Q�̿���
	/*���ѡ��Ӻ����̣߳������̻߳�����ס��ֱ�������߳��˳�Ϊֹ��
	��ͺ������߳���δִ����Ĳ��֣��Ӻ������̵߳ĵ�ǰλ�ã�����˳��ִ�С�*/

	for (int i = 0; i < 4; i++)
	{
		thread t{ HI, i };
		t.detach();
	}
}

//std::thread::id main_thread_id = std::this_thread::get_id();
//
//void hello()
//{
//	std::cout << "Hello Concurrent World\n";
//	if (main_thread_id == std::this_thread::get_id())
//		std::cout << "This is the main thread.\n";
//	else
//		std::cout << "This is not the main thread.\n";
//}
//
//void pause_thread(int n) {
//	std::this_thread::sleep_for(std::chrono::seconds(n));
//	std::cout << "pause of " << n << " seconds ended\n";
//}
//
//int main() {
//	std::thread t(hello);
//	std::cout << t.hardware_concurrency() << std::endl;//���Բ���ִ�ж��ٸ�(��׼ȷ)
//	std::cout << "native_handle " << t.native_handle() << std::endl;//���Բ���ִ�ж��ٸ�(��׼ȷ)
//	t.join();
//	std::thread a(hello);
//	a.detach();
//	std::thread threads[5];                         // Ĭ�Ϲ����߳�
//
//	std::cout << "Spawning 5 threads...\n";
//	for (int i = 0; i < 5; ++i)
//		threads[i] = std::thread(pause_thread, i + 1);   // move-assign threads
//	std::cout << "Done spawning threads. Now waiting for them to join:\n";
//	for (auto& thread : threads)
//		thread.join();
//	std::cout << "All threads joined!\n";
//}

#endif
