#include "pch.h"
#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdint>
#include <windows.h>
#include <thread>
#include <mutex>

using namespace std;

//std::mutex mtx;
int N = 0;

void ThreadA()
{
	std::mutex mtx;
	/*
	while (1) {
		cout << "A" << endl;
		Sleep(1000);
	}
	*/

	//mtx.lock();
	
	
	for (int i = 0; i < 10; i++) {
		
		N++;
		std::lock_guard<std::mutex> lock(mtx);
		cout << N << endl;
		
		Sleep(1000);
	}
	//mtx.unlock();
}

void ThreadB()
{
	cout << "B" << endl;
	Sleep(2000);
}

int main()
{
	mutex mtx1;

	std::thread th_a(ThreadA);
	//std::thread th_b(ThreadB);

	int NN = 0;
	for (int i = 0; i < 5; i++) {
		NN++;
		std::lock_guard<std::mutex> lock(mtx1);
		cout << i << "　最大5 C" << endl;
		Sleep(1000);

	}


	//th_a.join();//　join はその関数が終了するのを待つ 待つ
	th_a.detach();// 終わるのを待たないで次に進む

	NN = 0;

	for (int i = 0; i < 5; i++) {
		NN++;
		std::lock_guard<std::mutex> lock(mtx1);
		cout << i << "　最大5 CC" << endl;
		Sleep(2000);

	}

	cout << "N = " << N << endl;
	//th_b.join();

	return 0;
}