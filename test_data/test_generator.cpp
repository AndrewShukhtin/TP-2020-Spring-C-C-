#include <iostream>
#include <fstream>
#include <random>

int main(void) {
  const std::string relative_path{"test_data/"};
  std::string filename;
  std::cin >> filename;

  std::ofstream file(relative_path + filename);
  size_t dim = 0;
  std::cin >> dim;
  file << dim << std::endl;

  size_t data_size = 0;
  std::cin >> data_size;
  file << data_size << std::endl;

  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<> dist{0, 100};
  for (size_t coord_idx = 0; coord_idx < dim; ++coord_idx) {
    for (size_t idx = 0; idx < data_size; ++idx) {
      const double val = (dist(gen) - 10.0) / ((dist(gen) + 1.0) * 0.5);

      file << std::fixed << std::setprecision(3) << val << " ";
    }
    file << std::endl;
  }

  file.close();

  return EXIT_SUCCESS;
}