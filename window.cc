#include "window.h"
#include "ui_window.h"

#include <QKeyEvent>

Window::Window(QWidget *parent): QWidget(parent), ui(new Ui::Window) {
  ui->setupUi(this);
}

Window::~Window() {
  delete ui;
}

void Window::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void Window::on_cie2deg_clicked() {
  ui->CIEViz->setObserver(0);
}

void Window::on_cie10deg_clicked() {
  ui->CIEViz->setObserver(1);
}

void Window::on_comboBox_activated(int index) {
  ui->CIEViz->setWorkingSpace(index);
}

void Window::on_horizontalSlider_valueChanged(int value) {
  float v = static_cast<float>(value) / 10;
  ui->CIEViz->setGamma(v);
  ui->gamma_label->setValue(v);
}

void Window::on_front_clicked() {
  ui->CIEViz->setRotation(0, 0, 0);
}

void Window::on_right_clicked() {
  ui->CIEViz->setRotation(0, -90 * 16, 0);
}

void Window::on_top_clicked() {
  ui->CIEViz->setRotation(90 * 16, 0, 0);
}

void Window::on_persp_clicked() {
  ui->CIEViz->setRotation(45 * 16, -45 * 16, 0);
}

void Window::on_gamma_label_valueChanged(double gamma) {
  ui->CIEViz->setGamma(gamma);
  ui->horizontalSlider->setValue(gamma * 10);
}

void Window::on_cie_A_clicked() {
  ui->CIEViz->setIlluminant(0);
}

void Window::on_cie_D65_clicked() {
  ui->CIEViz->setIlluminant(1);
}

void Window::on_cie_C_clicked() {
  ui->CIEViz->setIlluminant(2);
}

void Window::on_cie_D50_clicked() {
  ui->CIEViz->setIlluminant(3);
}

void Window::on_cie_D55_clicked() {
  ui->CIEViz->setIlluminant(4);
}

void Window::on_cie_D75_clicked() {
  ui->CIEViz->setIlluminant(5);
}

void Window::on_cie_xyz_clicked() {
  ui->CIEViz->setAxes(0);
  ui->cie_A->setEnabled(false);
  ui->cie_D65->setEnabled(false);
  ui->cie_C->setEnabled(false);
  ui->cie_D50->setEnabled(false);
  ui->cie_D55->setEnabled(false);
  ui->cie_D75->setEnabled(false);
}

void Window::on_cie_xyY_clicked() {
  ui->CIEViz->setAxes(1);
  ui->cie_A->setEnabled(true);
  ui->cie_D65->setEnabled(true);
  ui->cie_C->setEnabled(true);
  ui->cie_D50->setEnabled(true);
  ui->cie_D55->setEnabled(true);
  ui->cie_D75->setEnabled(true);
}

void Window::on_minlambda_spinbox_valueChanged(int lambda) {
  ui->minlambda_slider->setValue(lambda);
  if (ui->maxlambda_slider->value() < lambda) {
    ui->maxlambda_slider->setValue(lambda);
    ui->maxlambda_spinbox->setValue(lambda);
  }

  ui->CIEViz->setMinLambda(lambda);
}

void Window::on_minlambda_slider_valueChanged(int lambda) {
  ui->minlambda_spinbox->setValue(lambda);
  if (ui->maxlambda_slider->value() < lambda) {
    ui->maxlambda_slider->setValue(lambda);
    ui->maxlambda_spinbox->setValue(lambda);
  }

  ui->CIEViz->setMinLambda(lambda);
}

void Window::on_maxlambda_spinbox_valueChanged(int lambda) {
  ui->maxlambda_slider->setValue(lambda);
  if (ui->minlambda_spinbox->value() > lambda) {
    ui->minlambda_spinbox->setValue(lambda);
    ui->minlambda_spinbox->setValue(lambda);
  }
  ui->CIEViz->setMaxLambda(lambda);
}

void Window::on_maxlambda_slider_valueChanged(int lambda) {
  ui->maxlambda_spinbox->setValue(lambda);
  if (ui->minlambda_spinbox->value() > lambda) {
    ui->minlambda_spinbox->setValue(lambda);
    ui->minlambda_spinbox->setValue(lambda);
  }
  ui->CIEViz->setMaxLambda(lambda);
}
