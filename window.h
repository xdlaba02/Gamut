#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

namespace Ui {
  class Window;
}

class Window : public QWidget {
  Q_OBJECT

public:
  explicit Window(QWidget *parent = nullptr);
  ~Window();

  void setName(const QString &name);
  QString name() const;

protected:
  void keyPressEvent(QKeyEvent *event) override;

private slots:

  void on_cie2deg_clicked();
  void on_cie10deg_clicked();
  void on_comboBox_activated(int index);
  void on_horizontalSlider_valueChanged(int value);
  void on_front_clicked();
  void on_right_clicked();
  void on_top_clicked();
  void on_persp_clicked();
  void on_gamma_label_valueChanged(double gamma);
  void on_cie_A_clicked();
  void on_cie_D65_clicked();
  void on_cie_C_clicked();
  void on_cie_D50_clicked();
  void on_cie_D55_clicked();
  void on_cie_D75_clicked();
  void on_cie_xyz_clicked();
  void on_cie_xyY_clicked();

  void on_minlambda_spinbox_valueChanged(int lambda);
  void on_minlambda_slider_valueChanged(int lambda);
  void on_maxlambda_spinbox_valueChanged(int lambda);
  void on_maxlambda_slider_valueChanged(int lambda);

private:
  Ui::Window *ui;
};

#endif // WINDOW_H
