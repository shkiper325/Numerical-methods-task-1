#ifndef HATS_HPP
#define HATS_HPP

#include <vector>
#include <functional>

std::vector<std::vector<double> >gen_diag(int N);
std::vector<double> gen_f(int N, int point_count, std::function<double(double)> f);
std::vector<std::vector<double> > set_initial_cond(std::vector<std::vector<double> > diag, std::vector<double> f);

#endif