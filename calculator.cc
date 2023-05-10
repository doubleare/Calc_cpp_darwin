#include "calculator.h"

void s21::Calculator::newExpression(st_tp str, double val_x) {
  deiks.clear();
  expression = str;
  replace_words();
  x = val_x;
}

void s21::Calculator::cred_calculation(double sum, int month, double percent,
                                       int credit_type) {
  cred_result.clear();
  if (sum <= 0 || month <= 0) {
    throw std::invalid_argument("invalid_argument");
  } else {
    double stv = percent / 100.0 / 12.0;
    double month_pay = 0, total_pay = 0, pereplata = 0;
    if (credit_type == 2) {
      month_pay = sum * (stv + (stv / (pow(1 + stv, month) - 1)));
      total_pay = month_pay * month;
      pereplata = total_pay - sum;
    } else {
      double tmp = sum, b = sum / month, PP = 0;
      for (int i = 0; i < month; i++) {
        PP = tmp * stv;
        month_pay = b + PP;
        if (i == 0) cred_result = std::to_string(month_pay) + "...";
        total_pay += month_pay;
        tmp -= b;
      }
      pereplata = total_pay - sum;
    }
    cred_result = cred_result + std::to_string(month_pay) + " " +
                  std::to_string(pereplata) + " " + std::to_string(total_pay);
  }
}

void s21::Calculator::just_calculation() {
  from_str_to_deiks();
  calculate();
}

void s21::Calculator::graph_calculation(int start, int end, double step) {
  graph_result.first.clear();
  graph_result.second.clear();
  for (x = start; x <= end; x += step) {
    graph_result.first.push_back(x);
    just_calculation();
    graph_result.second.push_back(get_res_calc());
  }
}

void s21::Calculator::from_str_to_deiks() {
  deiks.clear();
  ls_tp st, tp;
  st_tp str = expression;
  int f = 0;

  replace_x(&str);

  for (auto it = str.begin(); !str.empty(); it = str.begin()) {
    if ((*it >= '0' && *it <= '9') || ((*it == '-' || *it == '+') && f == 0)) {
      deiks.push_back({NUMBER, '0', 0, get_num_from_str(&str)});
      f++;
    } else {
      ops_to_stack(*it, &tp);
      str.erase(str.begin());
      if (tp.back().tp == FUNC || tp.back().priority == -1) {
        st.push_back(tp.back());
        f = 0;
      } else if (tp.back().priority == -2) {
        f++;
        while (!st.empty() && st.back().priority != -1) move(&st, &deiks);
        st.pop_back();
        if (!st.empty()) {
          while (!st.empty() && st.back().tp == FUNC) move(&st, &deiks);
        }
      } else if (tp.back().tp == OPERATOR) {
        if (!st.empty()) {
          while (st.back().priority >= tp.back().priority) {
            move(&st, &deiks);
            if (st.empty()) break;
          }
        }
        st.push_back(tp.back());
      }
      tp.pop_back();
    }
  }
  while (!st.empty()) move(&st, &deiks);
  deiks.reverse();
}

double s21::Calculator::get_num_from_str(st_tp *str) {
  std::size_t pos = 0;

  double res = std::stod(*str, &pos);
  str->erase(str->begin(), str->begin() + pos);

  return res;
}

void s21::Calculator::ops_to_stack(char o, ls_tp *lt) {
  int pr = 0;
  type t = OPERATOR;
  if (o >= 'a' && o <= 'z') {
    t = FUNC;
    pr = 3;
  } else if (o == '(') {
    pr = -1;
  } else if (o == ')') {
    pr = -2;
  } else if (o == '+' || o == '-') {
    pr = 1;
  } else if (o == '*' || o == '/') {
    pr = 2;
  } else if (o == '^' || o == '%') {
    pr = 4;
  } else {
    throw std::invalid_argument("invalid_argument");
  }
  lt->push_back({t, o, pr, 0});
}

void s21::Calculator::calculate() {
  ls_tp tmp;
  double res = 0;
  for (; !deiks.empty();) {
    if (deiks.back().tp == NUMBER) {
      res = deiks.back().num;
      move(&deiks, &tmp);
    } else if (deiks.back().tp == OPERATOR) {
      double val2 = tmp.back().num, val1 = (*-- --tmp.end()).num;
      tmp.pop_back();
      tmp.pop_back();
      res = solve_o(val1, val2, deiks.back().oper);
      deiks.pop_back();
      tmp.push_back({NUMBER, '0', 0, res});
    } else if (deiks.back().tp == FUNC) {
      double v = tmp.back().num;
      tmp.pop_back();
      res = solve_f(v, deiks.back().oper);
      deiks.pop_back();
      tmp.push_back({NUMBER, '0', 0, res});
    }
  }
  tmp.pop_back();
  calc_result = res;
}

double s21::Calculator::solve_o(double v1, double v2, char op) {
  double res = 0;
  switch (op) {
    case '+':
      res = v1 + v2;
      break;
    case '-':
      res = v1 - v2;
      break;
    case '*':
      res = v1 * v2;
      break;
    case '/':
      res = v1 / v2;
      break;
    case '^':
      res = pow(v1, v2);
      break;
    case '%':
      res = fmod(v1, v2);
      break;
    default:
      break;
  }
  return res;
}

double s21::Calculator::solve_f(double v1, char op) {
  double res = 0;
  switch (op) {
    case 's':
      res = sin(v1);
      break;
    case 't':
      res = tan(v1);
      break;
    case 'c':
      res = cos(v1);
      break;
    case 'k':
      res = acos(v1);
      break;
    case 'z':
      res = asin(v1);
      break;
    case 'd':
      res = atan(v1);
      break;
    case 'q':
      res = sqrt(v1);
      break;
    case 'g':
      res = log10(v1);
      break;
    case 'l':
      res = log(v1);
      break;
    default:
      break;
  }
  return res;
}

void s21::Calculator::replace_words() {
  std::map<st_tp, st_tp> wrd_to_repl = {
      {"acos", "k"}, {"asin", "z"}, {"atan", "d"}, {"sin", "s"}, {"cos", "c"},
      {"tan", "t"},  {"sqrt", "q"}, {"ln", "l"},   {"log", "g"}, {"mod", "%"}};

  std::size_t pos = 0;

  for (const auto &[key, value] : wrd_to_repl) {
    if ((pos = expression.find(key)) != st_tp::npos) {
      auto iter = expression.begin() + pos;
      expression.replace(iter, iter + key.length(), value);
    }
  }
}

void s21::Calculator::replace_x(st_tp *str) {
  for (std::size_t pos = str->find("x"); pos != st_tp::npos;) {
    auto iter = str->begin() + (pos - 1);
    st_tp tmp = std::to_string(x);
    double t_x = x;
    if (x < 0) {
      tmp.clear();
      if (*iter == '-' || *iter == '+') {
        t_x = -t_x;
        tmp = std::to_string(t_x);
        if (*iter == '+') *iter = '-';
      } else {
        tmp = '(' + std::to_string(x) + ')';
      }
    }
    str->replace(pos, 1, tmp);
    pos = str->find("x");
  }
}

void s21::Calculator::move(ls_tp *from, ls_tp *to) {
  to->push_back(from->back());
  from->pop_back();
}
