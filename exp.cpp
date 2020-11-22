#include <iostream>
#include <E.hpp>

int main()
{
	vector<double> origin = {0.7, 0.0, 0.0};
	vector<double> origin2 = {-0.7, 0.0, 0.0};
	vector<int> shell = {0, 0, 0};
	vector<double> myExps = {3.42525091, 0.62391373, 0.16885540};
	vector<double> myCoefs = {0.15432897, 0.53532814, 0.44463454};
	BasisFunction a(myExps, myCoefs, origin, shell);
	BasisFunction b(myExps, myCoefs, origin2, shell);
	a.print();
	a.normalize();
	b.normalize();
	cout << "printing exps";
	cout << S(a, b);
}