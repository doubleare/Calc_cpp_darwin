#ifndef SMART_V2_SRC_CALCULATOR_H
#define SMART_V2_SRC_CALCULATOR_H

#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <vector>

namespace s21 {

enum type { OPERATOR, FUNC, NUMBER };

struct element {
  type tp;
  char oper;
  int priority;
  double num;
};

class Calculator {
 public:
  using gr_tp = std::pair<std::vector<double>, std::vector<double>>;
  using ls_tp = std::list<element>;
  using st_tp = std::string;

  Calculator(){};

  void newExpression(st_tp str, double val_x = 0);
  void just_calculation();
  void graph_calculation(int start, int end, double step);
  void cred_calculation(double sum, int month, double percent, int credit_type);

  gr_tp get_res_graph() const noexcept { return graph_result; };
  st_tp get_res_cred() const noexcept { return cred_result; };
  double get_res_calc() const noexcept { return calc_result; };

 private:
  ls_tp deiks;
  st_tp expression, cred_result;
  gr_tp graph_result;
  double calc_result, x;

  void from_str_to_deiks();
  double get_num_from_str(st_tp *str);
  void ops_to_stack(char o, ls_tp *lt);
  void calculate();
  double solve_o(double v1, double v2, char op);
  double solve_f(double v1, char op);
  void replace_words();
  void replace_x(st_tp *str);
  void move(ls_tp *from, ls_tp *to);
};

}  // namespace s21

#endif  // SMART_V2_SRC_CALCULATOR_H