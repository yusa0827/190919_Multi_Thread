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

void work(int &num) {
	for (int i = 0; i < 10; i++) {
		num++;
	}
}


void sumvec(vector<int> &vec) {

	for (int i = 0; i < vec.size(); ++i) {
		vec[i] += 3;
	}

}
		
void vecvec(vector<int> &a, vector<int> &b, vector<int> &c,int& i){

	for (int j = 5; j < 10; j++) {

		std::lock_guard<std::mutex> lock(mtx1);
		a[i] = i;
		b[j] = j;
		c[j] = a[i] * b[j];
		


		//cout<<"c[" << j << "] = " << c[j] << endl;
		
		//Sleep(1500);//待機

	}



}




int main(int argc, char const *argv[]) {

	/*
	int num = 200;
	thread th(work, ref(num));
	cout << num << endl;
	th.join();
	cout << num << endl;
	*/
	ofstream TIME("c sample.csv");

	vector<int> a(10);
	vector<int> b(10);
	vector<int> c(10);
	


	std::vector<int> vec(2);
	//sumvec(vec);
	
	//配列の参照はベクター型で完成する
	//thread thth(sumvec, ref(vec));
	//cout << vec[1] << endl;


	//for文内を二分割のマルチスレッドを行う場合
	//マルスレをどのように使いたいかを確認する
	//[問題点]　マルスレで得た値を使用したい
	

	for (int i = 0; i < 10; i++) {

		//　iが毎回変更になるから　これを記述しただけで実行させる
		thread ththth(vecvec, ref(a), ref(b), ref(c), ref(i));


		for (int j = 0; j < 5; j++) {
			std::lock_guard<std::mutex> lock(mtx2);
			a[i] = i;
			b[j] = j;
			c[j] = a[i] * b[j];
			
			//cout << "c[" << j << "] = " << c[j] << endl;
			//Sleep(2000);
		}

		
		ththth.join();



		//cout << "i = " << i << endl;
		
		for (int k = 0; k < 10; k++) {
			TIME << c[k] << endl;
			cout << "c["<<k<<"] = " << c[k] << endl;
		}

		//cout << "c[" << 3 << "] = " << c[3] << endl;
		//cout << "c[" << 6 << "] = " << c[6] << endl;
	}



	return 0;
}

/*
//配列ってどうやるんだっけｗ
void half(int&i, int &b[10]) {

	int a[10] = { 0 };
	int b[10] = { 0 };
	int m = 0;
	int c[10] = { 0 };
	for (int j = 5; j < 10; j++) {


		m = i;
		b[j] = j;
		c[j] = a[i] * b[j];
		Sleep(2000);

		/*
		a[i] = i;
		b[j] = j;
		c[j] = a[i] * b[j];
		Sleep(2000);
	
	*/
/*
	}
}

*/