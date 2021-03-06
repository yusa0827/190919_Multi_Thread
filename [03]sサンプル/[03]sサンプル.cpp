// [03]sサンプル.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include <thread>

using namespace std;

void work(int &num) {
	for (int i = 0; i < 10; i++) {
		num++;
	}
}

int main(int argc, char const *argv[]) {
	int num = 200;
	thread th(work, ref(num));
	cout << num << endl;
	th.join();
	cout << num << endl;
	return 0;
}