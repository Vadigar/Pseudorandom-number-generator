#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Generate_1_clicked();

    void on_actionLehmer_triggered();

    void on_value_m_or_p_valueChanged(int arg1);

    void on_value_a_or_q_valueChanged(int arg1);

    void on_value_c_or_s_valueChanged(int arg1);

    void on_value_X0_or_n_valueChanged(int arg1);

    void on_actionBBS_triggered();

private:
    Ui::MainWindow *ui;
};
