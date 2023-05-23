/*
 * Encryptor.h
 *
 *  Created on: 2 Sep 2020
 *      Author: Kevin Vo Le
 *      Turn the plaintext to Initial Permutation
 *      Split IP into two parts (R4, L4)
 *      Apply Expansion Permutation on R4
 *      XOR on EP
 *
 *      IP_list = {2,6,3,1,4,8,5,7};
 *      EP {4,1,2,3,2,3,4,1}
 *		Encryptor is a child of Key_generator as it requires values from it to run
 *
 */

#ifndef S_DES_H_
#define S_DES_H_
#include "Global_Actions.h"
#include "Key_Generator.h"


class DES : public key_generator {
private:
	//initial permutation
	int IP_list[8] = {1,5,2,0,3,7,4,6};
	int E_P[8] = {3,0,1,2,1,2,3,0};
	int P4[4] = {1,3,2,0};
	int S0[4][4] = {1,0,3,2,3,2,1,0,0,2,1,3,3,1,3,2};
	int S1[4][4] = {0,1,2,3,2,0,1,3,3,0,1,0,2,1,0,3};
	int IP_invList[8] = {3,0,2,4,6,1,7,5};
public:
	vector<int> plaintext, IP, left_4_1, right_4_1, left_4, right_4, EP, EP1, sw_vect, IP_inv;
	vector<int> P4_val, P4_val1, P4_f, P4_f1, cipher, P4XOR, P4XOR1;
	vector<int> XOR_L, XOR_R, P4_XOR, P4_XOR1, XOR_Val, XOR_Val1, XOR_1, XOR_2;
	vector<int> XOR_Val_r, XOR_Val_l, XOR_Val_r1, XOR_Val_l1;
	vector<int> P4_output;
	string S1_val, S2_val, P4_s, P4_s1, S1_val1, S2_val1;
	string inital_pt, output;
	string sw_1, sw_2;
	DES(){
		cout << "Enter the 8 bit key" << endl;
				cin >> inital_pt;

	}

	void encrypt(){
		storeInputAsVector(plaintext, inital_pt);
		generateKey();
		cout << "Applying IP: " << endl;
		initialPermutation(plaintext);
		split(IP,left_4,right_4);
		EP_func(right_4, EP);
		XOR(P8_i, EP, XOR_Val, 8);
		cout << "S0: " << endl;
		split(XOR_Val,XOR_Val_l,XOR_Val_r);
		box(S1_val, XOR_Val_l, S0);
		box(S2_val, XOR_Val_r, S1);
		P4_s = S1_val + S2_val;
		storeInputAsVector(P4_val, P4_s);
		P4_func(P4_val,P4_f);
		XOR(P4_f,left_4, P4XOR,4);

		//repeat with right4 as left and P4_val as right

		EP_func(P4XOR, EP1);
		XOR(P8_f, EP1, XOR_Val1, 8);
		split(XOR_Val1, XOR_Val_l1, XOR_Val_r1);
		box(S1_val1, XOR_Val_l1, S0);
		box(S2_val1, XOR_Val_r1, S1);
		P4_s1 = S1_val1 + S2_val1;
		storeInputAsVector(P4_val1, P4_s1);
		P4_func(P4_val1,P4_f1);
		XOR(P4_f1,right_4, P4XOR1,4);
		combineVector(P4XOR1, P4XOR, IP_inv);
		IP_inverse(IP_inv, cipher);
		cout << "Cipher: ";
		printVecDebug(cipher);

	}

	void decrpyt(){
		storeInputAsVector(cipher, inital_pt);
		generateKey();
		cout << "Applying IP: " << endl;
		initialPermutation(cipher);
		split(IP,left_4,right_4);
		EP_func(right_4, EP);
		XOR(P8_f, EP, XOR_Val, 8);
//		cout << "S0: " << endl;
		split(XOR_Val,XOR_Val_l,XOR_Val_r);
		box(S1_val, XOR_Val_l, S0);
		box(S2_val, XOR_Val_r, S1);
		P4_s = S1_val + S2_val;
		storeInputAsVector(P4_val, P4_s);
		P4_func(P4_val,P4_f);
		XOR(P4_f,left_4, P4XOR,4);

		//repeat with right4 as left and P4_val as right

		EP_func(P4XOR, EP1);
		XOR(P8_i, EP1, XOR_Val1, 8);
		split(XOR_Val1, XOR_Val_l1, XOR_Val_r1);
		box(S1_val1, XOR_Val_l1, S0);
		box(S2_val1, XOR_Val_r1, S1);
		P4_s1 = S1_val1 + S2_val1;
		storeInputAsVector(P4_val1, P4_s1);
		P4_func(P4_val1,P4_f1);
		XOR(P4_f1,right_4, P4XOR1,4);
		combineVector(P4XOR1, P4XOR, IP_inv);
		IP_inverse(IP_inv, plaintext);
		cout << "Plaintext: ";
		printVecDebug(plaintext);
	}
	void initialPermutation(vector<int> &input){
		for (unsigned i = 0; i < input.size(); i++) {
			IP.push_back(input.at(IP_list[i]));
		}
		printVecDebug(IP);
	}
	void split(vector<int> &source, vector<int> &left, vector<int> &right){
//		cout << "Splitting" << endl;
//		cout << "Size:" << source.size() << endl;
		for (unsigned i = 0; i < (source.size() / 2); i++) {
			left.push_back(source.at(i));
		}
		for (unsigned i = 4; i < (source.size()); i++) {
			//cout << IP.at(i) << " ";
			right.push_back(source.at(i));
		}
	}
	void EP_func(vector<int> &input, vector<int> &output){
//		cout << "EP function " << endl;
//		cout << "Size:" << input.size() << endl;
//		for (unsigned i = 0; i < 4; i++){
//			cout << input.at(i) << endl;
//		}
		for (unsigned i = 0; i < 8; i++){
			output.push_back(input.at(E_P[i]));
		}
		//printVecDebug(EP);
	}
	void XOR(vector<int> &x, vector<int> &y, vector<int> &XOR, int size){
		for (int i = 0; i < size; i++) {
			int v1, v2;
			v1 = y.at(i);
			v2 = x.at(i);
			if ((v1 == 0 && v2 == 0) || (v1 == 1 && v2 == 1)) {
				XOR.push_back(0);
			} else {
				XOR.push_back(1);
			}
		}
	}
	void splitXOR(){
		for (unsigned i = 0; i < (XOR_Val.size()/2); i++) {
			XOR_L.push_back(XOR_Val.at(i));
		}
		for (unsigned i = 4; i < (XOR_Val.size()); i++) {
			XOR_R.push_back(XOR_Val.at(i));
		}
	}
	void box(string &output, vector<int>input, int box[][4]){
		int v1, v2, v3, v4, r, c, temp;
		v1 = input.at(0);
		v2 = input.at(1);
		v3 = input.at(2);
		v4 = input.at(3);
		//cout << "V1: " << v1 << ", V2: " << v2 << ", V3: " << v3 << ", V4: " << v4 << endl;
		findRowAndColumn(v1, v2, v3, v4, r, c);
		//cout << "Row: " << r << " Col: " << c << endl;
		temp = box[r][c];
		//cout << "Value = " << temp << endl;
		if (temp == 0){
			output = "00";
		}
		if (temp == 1){
			output = "01";
		}
		if (temp == 2){
			output = "10";
		}
		if (temp == 3) {
			output = "11";
		}
	}
	void findRowAndColumn(int v1, int v2, int v3, int v4, int &r, int &c){
		//binary string 00 = 0
		if (v1 == 0 && v4 == 0){
			r = 0;
		}
		// 01 = 1
		if (v1 == 0 && v4 == 1){
			r = 1;
		}
		// 10 = 2
		if (v1 == 1 && v4 == 0){
			r = 2;
		}
		// 11 = 3
		if (v1 == 1 && v4 == 1){
			r = 3;
		}
		if (v2 == 0 && v3 == 0){
			c = 0;
		}
		// 01 = 1
		if (v2 == 0 && v3 == 1){
			c = 1;
		}
		// 10 = 2
		if (v2 == 1 && v3 == 0){
			c = 2;
		}
		// 11 = 3
		if (v2 == 1 && v3 == 1){
			c = 3;
		}

	}
	void P4_func(vector<int> &P4_value, vector<int> &output){	//function P4 used to rearrange the permutation
		for (unsigned i = 0; i < P4_value.size(); i++) {
			output.push_back(P4_value.at(P4[i]));
		}
	}
	void IP_inverse(vector<int> &input, vector<int> &output){	//similar to previous permutation rearranged
		for (unsigned i = 0; i < input.size(); i++) {			//renamed for purposes of easy reading
			output.push_back(input.at(IP_invList[i]));
		}
	}
	void printBox() {	//debug command use to see if box was inputed correctly

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << " | " << S1[i][j] << " ";
			}
			cout << "|" << endl;
		}
		cout << "  ---  ---  --- " << endl;
	}


};



#endif /* S_DES_H_ */
