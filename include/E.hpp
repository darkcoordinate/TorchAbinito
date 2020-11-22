#include <iostream>
#include <memory>
#include <math.h>
#include <vector>
using namespace std;
double E(int i, int j, int t, double Qx, double a, double b);
double overlap(double a, shared_ptr<int> lmn1, shared_ptr<double> A,
               double b, shared_ptr<int> lmn2, shared_ptr<double> B);
double fact2(double f);
class BasisFunction
{
    /** A class that contains all our basis function data
        Attributes:
        origin: array/list containing the coordinates of the Gaussian origin
        shell:  tuple of angular momentum
        exps:   list of primitive Gaussian exponents
        coefs:  list of primitive Gaussian coefficients
        norm:   list of normalization factors for Gaussian primitives
        */

public:
    vector<double> origin;
    vector<int> shell;
    vector<double> exps;
    vector<double> coefs;
    vector<double> norm;
    BasisFunction(vector<double> exps, vector<double> coefs, vector<double> origin = {0.0, 0.0, 0.0}, vector<int> shell = {0, 0, 0}) : norm(coefs.size())
    {
        this->origin = origin;
        this->shell = shell;
        this->exps = exps;
        this->coefs = coefs;
    }

    void print()
    {
        cout << "\ncoefs: ";
        for (auto i : this->coefs)
        {
            cout << i << " ";
        }
        cout << "\nexps: ";
        for (auto i : this->exps)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    void normalize()
    {
        /* Routine to normalize the basis functions, in case they
            do not integrate to unity.
        */
        int l = this->shell[0];
        int m = this->shell[1];
        int n = this->shell[2];
        int L = l + m + n;
        //self.norm is a list of length equal to number primitives
        //normalize primitives first(PGBFs)
        for (size_t i = 0; i < this->norm.size(); i++)
        {
            this->norm[i] = sqrt((pow(2, 2 * (l + m + n) + 1.5) *
                                  pow(this->exps[i], l + m + n + 1.5)) /
                                 (fact2(2 * l - 1) * fact2(2 * m - 1) *
                                  fact2(2 * n - 1) * pow(M_PI, 1.5)));
        }

        //now normalize the contracted basis functions(CGBFs)
        //Eq.1.44 of Valeev integral whitepaper
        double prefactor = pow(M_PI, 1.5) *
                           fact2(2 * l - 1) * fact2(2 * m - 1) * fact2(2 * n - 1) / pow(2.0, L);

        double N = 0.0;
        size_t num_exps = this->exps.size();
        for (size_t ia = 0; ia < num_exps; ia++)
        {
            for (size_t ib = 0; ib < num_exps; ib++)
            {
                N += this->norm[ia] * this->norm[ib] * this->coefs[ia] * this->coefs[ib] /
                     pow(this->exps[ia] + this->exps[ib], L + 1.5);
            }
        }

        N *= prefactor;
        N = pow(N, -0.5);
        for (size_t ia = 0; ia < num_exps; ia++)
        {
            this->coefs[ia] *= N;
        }
    }
};
double S(BasisFunction a, BasisFunction b);
