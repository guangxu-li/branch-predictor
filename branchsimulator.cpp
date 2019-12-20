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
	try
	{
		config >> m >> k;
		config.close();
		if (m <= 0 || k < 0)
		{
			throw "Smallest number for m is 1, and for k is 0 (not recommend to use 0). Please change them in config.txt";
		}
	}
	catch (const char *msg)
	{
		cerr << msg << endl;
		return 0;
	}

	if (k == 0)
	{
		cout << "k = 0\nEven though the program could still handle it, the smallest recommended value for k is 1." << endl;
	}

	ofstream out;
	string _file_name = string(argv[2]);

	//int separator = _file_name.rfind(".");
	//_file_name = _file_name.substr(0, separator);
	string out_file_name = _file_name + ".out";
	out.open(out_file_name.c_str());

	ifstream trace;
	trace.open(argv[2]);

	unsigned long pc;
	bool taken;
	trace >> std::hex >> pc >> taken;
	bitset<32> ppc = pc;

	// define bhr
	unsigned long bhr = pow(2, k) - 1;

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
		unsigned long mm = bitset<32>(pc_substr).to_ulong();

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
		// get msb in decimal
		unsigned msb = (bhr & (1 << (k - 1)));
		bhr = ((bhr - msb) << 1) + (taken && (k != 0)); // 1. remove msb 2. left shift 1 bit 3. add taken when k != 0
		// next branch
		trace >> std::hex >> pc >> taken;
		ppc = pc;
	}

	trace.close();
	out.close();
	return 0;
}