#include "game_system.h"
#include <thread>
//C++ 11標準

#define TEST

#ifndef TEST
int main(void)
{
	//TODO 多綫程
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
		2019 11 02 return 0錯誤
		暫時先這樣頂著
		emmm 用return 0 的話
			在return 之前析構game_system，~game_system中
				調用35次plant[5][7]的析構函數，
				之後再依次析構其他成員
			正常返回到main 並return 0
			但最後程序要退出時似乎檢查了game_system的棧是否超界，
			然後就報錯超界……
				目前觀察到在game_system中添加了plants[5][7]這個類成員后才發生這樣的錯誤
					原本以爲是因爲釋放這個成員時，調用析構函數超過了35次
					逐步調試后發現調用次數正常
					不知道問題出在哪
			可能的話要看匯編語言了

		2019 11 03
		return 0 又沒有錯誤了……真是莫名其妙呢
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

	//t.detach();//子綫程由C++運行時庫控制，主綫程沒有控制權
	/*
	两个需要注意的地方
		主线程结束之后，子线程可能仍在运行（因而可以作为守护线程）；
		主线程结束伴随着资源销毁，需要保证子线程没有引用这些资源。
	*/

	//t.join() // 子綫程由主綫程控制
	/*如果选择接合子线程，则主线程会阻塞住，直到该子线程退出为止。
	这就好像将子线程尚未执行完的部分，接合在主线程的当前位置，而后顺序执行。*/

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
//	std::cout << t.hardware_concurrency() << std::endl;//可以并发执行多少个(不准确)
//	std::cout << "native_handle " << t.native_handle() << std::endl;//可以并发执行多少个(不准确)
//	t.join();
//	std::thread a(hello);
//	a.detach();
//	std::thread threads[5];                         // 默认构造线程
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
