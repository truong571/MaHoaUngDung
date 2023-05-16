#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
using namespace std;
string C[] = { "00000000","01000000","02000000","04000000","08000000",
"10000000","20000000","40000000","80000000","1b000000","36000000" };
const string S_Box{ "637c777bf26b6fc53001672bfed7ab76ca82c97dfa5947f0add4a2af9ca472c0b7fd9326363ff7cc34a5e5f171d8311504c723c31896059a071280e2eb27b27509832c1a1b6e5aa0523bd6b329e32f8453d100ed20fcb15b6acbbe394a4c58cfd0efaafb434d338545f9027f503c9fa851a3408f929d38f5bcb6da2110fff3d2cd0c13ec5f974417c4a77e3d645d197360814fdc222a908846eeb814de5e0bdbe0323a0a4906245cc2d3ac629195e479e7c8376d8dd54ea96c56f4ea657aae08ba78252e1ca6b4c6e8dd741f4bbd8b8a703eb5664803f60e613557b986c11d9ee1f8981169d98e949b1e87e9ce5528df8ca1890dbfe6426841992d0fb054bb16" };
string ArrayHex(string K)
{
	// Chuyển chuỗi string sang chuỗi hex
	string H{ "0123456789abcdef" };
	string result;
	for (int i = 0; i < K.length(); i++) {
		string X{ "  " };
		int flag = int(K[i]);
		int quotient = flag / 16;
		X[0] = H[quotient];
		int surplus = flag % 16;
		X[1] = H[surplus];
		result.append(X);
	}
	return result;
}
string ShiftRows(string X)
{
	// dịch sang phải 
	int length = X.length();
	for (int j = 0; j < 2; j++) {
		char temp = X[0];
		for (int i = 0; i < length; i++) {			
			if (i == length - 1) {
				X[i] = temp;
			}
			else {
				X[i] = X[i + 1];
			}
		}
	}
	return X;
}
string JoinSBox(string X)
{
	// kết quả chuỗi X vào S-Box
	string result;
	for (int i = 0; i < X.length(); i += 2) {
		int x, y;
		if (int(X[i]) < 58) {
			x = int(X[i]) - 48;
		}
		else {
			x = int(X[i]) - 87;
		}
		if (int(X[i+1]) < 58) {
			y = int(X[i+1]) - 48;
		}
		else {
			y = int(X[i+1]) - 87;
		}
		int flag = 32 * x + 2 * y;
		string kq{ "  " };
		kq[0] = S_Box[flag];
		kq[1] = S_Box[flag+1];
		result.append(kq);
	}
	return result;
}
long long HexToDec(string X)
{
	long long kq = 0;
	for (int i = 0; i < X.length(); i++) {
		int x;
		if (int(X[i]) < 58) {
			x = int(X[i]) - 48;
		}
		else {
			x = int(X[i]) - 87;
		}
		kq += pow(16, X.length() - 1 - i) * x;
	}
	return kq;
}
string DecToHex(long long X)
{
	string result;
	string H{ "0123456789abcdef" };
	while (X > 0) {
		string k{" "};
		k = H[X % 16];
		result.append(k);
		X /= 16;
	}
	if (result.length() < 8) {
		for (int i = result.length(); i < 8; i++) {
			result.append("0");
		}
	}
	string temp = result;
	for (int i = 0; i < temp.length(); i++) {
		result[i] = temp[temp.length() - 1 - i];
	}
	return result;
}
string XOR(string X, string Y)
{
	long long x = HexToDec(X);
	long long y = HexToDec(Y);
	long long z = x ^ y;
	return DecToHex(z);
}
void expand(string k)
{
	string x = ArrayHex(k);// chuyển kiểu string sang kiểu hex
	cout << "K0 : ";
	for (int i = 0; i < x.length(); i++) {
		if (i % 2 == 1) {
			cout << x[i] << " ";
		}
		else {
			cout << x[i];
		}
	}
	cout << endl;
	for (int i = 1; i <= 10; i++) {
		string k0, k1, k2, k3;
		string l0, l1, l2, l3;		
		for (int j = 0; j < x.length(); j++) {
			string flag{ " " };
			if (j < 8) {
				flag = x[j];
				k0.append(flag);
			}
			else if (j < 16) {
				flag = x[j];
				k1.append(flag);
			}
			else if (j < 24) {
				flag = x[j];
				k2.append(flag);
			}
			else {
				flag = x[j];
				k3.append(flag);
			}
		}
		l0 = XOR(k0, XOR(JoinSBox(ShiftRows(k3)), C[i]));
		l1 = XOR(l0, k1);
		l2 = XOR(l1, k2);
		l3 = XOR(l2, k3);
		string xx;
		xx.append(l0);
		xx.append(l1);
		xx.append(l2);
		xx.append(l3);
		x = xx;
		cout << "K" << i << " : ";
		for (int n = 0; n < xx.length(); n++) {
			if (n % 2 == 1) {
				cout << x[n] << " ";
			}
			else {
				cout << x[n];
			}
		}
		cout << endl;
	}
}
int main()
{
	expand("Thats my Kung Fu");
	return 1;
}