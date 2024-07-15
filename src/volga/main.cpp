#include <iostream>
#include <string>
#include "vm/vm.h"

using namespace std;
using namespace paulq::volga;

int main(){
	string name;
	volgavm vm = volgavm();
	cout << vm.hello() << '\n';
	cout << "What's your name?\n";
	cin >> name;
	cout << "Hello, " << name << "!\n";
}
