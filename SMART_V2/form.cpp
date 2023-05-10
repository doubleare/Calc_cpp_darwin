#include "form.h"

#include <QCloseEvent>
#include <QIntValidator>
#include <QMessageBox>

#include "ui_form.h"

Form::Form(s21::Controller *control, QWidget *parent)
    : QWidget(parent), ui(new Ui::Form), cont(control) {
  ui->setupUi(this);

  this->setWindowTitle("CreditCalc");

  ui->summa->setValidator(new QIntValidator(this));
  connect(ui->count, SIGNAL(clicked()), this, SLOT(count_clicked()));
}

Form::~Form() { delete ui; }

void Form::closeEvent(QCloseEvent *event) {
  if (event->spontaneous()) {
    clear_ui();
    ui->summa->setFocus();
  } else {
    QWidget::closeEvent(event);
  }
}

void Form::count_clicked() {
  int type = ui->ck_ann->checkState();
  QString str;
  try {
    str = QString::fromStdString(cont->cred_params(ui->summa->text().toDouble(),
                                                   ui->srok->value(),
                                                   ui->proce->value(), type));
  } catch (const std::invalid_argument &ex) {
    err_msg(ex);
  }
  QStringList strList = str.split(' ');
  if (str.length()) {
    set_text_to_ui(strList);
  }
}

void Form::err_msg(const std::invalid_argument &ex) {
  QMessageBox er_msg;
  er_msg.setText(ex.what());
  er_msg.exec();
  clear_ui();
}

void Form::set_text_to_ui(QStringList strl) {
  ui->m_plat->setText(strl.at(0));
  ui->pere_plat->setText(strl.at(1));
  ui->ob_plat->setText(strl.at(2));
}

void Form::clear_ui() {
  ui->summa->clear();
  ui->m_plat->clear();
  ui->pere_plat->clear();
  ui->ob_plat->clear();
}
