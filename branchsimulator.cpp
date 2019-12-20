#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <bitset>

using namespace std;

int main(int argc, char **argv)
{
	ifstream config;
	config.open(argv[1]);

	int m, k;
	config >> m >> k;

	config.close();

	ofstream out;
	string _file_name = string(argv[2]);

	int separator = _file_name.rfind(".");
	_file_name = _file_name.substr(0, separator);
	string out_file_name = _file_name + ".out";
	out.open(out_file_name.c_str());

	ifstream trace;
	trace.open(argv[2]);

	bitset<32> pc;
	bool taken;
	trace >> std::dec >> pc >> taken;

	// define bhr
	bitset<8> bhr = pow(2, k) - 1;

	// define pht
	vector<vector<int>> pht(pow(2, k) - 1, vector<int>(pow(2, m) - 1));

	// history k
	int row;
	int col;
	for (col = 0; col < pow(2, k) - 1; col++)
	{
		// index m
		for (row = 0; row < pow(2, m) - 1; row++)
		{
			cout << col << " " << row << endl;
			pht[col][row] = 3;
		}
	}

	while (!trace.eof())
	{
		string pc_substr = pc.to_string().substr(32 - m, m);
		unsigned long mm = bitset<32>(pc_substr).to_ulong();

		// predict
		bool prediction = pht[k][mm] >= 2 ? true : false;
		out << prediction << endl;

		// update pht
		if (taken)
		{
			// taken
			// pht == 00 -> 01
			// pht == 01 / 10 / 11 -> 11
			pht[k][mm] = pht[k][mm] == 0 ? 1 : 3;
		}
		else
		{
			// not taken
			// pht == 11 -> 10
			// pht == 10 / 01 / 00 -> 0
			pht[k][mm] = pht[k][mm] == 3 ? 2 : 0;
		}
		// update bhr
		bhr = bhr.to_ulong() - pow(2, k - 1) + taken;

		// next branch
		trace >> std::dec >> pc >> taken;
	}

	trace.close();
	out.close();
	return 0;
}