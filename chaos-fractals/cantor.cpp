// cantor.cpp : recursively generate subsections of the cantor set
#include <iostream>
#include <cmath>
#include <vector>

#pragma GCC optimize("Ofast,unroll-loops")

class Cantor {
	public:
		void generate(std::vector<int>& x, int start, int size, int iter) {
			if (iter == 1) return;
			int a, b;
			a = static_cast<int>(size / 3);
			b = static_cast<int>(2 * size / 3);
			for (int i = 0; i < size; ++i) {
				if (start + a <= i + start && i + start < start + b) {
					x[i + start] = 0;
				}
			}
			generate(x, start, size / 3, iter - 1);
			generate(x, start + b, size / 3, iter - 1);
		}

		std::vector<int> build(std::vector<int> x, int layers, int type) {
			if (x.size() % 3 != 0) std::cout << "Results may not be ideal; use sizes thats are a power of 3" << std::endl;
			std::vector<std::vector<int> > tree(layers, x);
			for (int i = 0; i < layers; ++i) {
				generate(tree[i], 0, x.size(), i + 1);
			}
			for (int i = 0; i < layers; ++i) {
				for (int j = 0; j < x.size(); ++j) {
					if (type == 0) std::cout << tree[i][j] << " ";
					else if (type == 1) {
						if (tree[i][j] == 0) std::cout << " ";
						else std::cout << "\u2588";
					}
				}
				std::cout << std::endl;
			}
			return tree[layers - 1];
		}
};

int main(int argc, char** argv) {
	int size;
	std::cout << "Layers: ";
	std::cin >> size;
	size = pow(3, size - 1);
	std::vector<int> x(size, 1);
	Cantor C;
	std::vector<int> ret;
	ret = C.build(x, static_cast<int>(logf(x.size()) / logf(3) + 1), 1);
	std::cout << std::endl << std::endl;
	for (auto& item : ret) {
		std::cout << item << " ";
	}
	std::cout << std::endl;
	return 0;
}