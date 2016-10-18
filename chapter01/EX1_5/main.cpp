#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const int MAX_BIT_LENGTH = 1000000;
const int MAX_BYTE_LENGTH = ((MAX_BIT_LENGTH+1)/2 + 7) / 8;

inline void set_flag(unsigned char flag[], int i)
{
	flag[i >> 3] |= (1 << (i & 7));
}

inline void clear_flag(unsigned char flag[], int i)
{
	flag[i >> 3] &= ~(1 << (i & 7));
}

inline bool test_flag(unsigned char flag[], int i)
{
	return (flag[i >> 3] & (1 << (i & 7))) ? true : false;
}

inline int random(int low, int high)
{
	return low + (rand() | (rand() << 15)) % (high - low + 1);
}

void phone_number_generate(const char *out_file, int n)
{
	unsigned int *phone_number_list = new unsigned int[MAX_BIT_LENGTH];

	for (int i = 0; i < MAX_BIT_LENGTH; ++i)
		phone_number_list[i] = i;

	srand(0);
	for (int i = 0; i < n; ++i)
		swap(phone_number_list[i], phone_number_list[random(i, MAX_BIT_LENGTH - 1)]);

	ofstream out_stream(out_file);

	for (int i = 0; i < n; ++i)
		out_stream << phone_number_list[i] << '\n';

	delete[] phone_number_list;
}

void first_half_sort_file(unsigned char *flag, const char *out_file)
{
	unsigned int i;
	int j;
	unsigned char k;
	ofstream out_stream(out_file);

	for (i = 0; i < MAX_BYTE_LENGTH; ++i) {
		k = flag[i];
		j = 0;
		while (k) {
			if (k & 0x01) out_stream << ((i << 3) + j) << '\n';
			k >>= 1;
			j++;
		}
	}
}

void second_half_sort_file(unsigned char *flag, int half, const char *out_file)
{
	unsigned int i;
	int j;
	unsigned char k;
	ofstream out_stream(out_file);

	for (i = 0; i < MAX_BYTE_LENGTH; ++i) {
		k = flag[i];
		j = 0;
		while (k) {
			if (k & 0x01) out_stream << ((i << 3) + j + half) << '\n';
			k >>= 1;
			j++;
		}
	}
}

void merge_sort_file(const char *in_file1, const char *in_file2, const char *out_file)
{
	unsigned int t1, t2;
	ifstream in_stream1(in_file1);
	ifstream in_stream2(in_file2);
	ofstream out_stream(out_file);

	if (!(in_stream1 >> t1)) {
		while (in_stream2 >> t2) out_stream << t2 << '\n';
		return;
	}

	if (!(in_stream2 >> t2)) {
		out_stream << t1 << '\n';
		while (in_stream1 >> t1) out_stream << t1 << '\n';
		return;
	}

	while (true) {
		if (t1 < t2) {
			out_stream << t1 << '\n';
			if (!(in_stream1 >> t1)) {
				out_stream << t2 << '\n';
				while (in_stream2 >> t2) out_stream << t2 << '\n';
				break;
			}
		}
		else {
			out_stream << t2 << '\n';
			if (!(in_stream2 >> t2)) {
				out_stream << t1 << '\n';
				while (in_stream1 >> t1) out_stream << t1 << '\n';
				break;
			}
		}
	}
}

bool phone_number_sort(const char *in_file, const char *out_file)
{
	unsigned int t;
	unsigned char flag[MAX_BYTE_LENGTH] = { 0 };
	ifstream in_stream(in_file);

	unsigned int half = (MAX_BIT_LENGTH+1)/2;

	while (in_stream >> t) {
		if (t < half) {
			if (!test_flag(flag, t)) set_flag(flag, t);
			else return false;
		}
	}

	first_half_sort_file(flag, "1.txt");

	in_stream.close();
	in_stream.open(in_file);
	memset(flag, 0, MAX_BYTE_LENGTH);

	while (in_stream >> t) {
		if (t >= half) {
			t -= half;
			if (!test_flag(flag, t)) set_flag(flag, t);
			else return false;
		}
	}

	second_half_sort_file(flag, half, "2.txt");

	merge_sort_file("1.txt", "2.txt", out_file);

	return true;
}

int main()
{
	//phone_number_generate("src.txt", 900000);
	phone_number_sort("src.txt", "dst.txt");

	return 0;
}

