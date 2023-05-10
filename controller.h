#ifndef SMART_V2_SRC_CONTROLLER_H
#define SMART_V2_SRC_CONTROLLER_H

#include "model.h"

namespace s21 {

class Controller {
 public:
  using gr_tp = std::pair<std::vector<double>, std::vector<double>>;
  using st_tp = std::string;

  Controller(Model* n_model) : md(n_model){};
  double calc_expression(st_tp exp, double x_val = 0) {
    md->calc_new_expression(exp, x_val);
    return md->get_res_calc();
  }
  st_tp cred_params(double sum, int month, double percent, int credit_type) {
    md->calc_new_cred(sum, month, percent, credit_type);
    return md->get_res_cred();
  };
  gr_tp calc_graph(st_tp exp, int start, int end, double step) {
    md->calc_new_graph(exp, start, end, step);
    return md->get_res_graph();
  };

 private:
  Model* md;
};

}  // namespace s21

#endif  // SMART_V2_SRC_CONTROLLER_H
