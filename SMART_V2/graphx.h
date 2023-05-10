#ifndef GRAPHX_H
#define GRAPHX_H

#include <../controller.h>

#include <QMainWindow>
#include <QPen>
#include <QVector>

namespace Ui {
class GraphX;
}

class GraphX : public QMainWindow {
  Q_OBJECT

 public:
  explicit GraphX(s21::Controller *control, QWidget *parent = nullptr);
  ~GraphX();

 public slots:
  void get_data(QString str);
  void new_draw();

 private slots:
  void on_make_g_clicked();
  void draw_graph(QPen p, QVector<double> x, QVector<double> y);
  void on_init();

 private:
  Ui::GraphX *ui;
  s21::Controller *cn;

  QString exp = "";
  std::pair<std::vector<double>, std::vector<double>> pr;

  double s = 0.1, st = 0, en = 0;
};

#endif  // GRAPHX_H
