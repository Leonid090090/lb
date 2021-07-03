#ifndef HISOGRAM_H_INCLUDED
#define HISOGRAM_H_INCLUDED
#include <vector>

using namespace std;

vector<double>
input_numbers(istream& in, size_t count);

void find_minmax(const vector<double> numbers, double& min, double& max);
struct Input {
    vector<double> numbers;
    size_t bin_count;
};

void
show_histogram_text(const vector<size_t>& bins);

vector<size_t> make_histogram(Input data);





#endif // HISOGRAM_H_INCLUDED
