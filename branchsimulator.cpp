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

	string out_file_name = _file_name + ".out";
	out.open(out_file_name.c_str());

	ifstream trace;
	trace.open(argv[2]);

	unsigned long pc;
	bool taken;
	trace >> std::hex >> pc >> taken;
	bitset<32> ppc = pc;

	// define bhr
	int bhr = pow(2, k) - 1;

	// define pht
	vector<vector<int>> pht(pow(2, k), vector<int>(pow(2, m)));

	// history k
	for (int col = 0; col < pow(2, k); col++)
	{
		// index m
		for (int row = 0; row < pow(2, m); row++)
		{
			pht[col][row] = 3;
		}
	}

	while (!trace.eof())
	{
		// substract m lsb from pc
		string pc_substr = ppc.to_string().substr(32 - m, m);

		// initial / update mm <- row of pht
		unsigned long mm = bitset<32>(pc_substr).to_ulong() - 1;

		// predict
		bool prediction = pht[bhr][mm] >= 2 ? true : false;
		out << prediction << endl;

		// update pht
		if (taken)
		{
			// taken
			// pht == 00 -> 01
			// pht == 01 / 10 / 11 -> 11
			pht[bhr][mm] = pht[bhr][mm] == 0 ? 1 : 3;
		}
		else
		{
			// not taken
			// pht == 11 -> 10
			// pht == 10 / 01 / 00 -> 0
			pht[bhr][mm] = pht[bhr][mm] == 3 ? 2 : 0;
		}
		// update bhr
		bhr = bitset<32>(bitset<32>(bhr).to_string().substr(33 - k, k)).to_ulong() * 2 + taken; // 32 - k + 1
		// next branch
		trace >> std::hex >> pc >> taken;
		ppc = pc;
	}

	trace.close();
	out.close();
	return 0;
}