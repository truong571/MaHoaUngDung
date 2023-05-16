#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <time.h>
using namespace std;
void k_m(uint64_t n, uint64_t& k, uint64_t& m)
{
	n -= 1;
	while (n % 2 == 0)
	{
		k += 1;
		n = n >> 1;
	}
	m = n;
}
uint64_t PowerMod(uint64_t a, uint64_t m, uint64_t p) // a^m mod p
{
	uint64_t result = 1;
	a = a % p;
	if (a == 0) return 0;
	while (m > 0) {
		if (m & 1) {
			result = (result * a) % p;
		}
		m = m >> 1;
		a = (a * a) % p;
	}
	return result;
}
bool Miller_Rabin(uint64_t p)// return TRUE if p is a composite and FALSE if p is prime
{
	srand(time(NULL));
	if (p == 2) {
		return true;
	}
	else if (p < 2) {
		return false;
	}
	else {
		int times = 10;
		bool isComposite = false;
		while (times > 0 && isComposite != true) {
			times--;
			uint64_t max = p-2;
			uint64_t min = 2;
			uint64_t a = 67;//rand() % max + min; // generate a in range(1,p-1)
			uint64_t k = 0;
			uint64_t m = 0;
			k_m(p, k, m);
			uint64_t b = PowerMod(a, m, p);
			if (b == 1) {
				continue;
			}
			for (int i = 0; i < k; i++) {
				if (b == p - 1) {
					isComposite = false;
					break;
				}
				else
				{
					b = PowerMod(b, 2, p);
					isComposite = true;
				}
			}
		}
		return isComposite;
	}
}
int main()
{
	
	//uint64_t n = 1073676287;
	uint64_t n = 1204108153;
	if (Miller_Rabin(n) == false) {
		cout << n << " is a prime." << endl;
	}
	else {
		cout << n << " is NOT a prime." << endl;
	}
	return 0;
}