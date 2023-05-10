#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      main_cn(&md),
      form(&main_cn),
      graphx(&main_cn) {
  ui->setupUi(this);

  connects();

  ui->x_val->setPlaceholderText("x value");
  ui->x_val->setValidator(new QDoubleValidator(this));
  x_disable(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::textToL(QString txt) {
  if (ui->label->text().isEmpty())
    ui->label->setText(txt);
  else
    ui->label->setText(ui->label->text() + txt);
}

void MainWindow::print_num() {
  QPushButton *btn = (QPushButton *)sender();
  if (last_o != -2 && is_x == 0) {
    textToL(btn->text());
    reset(is_x, is_d, 0, 1, bre);
  }
}

void MainWindow::print_x() {
  QPushButton *btn = (QPushButton *)sender();
  if (is_x == 0 && is_d == 0 && last_o != 0 && last_o != -2) {
    x_disable(false);
    textToL(btn->text());
    reset(1, is_d, 0, 1, bre);
  }
}

void MainWindow::del() {
  QString str = ui->label->text();
  if (!str.isEmpty()) {
    if (str.endsWith("mod"))
      str.truncate(str.size() - 3);
    else
      str.truncate(str.size() - 1);
    ui->label->setText(str);
  }
}

void MainWindow::clear() {
  if (!ui->label->text().isEmpty()) {
    ui->label->setText("");
    reset(0, 0, -1, 0, 0);
    x_disable(true);
  }
}

void MainWindow::print_opers() {
  QPushButton *btn = (QPushButton *)sender();
  if (last_o != 4) {
    if ((n_ex == 0 || n_ex == 2) &&
        (btn->text() == '-' || btn->text() == '+')) {
      if (ui->label->text().isEmpty())
        ui->label->setText(btn->text());
      else {
        if (n_ex == 2) del();
        ui->label->setText(ui->label->text() + btn->text());
      }
      n_ex = 2;
    } else if (!ui->label->text().isEmpty() &&
               !ui->label->text().endsWith(btn->text()) && n_ex == 1) {
      if (last_o == 1) del();
      ui->label->setText(ui->label->text() + btn->text());
    }
    reset(0, 0, 1, n_ex, bre);
  }
}

void MainWindow::print_dot() {
  if (last_o == 0 && is_d == 0 && is_x == 0) {
    ui->label->setText(ui->label->text() + '.');
    reset(is_x, 1, 4, n_ex, bre);
  }
}

void MainWindow::open_bre() {
  QPushButton *btn = (QPushButton *)sender();
  if (last_o != 0 && last_o != 4 && last_o != -2) {
    textToL(btn->text());
    reset(is_x, is_d, 2, 0, bre + 1);
  }
}

void MainWindow::close_bre() {
  QPushButton *btn = (QPushButton *)sender();
  if (!ui->label->text().isEmpty() && last_o != 2 && bre > 0 && last_o != 1 &&
      last_o != 4) {
    ui->label->setText(ui->label->text() + btn->text());
    reset(is_x, is_d, -2, n_ex, bre - 1);
  }
}

void MainWindow::print_func() {
  QPushButton *btn = (QPushButton *)sender();
  if (last_o == 1 || last_o == 2 || last_o == -1) {
    textToL(btn->text());
    ui->op_b->click();
  }
}

void MainWindow::placeHold(QString r) {
  ui->label->setPlaceholderText(r);
  ui->C->click();
}

void MainWindow::on_res() {
  if (last_o == 0 || last_o == -2) {
    if (bre > 0)
      for (; bre > 0; bre--) ui->label->setText(ui->label->text() + ")");
    if (!ui->label->text().isEmpty()) {
      QString r = QString::number(main_cn.calc_expression(
          ui->label->text().toStdString(), ui->x_val->text().toDouble()));
      x_disable(true);
      graphx.close();
      is_d = r.contains('.') ? 1 : 0;
      reset(0, is_d, 0, 1, 0);
      if (r == "nan" || r == "inf" || r == "0" || r == "-inf")
        placeHold(r);
      else
        ui->label->setText(r);
    }
  }
}

void MainWindow::on_credit() { form.show(); }

void MainWindow::on_graph() {
  if (bre > 0)
      for (; bre > 0; bre--) ui->label->setText(ui->label->text() + ")");
  graphx.get_data(ui->label->text());
  if (graphx.isVisible()) {
    graphx.new_draw();
  } else {
    graphx.show();
    graphx.new_draw();
  }
}

void MainWindow::x_disable(bool tf) {
  ui->graph->setDisabled(tf);
  ui->x_val->setDisabled(tf);
}

void MainWindow::reset(int x, int d, int l, int n, int b) {
  is_x = x;
  is_d = d;
  last_o = l;
  n_ex = n;
  bre = b;
}

void MainWindow::connects() {
  connect(ui->one, SIGNAL(clicked()), this, SLOT(print_num()));
  connect(ui->two, SIGNAL(clicked()), this, SLOT(print_num()));
  connect(ui->three, SIGNAL(clicked()), this, SLOT(print_num()));
  connect(ui->four, SIGNAL(clicked()), this, SLOT(print_num()));
  connect(ui->five, SIGNAL(clicked()), this, SLOT(print_num()));
  connect(ui->six, SIGNAL(clicked()), this, SLOT(print_num()));
  connect(ui->seven, SIGNAL(clicked()), this, SLOT(print_num()));
  connect(ui->eight, SIGNAL(clicked()), this, SLOT(print_num()));
  connect(ui->nine, SIGNAL(clicked()), this, SLOT(print_num()));
  connect(ui->zero, SIGNAL(clicked()), this, SLOT(print_num()));
  connect(ui->x, SIGNAL(clicked()), this, SLOT(print_x()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(print_dot()));
  connect(ui->op_b, SIGNAL(clicked()), this, SLOT(open_bre()));
  connect(ui->cl_b, SIGNAL(clicked()), this, SLOT(close_bre()));
  connect(ui->div, SIGNAL(clicked()), this, SLOT(print_opers()));
  connect(ui->mult, SIGNAL(clicked()), this, SLOT(print_opers()));
  connect(ui->minus, SIGNAL(clicked()), this, SLOT(print_opers()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(print_opers()));
  connect(ui->step, SIGNAL(clicked()), this, SLOT(print_opers()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(print_opers()));
  connect(ui->C, SIGNAL(clicked()), this, SLOT(clear()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(print_func()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(print_func()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(print_func()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(print_func()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(print_func()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(print_func()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(print_func()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(print_func()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(print_func()));
  connect(ui->credit, SIGNAL(clicked()), this, SLOT(on_credit()));
  connect(ui->res, SIGNAL(clicked()), this, SLOT(on_res()));
  connect(ui->graph, SIGNAL(clicked()), this, SLOT(on_graph()));
}
