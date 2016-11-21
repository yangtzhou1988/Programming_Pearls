#include <iostream>
#include <cstring>

using namespace std;

static int gcd(int a, int b)
{
	if (b == 0) return a;
	else return gcd(b, a%b);
}

template <typename T>
void left_rotate1(T *vec, int n, int i)
{
	if (vec == NULL || n <= 0 || i <= 0)
		return;

	i = i%n;
	if (i <= 0)
		return;

	int k = gcd(n, i);

	do {
		int prev;
		int next = --k;
		T temp = vec[next];

		while (true) {
			prev = next;
			next = (next + i) % n;
			if (next == k) break;
			vec[prev] = vec[next];
		}

		vec[prev] = temp;
	} while (k > 0);
}

template <typename T>
static void reverse(T *vec, int l, int h)
{
	while (l < h) {
		swap(vec[l], vec[h]);
		l++;
		h--;
	}
}

template <typename T>
void left_rotate2(T *vec, int n, int i)
{
	if (vec == NULL || n <= 0 || i <= 0)
		return;

	i = i%n;
	if (i <= 0)
		return;

	reverse(vec, 0, i - 1);
	reverse(vec, i, n - 1);
	reverse(vec, 0, n - 1);
}

int main()
{
	char s[] = "hello!";

	left_rotate1(s, strlen(s), 6);

	cout << s << endl;

	return 0;
}
