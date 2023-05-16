#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

string Addition(string m, string n)
{
	string sum;
	// chuẩn hóa hai chuổi cho bằng nhau về độ dài
	// ví dụ m=12345 n=123 sau chuẩn hóa n=00123
	int size_lenght = 0;
	if (m.length() > n.length()) {
		size_lenght = m.length() - n.length();
		for (int i = 0; i < size_lenght; i++) {
			n.insert(0, "0");
		}
	}
	else {
		size_lenght = n.length() - m.length();
		for (int i = 0; i < size_lenght; i++) {
			m.insert(0, "0");
		}
	}
	// cộng hai chuỗi 
	int flag = 0;
	int temp = 0;
	size_lenght = m.length();
	for (int i = size_lenght - 1; i >= 0; i--) {
		temp = int(m[i]) + int(n[i]) - 2 * 48 + flag;
		flag = 0;
		flag += temp / 10;
		string ch = to_string(temp % 10);
		sum.insert(0, ch);
	}
	if (flag > 0) {
		sum.insert(0, to_string(flag));
	}
	flag = 0;
	return sum;
}
string Multiplication(string m, string n)
{
	string Mul;
	// m*n
	for (int i = n.length() - 1; i >= 0; i--) {
		string Result;
		int temp;
		int flag = 0;
		for (int j = m.length() - 1; j >= 0; j--) {
			temp = (int(m[j]) - 48) * (int(n[i]) - 48) + flag;
			flag = 0;
			flag += temp / 10;
			string ch = to_string(temp % 10);
			Result.insert(0, ch);
		}
		if (flag > 0) {
			Result.insert(0, to_string(flag));
		}
		flag = 0;
		for (int k = 0; k < n.length() - i - 1; k++) {
			Result.insert(Result.length(), "0");
		}
		Mul = Addition(Mul, Result);
	}
	// Nếu nhân với 0 thì kết quả sẽ là 0 
	for (int i = 0; i < Mul.length(); i++) {
		if (Mul[i] != '0') {
			return Mul;
		}
	}
	return "0";
}
int Mod(string S, int z)
{
	int result = 0;
	for (int i = 0; i < S.length(); i++) {
		// Ta chia như phép chia bình thường rồi lấy phần dư 
		result = (result * 10 + int(S[i]) - 48) % z;
	}
	return result;
}
int main()
{
	string m;
	string n;
	int z;
	cout << "Enter m : ";
	getline(cin, m);
	cout << "Enter n : ";
	getline(cin, n);
	do {
		cout << "Enter z : ";
		cin >> z;
	} while (z == 0);
	// (m + n)
	cout << "(m + n)" << Addition(m, n) << endl;
	// (m + n) mod z
	cout << "(m + n) mod z" << Mod(Addition(m, n), z) << endl;
	// m*n
	cout << "m*n" << Multiplication(m, n) << endl;
	// m*n mod z
	cout << "m*n mod z" << Mod(Multiplication(m, n), z) << endl;
	return 1;
}