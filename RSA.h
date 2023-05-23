/*
 * RSA.h
 *
 *  Created on: 20 Sep 2020
 *      Author: Kevin Vo Le
 */

#ifndef RSA_H_
#define RSA_H_

class RSA {
public:
	int p, q, n, e, m, c;
	int A1 = 1;
	int A2 = 0;
	int A3;
	int B1 = 0;
	int B2 = 1;
	int B3;
	int T1, T2, T3;
	int phi, d;
	string binaryString = "";

	bool theSame(int p, int q) {

		if (p == q) {
			cout << "Invalid input. p & q cannot be the same." << endl;
			return true;
		}
		return false;
	}

	bool isPrime(int p, int q) {

		if (p <= 1 || q <= 1) {
			cout << "Invalid input. Value entered is <= 1 " << endl;
			return false;
		}

		for (int i = 2; i < p; i++) {
			if (p % i == 0) {
				cout << "Invalid input. Value entered is not a prime " << endl;
				return false;
			}
		}

		for (int i = 2; i < q; i++) {
			if (q % i == 0) {
				cout << "Invalid input. Value entered is not a prime " << endl;
				return false;
			}
		}
		return true;
	}
	void getPrimeNumbers() {
		bool done = false;
		int count = 0;
		do {
			cout << "Enter Prime number p: " << endl;
			cin >> p;
			if (!cin) {
				cin.clear();
				cin.ignore();
				cout << "Enter a valid input for p!" << endl;
			} else {
				count++;
			}
			cout << count << endl;
			cout << "Enter Prime number q: " << endl;
			cin >> q;
			if (!cin) {
				cin.clear();
				cin.ignore();
				cout << "Enter a valid input for q!" << endl;
			} else {
				count++;
			}
			if (count > 1) {
				done = true;
				break;
			}
		} while ((!isPrime(p, q) || !theSame(p, q)) || !done);
	}
	void setN() {
		n = p * q;
	}
	void setPhi() {
		phi = (p - 1) * (q - 1);
	}
	void getE() {
		bool done = false;
		do {
			cout << "Enter encryption key 'e': " << endl;
			cin >> e;
			if (!cin) {
				cin.clear();
				cin.ignore();
				cout << "Enter a valid input for e!" << endl;
			}
			else {
				done = true;
				break;
			}
		} while (e < 1 || phi < e || !done);	//1< e < phi(n),
	}
	void setM() {
		bool done = false;
		do {
			cout << "Enter m" << endl;
			cin >> m;
			if (!cin) {
				cin.clear();
				cin.ignore();
				cout << "Enter a valid input!" << endl;
			} else {
				done = true;
				break;
			}
		} while (!done);
	}
	void findDecryptionKey() {
		//call Eucalid's Algorithm
		cout << "N: " << n << " Phi: " << phi << endl;
		A3 = phi;
		B3 = e;
		d = gcdExtended(e, phi);
		if (d > 0) {			
			squareAndMultiply("1", (d + phi), phi);
		}

	}

	void encrypt() {
		getPrimeNumbers();
		setN();
		setPhi();
		getE();
		findDecryptionKey();
		setM();
		decToBinary(e);
		trimString(binaryString);
		encryption();

	}

	int gcdExtended(int m, int b) {
		
		int Q;
		if (B3 == 0) {
			return A3;
		}
		if (B3 == 1) {

			return B2;
		}
		Q = A3 / B3;

		T1 = A1 - (Q * B1);
		T2 = A2 - (Q * B2);
		T3 = A3 - (Q * B3);


		A1 = B1;
		A2 = B2;
		A3 = B3;



		B1 = T1;
		B2 = T2;
		B3 = T3;

		gcdExtended(A3, B3);

	}

	void decToBinary(int n) {

		for (int i = 31; i >= 0; i--) {
			int k = n >> i;
			if (k & 1)
				binaryString = binaryString + "1";
			else
				binaryString = binaryString + "0";
		}
	}

	void trimString(string &input) {
		int i;
		for (auto &letter : input) {
			i++;
			if (letter == '1') {
				input.erase(input.begin(), input.begin() + i);
				break;
			}
		}
	}

	int squareAndMultiply(string input, int a, int n) {
		int c, d;
		c = 0;
		d = 1;
		for (unsigned it = 0; it < input.length(); it++) {
			string val;
			int num;
			val = input[it];
			num = stoi(val);
			d = (d * d) % n;
			if (num == 1) {
				c = c + 1;
				d = (d * a) % n;
			}
		}
		return d;
	}

	void encryption() {
		cout << "C: " << squareAndMultiply(binaryString, m, n) << endl;
	}

};

#endif /* RSA_H_ */
