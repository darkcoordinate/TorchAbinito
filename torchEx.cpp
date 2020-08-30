#include <iostream>
#include <torch/torch.h>

int main() {
  torch::Tensor tensor = torch::rand({2, 3});
  std::cout << tensor[0][2] << std::endl;
  std::cout << tensor << std::endl;
}