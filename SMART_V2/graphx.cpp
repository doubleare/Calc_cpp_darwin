#include "graphx.h"

#include "ui_graphx.h"

GraphX::GraphX(s21::Controller *control, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GraphX), cn(control) {
  ui->setupUi(this);

  on_init();
}

GraphX::~GraphX() { delete ui; }

void GraphX::on_init() {
  ui->graf->xAxis->setLabel("x");
  ui->graf->yAxis->setLabel("y");

  ui->graf->xAxis->setTickLabels(false);
  ui->graf->yAxis->setTickLabels(false);
}

void GraphX::get_data(QString str) { exp.swap(str); }

void GraphX::new_draw() { on_make_g_clicked(); }

void GraphX::on_make_g_clicked() {
  st = ui->X_neg->value();
  en = ui->X_pos->value();

  ui->graf->xAxis->setRange(st, en);
  ui->graf->yAxis->setRange(ui->Y_neg->value(), ui->Y_pos->value());

  double Y = 0;
  QPen p(Qt::darkRed, 1);
  pr = cn->calc_graph(exp.toStdString(), st, en, s);

  draw_graph(p, QVector<double>(pr.first.begin(), pr.first.end()),
             QVector<double>(pr.second.begin(), pr.second.end()));
}

void GraphX::draw_graph(QPen p, QVector<double> x, QVector<double> y) {
  ui->graf->addGraph();
  ui->graf->graph(0)->setPen(p);
  ui->graf->graph(0)->addData(x, y);
  ui->graf->replot();
  ui->graf->clearGraphs();
}
