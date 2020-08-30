#include <memory>
#include <math.h>
#include <vector>
using namespace std;
double E(int i, int j, int t, double Qx, double a, double b);
double overlap(double a, shared_ptr<int> lmn1, shared_ptr<double> A,
               double b, shared_ptr<int> lmn2, shared_ptr<double> B);

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
    double norm;
    vector<double> normalize;
    BasisFunction(vector<double> exps, vector<double> coefs, vector<double> origin = {0.0, 0.0, 0.0}, vector<int> shell = {0, 0, 0})
    {
        this->origin = origin;
        this->shell = shell;
        this->exps = exps;
        this->coefs = coefs;
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
        this->norm = sqrt(pow(2,2*(l+m+n)+1.5)*
                        pow(this->exps,l+m+n+1.5)/
                        fact2(2*l-1)/fact2(2*m-1)/
                        fact2(2*n-1)/pow(np.pi,1.5))

//now normalize the contracted basis functions(CGBFs)
//Eq.1.44 of Valeev integral whitepaper
        prefactor = pow(np.pi,1.5)*\
            fact2(2*l - 1)*fact2(2*m - 1)*fact2(2*n - 1)/pow(2.0,L)

        N = 0.0
        num_exps = len(self.exps)
        for ia in range(num_exps):
            for ib in range(num_exps):
                N += self.norm[ia]*self.norm[ib]*self.coefs[ia]*self.coefs[ib]/\
                         np.power(self.exps[ia] + self.exps[ib],L+1.5)

        N *= prefactor
        N = np.power(N,-0.5)
        for ia in range(num_exps):
            self.coefs[ia] *= N
    }
