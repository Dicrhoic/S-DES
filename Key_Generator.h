/*
 * Key_Generator.h
 *
 *  Created on: 2 Sep 2020
 *      Author: 19396431- Kevin Vo Le
 */

#ifndef KEY_GENERATOR_H_
#define KEY_GENERATOR_H_
#include "Global_Actions.h"

class key_generator {
private:
	int P10_list[10] = { 2, 4, 1, 6, 3, 9, 0, 8, 7, 5 };
	int P8_list[10] = { 5, 2, 6, 3, 7, 4, 9, 8 };

public:
	vector<int> keyInput;
	int key_1 = 0, key_2 = 0;
	string key1, key2;
	string intial_key_input;
	vector<int> P8_i, P8_f;
	vector<int> LS_1, LS_2, K1, K2, P10;
	key_generator() {
		cout << "Enter the 10 bit key" << endl;
		cin >> intial_key_input;
		//cout << "Entered: " <<intial_key_input << endl;
	}
	void getKey(){
		cout << "Enter the 10 bit key" << endl;
		cin >> intial_key_input;
	}
	void generateKey() {
		storeInputAsVector(keyInput, intial_key_input);
//		cout << "Applying P10: " << endl;
		applyP10_key();
//		cout << "Left Shift: " << endl;
		leftShift_1();
//		cout << "applying P8" << endl;
		applyP8(P8_i, LS_1);
		key1 = convertToString(P8_i);
//		cout << "Left Shift 2: " << endl;
		leftShift_2(LS_1);
//		cout << "applying P8" << endl;
		applyP8(P8_f, LS_2);
		key2 = convertToString(P8_f);
		cout << "Key 1: " << key1 << endl;
		cout << "Key 2: " << key2 << endl;
	}


	void applyP10_key() {
		for (int i = 0; i < 10; i++) {
			P10.push_back(keyInput.at(P10_list[i]));
		}
//		printVecDebug(P10);
	}
	void leftShift_1() {
		vector<int> first_half, second_half;
		/*
		 * Create two vectors (halves) to left shift first
		 */
		for (unsigned i = 0; i < (P10.size() / 2); i++) {
			first_half.push_back(P10.at(i));
		}
		for (unsigned i = 5; i < (P10.size()); i++) {
			second_half.push_back(P10.at(i));
		}
		/*
		 *	 Left shift first element of both vectors
		 */
		//temp storages for the first values
		int first_half_element, second_half_element;
		//first half LS-1
		first_half_element = first_half.at(0);
		//remove the first element
		first_half.erase(first_half.begin());
		first_half.push_back(first_half_element);
		//repeat for the second half
		second_half_element = second_half.at(0);
		second_half.erase(second_half.begin());
		second_half.push_back(second_half_element);
		//Consecrate the halves into LS-1
		LS_1.reserve(first_half.size() + first_half.size()); // preallocate memory
		LS_1.insert(LS_1.end(), first_half.begin(), first_half.end());
		LS_1.insert(LS_1.end(), second_half.begin(), second_half.end());
//		cout << "LS1: ";
//		printVecDebug(LS_1);
		//
	}

	void applyP8(vector<int> &p8List, vector<int> LS) {
		for (int i = 0; i < 8; i++) {
			//cout << LS.at(P8_list[i]);
			p8List.push_back(LS.at(P8_list[i]));
		}
		cout << "P8: ";
		printVecDebug(p8List);
	}

	void leftShift_2(vector<int> LS_1) {
		vector<int> first_half, second_half;
		/*
		 * Create two vectors (halves) to left shift first
		 */
		for (unsigned i = 0; i < (LS_1.size() / 2); i++) {
			first_half.push_back(LS_1.at(i));
		}
		for (unsigned i = 5; i < (LS_1.size()); i++) {
			second_half.push_back(LS_1.at(i));
			//cout << LS_1.at(i);
		}
		/*
		 *	 Left shift first two elements of both vectors
		 */
		//temp storages for the first values
		int first_half_element, second_half_element;
		//temp storages for the second values
		int first_half_element2, second_half_element2;
		//first half LS-1
		first_half_element = first_half.at(0);
		first_half_element2 = first_half.at(1);
		//remove the first element
		first_half.erase(first_half.begin());
		first_half.erase(first_half.begin());
		first_half.push_back(first_half_element);
		first_half.push_back(first_half_element2);
		//repeat for the second half
		second_half_element = second_half.at(0);
		second_half_element2 = second_half.at(1);
		second_half.erase(second_half.begin());
		second_half.erase(second_half.begin());
		second_half.push_back(second_half_element);
		second_half.push_back(second_half_element2);
		//Consecrate the halfs into LS-1
		LS_2.reserve(first_half.size() + first_half.size()); // preallocate memory
		LS_2.insert(LS_2.end(), first_half.begin(), first_half.end());
		LS_2.insert(LS_2.end(), second_half.begin(), second_half.end());
//		cout << "LS2: ";
//		printVecDebug(LS_2);
		//
	}

};

#endif /* KEY_GENERATOR_H_ */
