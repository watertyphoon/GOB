#include "/public/read.h" // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep
#include <cmath>
using namespace std;

/*void choice(int input) {
}*/

//TODO:
//truth table
//other output
//edge cases aka bad output or invalid circuits

void die() {// use this for bad input
	cout << "Invalid Input!\n";
	exit(EXIT_FAILURE);
}

string Logic_Gate(int gate_value) {//turns the ints in main into the strings
	if (gate_value == 0) {
		return "NOT";
	} else if (gate_value == 1) {
		return "AND";
	} else if (gate_value == 2) {
		return "OR";
	} else if (gate_value == 3) {
		return "NAND";
	} else if (gate_value == 4) {
		return "NOR";
	} else if (gate_value == 5) {
		return "XOR";
	} else {
		die();
		return "this is pointless just here to get rid of the warning";
	}
}

struct Node {
	int input1 = 0;//input index 1 connected to node
	int input2 = 0;//input index 2 connected to node
	int output_index = 0;//the index of where it outputs to
	string gate = "";//name of the gate, if its the first set of pins it should be "INPUT", double check README though
	Node(int i, int c, string g, int o) {
		input1 = i;
		input2 = c;
		gate = g;
		output_index = o;
	}
};
/*void build_truth_table (vector<Node> &pins) {
	vector<pair<Node, bool>> resultants{};
	for(int i = 0; i < pins.size(); i++) {
	}
}*/

int main() {
	vector<Node> circuit = {};
	int N = 0;//initial size of the circuit, the amount of initial pins
	int input = 0;
	int index1 = 0;
	int index2 = 0;
	cout << "Welcome to the Gates of Babylon!" << endl;
	cout << "How many inputs does your logic block have? (1 to 10)" << endl;
	cin >> N;
	for (int i = 0; i < N; i++) { //creates the first input pins
		Node temp(-1, -1, "INPUT", -1);
		circuit.push_back(temp);
	}
	while (true) {
		cout << "What sort of gate do you want to add?" << endl;
		cout << " 0 - NOT, 1 - AND, 2 - OR, 3 - NAND, 4 - NOR, 5 - XOR, 6 - DONE" << endl;
		cin >> input;
		if (!cin) {
			die();
		}
		if (input == 6) {
			break;
		}
		if (input > 6 || input < 0) {
			die();
		}
		/*cout << "Give the index for the first input:" << endl;
		cin >> index1;
		if (index1 >= circuit.size()) {
			die();
		}*/
		if (input != 0) {//if the gate isn't NOT
			cout << "Give the index for the first input:" << endl;
			cin >> index1;
			if (index1 >= circuit.size()) {
				die();
			}
			cout << " Give the index for the second input:" << endl;
			cin >> index2;
			if (index2 > circuit.size()) {
				die();
			}
			Node temp(index1, index2, Logic_Gate(input), -1);//creates the new pin that is a logic gate
			circuit.push_back(temp);
			circuit.at(index1).output_index = circuit.size() - 1;//connects the input pins to the output
			circuit.at(index2).output_index = circuit.size() - 1; //same as above
		} else {//if the gate is NOT
			cout << "Give the index for the input:" << endl;
			cin >> index1;
			if (index1 >= circuit.size()) {
				die();
			}
			Node temp(index1, index1, Logic_Gate(input), -1);
			circuit.push_back(temp);
			circuit.at(index1).output_index = circuit.size() - 1;
		}
		//cicuit.push_back(
	}
//still a work in progress but this is where the truth table or other output will go
	cout << endl;
	cout << "1) Print Circuit Block or 2) Print Truth Table" << endl;
	cin >> input;
	if (input == 1) {
		for (int i = 0; i < circuit.size(); i++) {
			cout << "Gate Type: " << circuit.at(i).gate << endl;
			cout << "Input Connected to Index: ";
			if (circuit.at(i).input1 == -1) {
				cout << "N.C. and N.C." << endl;
			} else {
				if (circuit.at(i).gate == "NOT") {
					cout << circuit.at(i).input1 << endl;
				} else {
					cout << circuit.at(i).input1 << " and " << circuit.at(i).input2 << endl;
				}
			}
			cout << "Output Connected to Index: ";
			if (i == circuit.size() - 1) {
				cout << "OUTPUT PIN" << endl;
			} else {
				cout << circuit.at(i).output_index << endl;
			}
			cout << "Value: X" << endl;
			cout << endl;
		}
	} else if (input == 2) {
		int all_possibilities = 1 << N;
		vector<vector<bool>> t_table(all_possibilities);
		cout <<  "Input Pins (Numbers), Output Pin (O):" << endl;
		for (int i = 0; i < N; i++) {
			cout << i << "|";
		}
		cout << "O" << endl;
		for (int i = 0; i < all_possibilities; i++) {
			vector<bool> results(circuit.size());
			for (int j = 0; j < N; j++) {
				results.at(j) = ((i >> (N - 1 - j)) & 1);
				//cout << results.at(j) << "|";
				t_table.at(i).push_back(results.at(j));
			}
			for (int k = N; k < circuit.size(); k++) {
				Node temp = circuit.at(k);
				bool rhs = results.at(temp.input1);
				bool lhs = true;
				bool resultant = false;
				if (temp.gate != "NOT") {
					lhs = results.at(temp.input2);
				} else {
					lhs = false;
				}
				if (temp.gate == "NOT") {
					resultant = !rhs;
				} else if (temp.gate == "AND") {
					resultant = rhs && lhs;
				} else if (temp.gate == "OR") {
					resultant = rhs || lhs;
				} else if (temp.gate == "NAND") {
					resultant = !(rhs && lhs);
				} else if (temp.gate == "XOR") {
					resultant = rhs ^ lhs;
				} else if (temp.gate == "NOR") {
					resultant = !(rhs || lhs);
				}
				results.at(k) = resultant;
			}
			//cout << results.at(circuit.size() - 1) << endl;
			//results.clear();
			t_table.at(i).push_back(results.at(circuit.size() - 1));
		}
		for (int i = t_table.size() - 1; i >= 0; i--) {
			for (int j = 0; j < t_table.at(i).size(); j++) {
				cout << t_table.at(i).at(j);
				if (t_table.at(i).size() - 1 == j) {
					cout << endl;
				} else {
					cout << "|";
				}
			}
		}
	} else {
		die();
	}
}
