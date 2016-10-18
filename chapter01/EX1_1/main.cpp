#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>

using namespace std;

const int MAX_BIT_LENGTH = 1000000;
const int MAX_BYTE_LENGTH = (MAX_BIT_LENGTH + 7) / 8;

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

bool phone_number_sort(const char *in_file, const char *out_file)
{
	unsigned int t;
	ifstream in_stream(in_file);
	ofstream out_stream(out_file);
	set<int> data_set;

	while (in_stream >> t)
		data_set.insert(t);

	for (set<int>::iterator i = data_set.begin(); i != data_set.end(); ++i)
		out_stream << *i << '\n';

	return true;
}

int main()
{
	//phone_number_generate("src.txt", 500000);
	phone_number_sort("src.txt", "dst.txt");

	return 0;
}
