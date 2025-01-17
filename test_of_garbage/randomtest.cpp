#include <iostream>
#include <random>

using namespace std;

int main(){
	 std::random_device rnd;     // 非決定的な乱数生成器でシード生成機を生成
     std::mt19937 mt(rnd()); //  メルセンヌツイスターの32ビット版、引数は初期シード
     //std::uniform_int_distribution<> rand100(0, 99);     // [0, 99] 範囲の一様乱数
     std::normal_distribution<> norm(0.0, 0.5);       // 平均50, 分散値10の正規分布
     for (int i  =  0; i < 20; ++i) {
	         //std::cout << rand100(mt) << "\n";
	         std::cout << norm(mt) << "\n";
     }
}
