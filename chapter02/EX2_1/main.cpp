#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

void preprocess_dict(const char *infile, const char *outfile)
{
	ifstream is(infile);
	ofstream os(outfile);

	string str;
	int i = 1;
	while (getline(is, str)) {
		if (i & 1) {
			bool lower_case = true;
			for (unsigned int i = 0; i < str.size(); ++i) {
				if (str[i] >= 'a' && str[i] <= 'z') continue;
				else { lower_case = false; break; }
			}

			if(lower_case) os << str << '\n';
		}
		i++;
	}
}

void sign_dict(const char *infile, const char *outfile)
{
	ifstream is(infile);
	ofstream os(outfile);
	string str1, str2;

	while (is >> str1) {
		str2 = str1;
		sort(str1.begin(), str1.end());
		os << str1 << " " << str2 << '\n';
	}
}

void sort_dict_sign(const char *infile, const char *outfile)
{
	ifstream is(infile);
	ofstream os(outfile);
	vector<string> dict_sign;
	string str;

	while (getline(is, str))
		dict_sign.push_back(str);
	sort(dict_sign.begin(), dict_sign.end());

	for (unsigned int i = 0; i < dict_sign.size(); ++i)
		os << dict_sign[i] << '\n';
}

void squash_dict(const char *infile, const char *outfile)
{
	ifstream is(infile);
	ofstream os(outfile);
	string oldsig, sig, word;

	while (is >> sig && is >> word) {
		if (sig != oldsig) {
			oldsig = sig;
			os << '\n';
		}
		
		os << word << " ";
	}
}

int main()
{
	preprocess_dict("gre_dictionary.txt", "gre_dictionary2.txt");
	sign_dict("gre_dictionary2.txt", "dictionary_sign.txt");
	sort_dict_sign("dictionary_sign.txt", "dictionary_sign_sort.txt");
	squash_dict("dictionary_sign_sort.txt", "dictionary_squash.txt");

	return 0;
}
