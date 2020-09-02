#include "E.hpp"
double E(int i, int j, int t, double Qx, double a, double b)
{
    /* Recursive definition of Hermite Gaussian coefficients.
        Returns a float.
        a: orbital exponent on Gaussian 'a' (e.g. alpha in the text)
        b: orbital exponent on Gaussian 'b' (e.g. beta in the text)
        i,j: orbital angular momentum number on Gaussian 'a' and 'b'
        t: number nodes in Hermite (depends on type of integral, 
           e.g. always zero for overlap integrals)
        Qx: distance between origins of Gaussian 'a' and 'b'
    */
    double p = a + b;
    double q = a * b / p;
    if ((t < 0) or (t > (i + j)))
    {
        // out of bounds for t
        return 0.0;
    }
    else if (i == j == t == 0)
    {
        // base case
        return exp(-q * Qx * Qx);
    }
    else if (j == 0)
    {
        //decrement index i
        return (1 / (2 * p)) * E(i - 1, j, t - 1, Qx, a, b) -
               (q * Qx / a) * E(i - 1, j, t, Qx, a, b) +
               (t + 1) * E(i - 1, j, t + 1, Qx, a, b);
    }
    else
    {
        // decrement index j
        return (1 / (2 * p)) * E(i, j - 1, t - 1, Qx, a, b) +
               (q * Qx / b) * E(i, j - 1, t, Qx, a, b) +
               (t + 1) * E(i, j - 1, t + 1, Qx, a, b);
    }
}

double overlap(double a, vector<int> lmn1, vector<double> A, double b, vector<int> lmn2, vector<double> B)
{
    /**  Evaluates overlap integral between two Gaussians
        Returns a float.
        a:    orbital exponent on Gaussian 'a' (e.g. alpha in the text)
        b:    orbital exponent on Gaussian 'b' (e.g. beta in the text)
        lmn1: int tuple containing orbital angular momentum (e.g. (1,0,0))
              for Gaussian 'a'
        lmn2: int tuple containing orbital angular momentum for Gaussian 'b'
        A:    list containing origin of Gaussian 'a', e.g. [1.0, 2.0, 0.0]
        B:    list containing origin of Gaussian 'b'
    */
    int l1 = lmn1[0]; // shell angular momentum on Gaussian 'a'
    int m1 = lmn1[1];
    int n1 = lmn1[2];
    int l2 = lmn2[0]; // shell angular momentum on Gaussian 'b'
    int m2 = lmn2[1];
    int n2 = lmn2[2];
    double S1 = E(l1, l2, 0, A[0] - B[0], a, b); // X
    double S2 = E(m1, m2, 0, A[1] - B[1], a, b); // Y
    double S3 = E(n1, n2, 0, A[2] - B[2], a, b); // Z
    return S1 * S2 * S3 * pow(M_PI / (a + b), 1.5);
}

double fact2(double f)
{
    if (f == 0)
    {
        return 1.0;
    }
    return f * fact2(f - 1.0);
}

double S(BasisFunction a, BasisFunction b)
{
    /**Evaluates overlap between two contracted Gaussians
       Returns float.
       Arguments:
       a: contracted Gaussian 'a', BasisFunction object
       b: contracted Gaussian 'b', BasisFunction object
    */
    double s = 0.0;
    for (size_t ia = 0; ia < a.coefs.size(); ia++)
    {
        for (size_t ib = 0; ib < b.coefs.size(); ib++)
        {
            s += a.norm[ia] * b.norm[ib] * a.coefs[ia] * b.coefs[ib] *
                 overlap(a.exps[ia], a.shell, a.origin,
                         b.exps[ib], b.shell, b.origin);
        }
    }
    return s;
}