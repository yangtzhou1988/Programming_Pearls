#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const int MAX_BIT_LENGTH = 1000000;
const int MAX_BYTE_LENGTH = (MAX_BIT_LENGTH+7)/8;

inline void set_flag(unsigned char flag[], int i)
{
	flag[i>>3] |= (1<<(i&7));
}

inline void clear_flag(unsigned char flag[], int i)
{
	flag[i>>3] &= ~(1<<(i&7));
}

inline bool test_flag(unsigned char flag[], int i)
{
	return (flag[i>>3]&(1<<(i&7))) ? true : false;
}

inline int random(int low, int high)
{
	return low + (rand()|(rand()<<15))%(high-low+1);
}

void phone_number_generate(const char *out_file, int n)
{
	unsigned int *phone_number_list = new unsigned int[MAX_BIT_LENGTH];

	for(int i = 0; i < MAX_BIT_LENGTH; ++i)
		phone_number_list[i] = i;

	srand(0);
	for(int i = 0; i < n; ++i)
		swap(phone_number_list[i], phone_number_list[random(i, MAX_BIT_LENGTH-1)]);

	ofstream out_stream(out_file);

	for(int i = 0; i < n; ++i)
		out_stream << phone_number_list[i] << '\n';

	delete [] phone_number_list;
}

bool phone_number_sort(const char *in_file, const char *out_file)
{
	unsigned int t;
	unsigned char flag[MAX_BYTE_LENGTH] = {0};
	ifstream in_stream(in_file);

	while(in_stream>>t) {
		if(!test_flag(flag, t)) set_flag(flag, t);
		else return false;
	}

	unsigned char k;
	int i, j;
	ofstream out_stream(out_file);

	for(i = 0; i < MAX_BYTE_LENGTH; ++i) {
		k = flag[i];
		j = 0;
		while(k){
			if(k&0x01) out_stream << ((i<<3)+j) << '\n';
			k >>= 1;
			j++;
		}
	}

	return true;
}

int main()
{
	phone_number_generate("src.txt", 500000);
	phone_number_sort("src.txt", "dst.txt");

	return 0;
}
