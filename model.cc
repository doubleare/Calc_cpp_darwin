#include "model.h"

void s21::Model::calc_new_expression(st_tp str, double x_val) {
  calc.newExpression(str, x_val);
  calc.just_calculation();
}

void s21::Model::calc_new_cred(double sum, int month, double percent,
                               int credit_type) {
  calc.cred_calculation(sum, month, percent, credit_type);
}

void s21::Model::calc_new_graph(st_tp exp, int start, int end, double step) {
  calc.newExpression(exp, start);
  calc.graph_calculation(start, end, step);
}
