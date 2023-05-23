/*
 * main.cpp
 *
 *  Created on: 2 Sep 2020
 *      Author: Kevin Vo Le
 */
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
#include "Key_Generator.h"
#include "S-DES.h"
#include "Global_Actions.h"

int input_size = 10;
int p_value_10 = 10;
int p_value_8 = 8;

int main(){
	char option;
	cout << "Enter an option:\n";
	cout << "a) Encryption\nb) Decryption " <<endl;
	cin >> option;
	if(option == 'a'){
		DES des;
		des.encrypt();
	}
	if(option == 'b'){
		DES des;
		des.decrpyt();
	}
	return 0;
}
