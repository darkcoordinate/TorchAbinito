#include <iostream>
#include <torch/torch.h>
using namespace std;

#define TOLERANCE 1.0e-10
double hyperGeometric(double a, double c, double x)
{
  double term = a * x / c;
  double value = 1.0 + term;
  int n = 1;

  while (abs(term) > TOLERANCE)
  {
    a++, c++, n++;
    term *= a * x / c / n;
    value += term;
  }
  return value;
}

torch::Tensor hyperGeometric(torch::Tensor a, torch::Tensor c, torch::Tensor x)
{
  torch::Tensor term = a * x / c;
  torch::Tensor value = 1.0 + term;
  double n = 1;
  while (torch::min(torch::abs(term)).item<double>() > TOLERANCE)
  {
    a += 1;
    c += 1;
    n += 1;
    term *= a * x / c / n;
    value += term;
  }
  return value;
}

torch::Tensor hyp1f1(torch::Tensor a, torch::Tensor c, torch::Tensor xin)
{
  double RECUR_BIG = 1.0e+50;
  const double nmax = 5000;
  double n = 3;
  const torch::Tensor x = -xin;
  const torch::Tensor x3 = x * x * x;
  const torch::Tensor t0 = a / c;
  const torch::Tensor t1 = (a + 1.0) / (2.0 * c);
  const torch::Tensor t2 = (a + 2.0) / (2.0 * (c + 1.0));

  torch::Tensor F = torch::ones(t1.sizes());
  torch::Tensor prec = torch::zeros(t1.sizes());

  torch::Tensor Bnm3 = torch::ones(t1.sizes());
  torch::Tensor Bnm2 = 1.0 + t1 * x;
  torch::Tensor Bnm1 = 1.0 + t2 * x * (1.0 + t1 / 3.0 * x);
  torch::Tensor Anm3 = torch::ones(t1.sizes());
  torch::Tensor Anm2 = Bnm2 - t0 * x;
  torch::Tensor Anm1 = Bnm1 - t0 * (1.0 + t2 * x) * x + t0 * t1 * (c / (c + 1.0)) * x * x;
  cout << Anm2 << endl;
  while (1)
  {
    torch::Tensor npam1 = n + a - 1;
    torch::Tensor npcm1 = n + c - 1;
    torch::Tensor npam2 = n + a - 2;
    torch::Tensor npcm2 = n + c - 2;
    torch::Tensor tnm1 = (2 * n - 1) * torch::ones(t1.sizes());
    torch::Tensor tnm3 = (2 * n - 3) * torch::ones(t1.sizes());
    torch::Tensor tnm5 = (2 * n - 5) * torch::ones(t1.sizes());
    torch::Tensor F1 = (n - a - 2) / (2 * tnm3 * npcm1);
    torch::Tensor F2 = (n + a) * npam1 / (4 * tnm1 * tnm3 * npcm2 * npcm1);
    torch::Tensor F3 = -npam2 * npam1 * (n - a - 2) / (8 * tnm3 * tnm3 * tnm5 * (n + c - 3) * npcm2 * npcm1);
    torch::Tensor E = -npam1 * (n - c - 1) / (2 * tnm3 * npcm2 * npcm1);

    torch::Tensor An = (1.0 + F1 * x) * Anm1 + (E + F2 * x) * x * Anm2 + F3 * x3 * Anm3;
    torch::Tensor Bn = (1.0 + F1 * x) * Bnm1 + (E + F2 * x) * x * Bnm2 + F3 * x3 * Bnm3;
    torch::Tensor r = An / Bn;

    prec = torch::abs((F - r) / F);
    F = r;

    if (torch::min(prec).item<double>() < TOLERANCE || n > nmax)
      break;

    if (torch::max(torch::abs(An)).item<double>() > RECUR_BIG || torch::max(torch::abs(Bn)).item<double>() > RECUR_BIG)
    {
      std::cout << "hello2" << std::endl;
      An /= RECUR_BIG;
      Bn /= RECUR_BIG;
      Anm1 /= RECUR_BIG;
      Bnm1 /= RECUR_BIG;
      Anm2 /= RECUR_BIG;
      Bnm2 /= RECUR_BIG;
      Anm3 /= RECUR_BIG;
      Bnm3 /= RECUR_BIG;
    }
    else if (torch::min(torch::abs(An)).item<double>() < 1.0 / RECUR_BIG || torch::min(torch::abs(Bn)).item<double>() < 1.0 / RECUR_BIG)
    {
      std::cout << "hello3" << std::endl;
      An *= RECUR_BIG;
      Bn *= RECUR_BIG;
      Anm1 *= RECUR_BIG;
      Bnm1 *= RECUR_BIG;
      Anm2 *= RECUR_BIG;
      Bnm2 *= RECUR_BIG;
      Anm3 *= RECUR_BIG;
      Bnm3 *= RECUR_BIG;
    }

    n++;
    Bnm3 = Bnm2;
    Bnm2 = Bnm1;
    Bnm1 = Bn;
    Anm3 = Anm2;
    Anm2 = Anm1;
    Anm1 = An;
  }
  return F;
}

double hyperg_1F1_luke(const double a, const double c, const double xin)
{
  const double RECUR_BIG = 1.0e+50;
  const double nmax = 5000;
  double n = 3;
  const double x = -xin;
  const double x3 = x * x * x;
  const double t0 = a / c;
  const double t1 = (a + 1.0) / (2.0 * c);
  const double t2 = (a + 2.0) / (2.0 * (c + 1.0));
  double F = 1.0;
  double prec;

  double Bnm3 = 1.0;
  double Bnm2 = 1.0 + t1 * x;
  double Bnm1 = 1.0 + t2 * x * (1.0 + t1 / 3.0 * x);
  double Anm3 = 1.0;
  double Anm2 = Bnm2 - t0 * x;
  double Anm1 = Bnm1 - t0 * (1.0 + t2 * x) * x + t0 * t1 * (c / (c + 1.0)) * x * x;
  while (1)
  {
    double npam1 = n + a - 1;
    double npcm1 = n + c - 1;
    double npam2 = n + a - 2;
    double npcm2 = n + c - 2;
    double tnm1 = 2 * n - 1;
    double tnm3 = 2 * n - 3;
    double tnm5 = 2 * n - 5;
    double F1 = (n - a - 2) / (2 * tnm3 * npcm1);
    double F2 = (n + a) * npam1 / (4 * tnm1 * tnm3 * npcm2 * npcm1);
    double F3 = -npam2 * npam1 * (n - a - 2) / (8 * tnm3 * tnm3 * tnm5 * (n + c - 3) * npcm2 * npcm1);
    double E = -npam1 * (n - c - 1) / (2 * tnm3 * npcm2 * npcm1);

    double An = (1.0 + F1 * x) * Anm1 + (E + F2 * x) * x * Anm2 + F3 * x3 * Anm3;
    double Bn = (1.0 + F1 * x) * Bnm1 + (E + F2 * x) * x * Bnm2 + F3 * x3 * Bnm3;
    double r = An / Bn;

    prec = fabs((F - r) / F);
    F = r;

    if (prec < TOLERANCE || n > nmax)
      break;

    if (fabs(An) > RECUR_BIG || fabs(Bn) > RECUR_BIG)
    {

      An /= RECUR_BIG;
      Bn /= RECUR_BIG;
      Anm1 /= RECUR_BIG;
      Bnm1 /= RECUR_BIG;
      Anm2 /= RECUR_BIG;
      Bnm2 /= RECUR_BIG;
      Anm3 /= RECUR_BIG;
      Bnm3 /= RECUR_BIG;
    }
    else if (fabs(An) < 1.0 / RECUR_BIG || fabs(Bn) < 1.0 / RECUR_BIG)
    {
      An *= RECUR_BIG;
      Bn *= RECUR_BIG;
      Anm1 *= RECUR_BIG;
      Bnm1 *= RECUR_BIG;
      Anm2 *= RECUR_BIG;
      Bnm2 *= RECUR_BIG;
      Anm3 *= RECUR_BIG;
      Bnm3 *= RECUR_BIG;
    }

    n++;
    Bnm3 = Bnm2;
    Bnm2 = Bnm1;
    Bnm1 = Bn;
    Anm3 = Anm2;
    Anm2 = Anm1;
    Anm1 = An;
  }
  return F;
}
torch::Tensor boys(torch::Tensor n, torch::Tensor T)
{
  return hyperGeometric(n + 0.5, n + 1.5, T) / (2.0 * n + 1.0);
}

double boys(double n, double T)
{
  return hyperGeometric(n + 0.5, n + 1.5, T) / (2.0 * n + 1.0);
}
int main()
{
  torch::Tensor tensor = torch::tensor({2.0, 3.0});
  torch::Tensor tensor2 = torch::tensor({8.0, 5.0});
  torch::Tensor tensor3 = torch::tensor({0.5, 0.5});
  std::cout << tensor << std::endl;
  std::cout << tensor2 << std::endl;
  std::cout << tensor2 * tensor << std::endl;
  std::cout << torch::ones(tensor.sizes()) << std::endl;
  std::cout << torch::min(tensor2).item<double>() << std::endl;
  std::cout << hyperg_1F1_luke(8, 2, 0.5) << std::endl;
  std::cout << hyperg_1F1_luke(5, 3, 0.5) << std::endl;
  std::cout << hyp1f1(tensor2, tensor, tensor3);
  cout << hyperGeometric(tensor2, tensor, tensor3);
}
