// [03]sサンプル.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <chrono>
#include <Windows.h>
#include <sstream>
#include <direct.h>
#include <math.h>

using namespace std;

std::mutex mtx1;
std::mutex mtx2;

//２次元の参照がめんどくさかったのでやりません

void vecvec1(vector<int> &a, vector<int> &b, vector<int> &c, int& i) {

	for (int j = 4; j < 8; j++) {

		std::lock_guard<std::mutex> lock(mtx1);
		a[i] = i;
		b[j] = j;
		c[j] = a[i] * b[j];

	}

}

void vecvec2(vector<int> &a, vector<int> &b, vector<int> &c, int& i) {

	for (int j =8; j < 12; j++) {

		std::lock_guard<std::mutex> lock(mtx1);
		a[i] = i;
		b[j] = j;
		c[j] = a[i] * b[j];

	}

}

void vecvec3(vector<int> &a, vector<int> &b, vector<int> &c, int& i) {

	for (int j = 12; j < 16; j++) {

		std::lock_guard<std::mutex> lock(mtx1);
		a[i] = i;
		b[j] = j;
		c[j] = a[i] * b[j];

	}

}


int main(int argc, char const *argv[]) {


	ofstream TIME("c sample.csv");


	vector<int> a(16);
	vector<int> b(16);
	vector<int> c(16);

	vector< vector<int> > cc(10, vector<int>(10));

	//このfor文は九九を並列処理で計算する内容である
	//ポイントとしては参照配列のためにvectorを使用する
	for (int i = 0; i < 16; i++) {

		//　iが毎回変更になるから　これを記述しただけで実行させる
		thread ththth1(vecvec1, ref(a), ref(b), ref(c), ref(i));
		thread ththth2(vecvec2, ref(a), ref(b), ref(c), ref(i));
		thread ththth3(vecvec3, ref(a), ref(b), ref(c), ref(i));

		for (int j = 0; j < 4; j++) {
			std::lock_guard<std::mutex> lock(mtx2);
			a[i] = i;
			b[j] = j;
			c[j] = a[i] * b[j];

		}

		//上記の処理が終わるまで先に進まず、thththは待機をしている
		ththth1.join();
		ththth2.join();
		ththth3.join();

		//正しく書き込まれているか確認
		for (int k = 0; k < 10; k++) {
			TIME << c[k] << endl;
			cout << "c[" << k << "] = " << c[k] << endl;
		}

		
	}



	return 0;
}
