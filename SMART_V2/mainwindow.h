#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <form.h>
#include <graphx.h>

#include <QDoubleValidator>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Form form;
  GraphX graphx;

  s21::Model md;
  s21::Controller main_cn;

  int bre = 0, n_ex = 0;
  int last_o = -1, is_x = 0, is_d = 0;

 private slots:
  void x_disable(bool tf);
  void print_num();
  void print_x();
  void print_opers();
  void print_dot();
  void del();
  void clear();
  void open_bre();
  void close_bre();
  void print_func();
  void on_credit();
  void on_res();
  void on_graph();
  void placeHold(QString r);
  void textToL(QString txt);
  void reset(int x, int d, int l, int n, int b);
  void connects();
};
#endif  // MAINWINDOW_H
