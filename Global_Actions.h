/*
 * Global_Actions.h
 *
 *  Created on: 2 Sep 2020
 *      Author: Kevin Vo Le
 */

#ifndef GLOBAL_ACTIONS_H_
#define GLOBAL_ACTIONS_H_

void storeInputAsVector(vector<int> &dest, string input) {
	for (unsigned i = 0; i < input.length(); i++) {
		string it;
		int num;
		it = input[i];
		num = stoi(it);
		dest.push_back(num);
		//cout << "Vector Size: " << dest.size();
	}
}

string convertToString(vector<int> &p) {
	string key = "";
	//cout << "P size: " << p.size() << endl;
	for (unsigned i = 0; i < p.size(); i++) {
		key = key + to_string(p.at(i));
	}
//		key_int = stoi(key);
	return key;
}

void printVecDebug(vector<int> vect) {
	//cout << "Print test: " << endl;
	for (unsigned i = 0; i < vect.size(); i++) {
		cout << vect.at(i);
//			if (i == 4){
//				cout << " " << endl;
//			}
	}
	cout << endl;
}

void combineVector(vector<int> &x, vector<int> &y, vector<int> &output){
	for(unsigned i = 0; i < x.size(); i++){
		//cout << x.at(i) << endl;
		output.push_back(x.at(i));
	}
	for(unsigned i = 0; i < y.size(); i++){
		//cout << y.at(i) << endl;
		output.push_back(y.at(i));
	}

}




#endif /* GLOBAL_ACTIONS_H_ */
