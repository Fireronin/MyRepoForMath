// Test_MPFR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "mpreal.h"
#include <vector>
#include <time.h>
#include <bitset>
#include <string>

int npri(int n) {
	if (n == 1)
	{
		return 2;
	}
	int ct = 1;
	for (int i = 3; i < 100000; i += 2)
	{
		bool ok = true;
		for (int j = 3; j*j < i; j += 2)
		{
			if (i%j == 0)
			{
				ok = false;
				break;
			}
		}
		if (ok)
		{
			ct++;
			if (ct == n)
			{
				return i;
			}
		}
	}
	return 0;
}
using namespace std;
int main()
{
	using mpfr::mpreal;
	using std::cout;
	using std::endl;
	using std::cin;
	using std::vector;

	const long int digits = 1000;

	mpreal::set_default_prec(mpfr::digits2bits(digits));

	const mpreal iv = mpreal("5982008194709330540717000806649795645173440000");

	mpreal rv = mpfr::sqrt(iv);
	mpreal sp = mpfr::floor(rv) + 1;
	mpreal ep = mpfr::floor(rv*1.01f);
	cout.precision(80);    // Show all the digits

	int ct = 0;
	int am;
	int sg;
	cin >> am;
	cin >> sg;
	int myints[43];

	for (int i = 1; i <= sg; i++)
	{
		int ta;
		cin >> ta;
		for (int j = 0; j < ta; j++)
		{
			myints[ct++] = npri(i);
		}
	}
	int tp = ct;
	for (int i = ct; i < am; i++)
	{
		myints[ct++] = npri(i - tp + sg);
	}
	cout << "in val   " << iv << endl;
	cout << "root val   " << rv << endl;
	cout << "sp   " << sp << endl;
	time_t start = time(0);
	ct = 0;

	for (long int itv = 0; itv < pow(2, am); itv++)
	{
		mpreal cd = mpreal(1);

		for (int j = 0; j < am; j++)
		{
			long int nit = itv;
			if (itv & 1 << j)
			{
				cd *= myints[j];
			}
		}
		//cout << cd << endl;
		if (cd >= sp && cd < ep)
		{
			if (mpfr::mod(iv, cd) == 0)
			{
				ct++;
				cout << ct << "  " << itv << endl;
			}
		}
	}

	cout << ct;
	cout << "    " << difftime(time(0), start);

	getchar();

	return 0;
}