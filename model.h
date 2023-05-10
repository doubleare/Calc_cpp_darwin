#ifndef SMART_V2_SRC_MODEL_H
#define SMART_V2_SRC_MODEL_H

#include "calculator.h"

namespace s21 {

class Model {
 public:
  using gr_tp = std::pair<std::vector<double>, std::vector<double>>;
  using st_tp = std::string;

  Model(){};

  void calc_new_expression(st_tp str, double x_val = 0);
  void calc_new_cred(double sum, int month, double percent, int credit_type);
  void calc_new_graph(st_tp exp, int start, int end, double step);
  double get_res_calc() { return calc.get_res_calc(); };
  gr_tp get_res_graph() { return calc.get_res_graph(); };
  st_tp get_res_cred() { return calc.get_res_cred(); };

 private:
  Calculator calc;
};

}  // namespace s21

#endif  // SMART_V2_SRC_CONTROLLER_H
