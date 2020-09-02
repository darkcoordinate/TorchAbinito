#include <iostream>
#include <E.hpp>

int main()
{
	vector<double> origin = {1.0, 2.0, 3.0};
	vector<int> shell = {0, 0, 0};
	vector<double> myExps = {3.42525091, 0.62391373, 0.16885540};
	vector<double> myCoefs = {0.15432897, 0.53532814, 0.44463454};
	BasisFunction a(myExps, myCoefs, origin, shell);
	cout << S(a, a);
}