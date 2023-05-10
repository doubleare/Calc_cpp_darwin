#ifndef FORM_H
#define FORM_H

#include <../controller.h>

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget {
  Q_OBJECT

 public:
  explicit Form(s21::Controller *control, QWidget *parent = nullptr);
  ~Form();

 private slots:
  void closeEvent(QCloseEvent *event) override;
  void count_clicked();
  void set_text_to_ui(QStringList strl);
  void err_msg(const std::invalid_argument &ex);
  void clear_ui();

 private:
  Ui::Form *ui;
  s21::Controller *cont;
};

#endif  // FORM_H
