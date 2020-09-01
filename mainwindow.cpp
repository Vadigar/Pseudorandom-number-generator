#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <cmath>
#define check(x) if(!(x)) throw #x
#define int long long

int m, a, c, X0, p, q, s, n;
QVector<int> seq;
QString res = "", flag = "lehmer";

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {ui->setupUi(this);}
MainWindow::~MainWindow(){delete ui;}

int get_T(){
    int T = 1, X = ((X0 * a + c) * a + c) % m, first = (X0 * a + c) % m;
    if(first == X0) return T;

    while (X != first){
        if(X == (X * a + c) % m) return 1;
        X = (X * a + c) % m;
        T++;
    }
    return T;
}

bool test1(){
    int count = std::count(res.begin(), res.end(), '1');
    return (count > 9654) && (count < 10346);
}

bool test2(){
    int count[16];
    auto bits = res.toStdString();
    for(int i = 0; i < 16; i++)
        count[i] = 0;
    for(int i = 0; i < 20000; i += 4)
        count[((bits[i] - '0') << 3) + ((bits[i + 1] - '0') << 2) + ((bits[i + 2] - '0') << 1) + (bits[i + 3] - '0')]++;

    double X = 0;
    for(int i = 0; i < 16; i++)
        X += count[i] * count[i];
    X *= 16.  ;
    X /= 5000.;
    X -= 5000.;
    return (X > 1.03) && (X < 157.4);
}

bool tests(){return  test1() && test2();}

bool is_prime(int n){
    if(n == 2) return true;
    if(n == 0 || n == 1 || !(n % 2))return false;
    for(int i = 3;i < std::sqrt(n); ++++i) if(!(n % i))return false;
    return true;
}

void lehmer_check(){
    check(a < m);
    check(c < m);
    check(X0 < m);
}

void bbs_check(){
    check(is_prime(p));
    check(is_prime(q));
    check(p % 4 == 3);
    check(q % 4 == 3);
    check(s % p != 0);
    check(s % q != 0);
}

void MainWindow::on_Generate_1_clicked(){
    if(flag == "lehmer"){
        if(seq.empty()){
            m = ui->value_m_or_p->value();
            a = ui->value_a_or_q->value();
            c = ui->value_c_or_s->value();
            X0 = ui->value_X0_or_n->value();

            try {
                lehmer_check();
            } catch (char const* err) {
                res = err;
                res += " is not true!";
                ui->textBrowser->setText(res);
                res.clear();
                return;
            }

            seq.push_back(X0);
        }
        else
            seq.push_back((seq.last() * a + c) % m);

        res += QString::number(seq.last()) + " ";
        ui->textBrowser->setText(res);
        ui->statusbar->clearMessage();
        ui->statusbar->showMessage("T = " + QString::number(get_T()));
    }
    else {
        p = ui->value_m_or_p->value();
        q = ui->value_a_or_q->value();
        s = ui->value_c_or_s->value();
        res.clear();

        try {
            bbs_check();
        } catch (char const* err) {
            res = err;
            res += " is not true!";
            ui->textBrowser->setText(res);
            res.clear();
            return;
        }

        for (int i = 0;i < 20000;i++) {
            s *= s;
            s %= n;
            res.push_back(((s & 1) ? '1' : '0'));
        }
        ui->textBrowser->setText(res);
        ui->statusbar->clearMessage();
        ui->statusbar->showMessage(tests() ? "Tests passed" : "Tests failed");
    }
}
#undef int

void MainWindow::on_value_m_or_p_valueChanged(int arg1){
    p = m = arg1;
    res.clear();
    seq.clear();
    ui->textBrowser->setText("");
    if(flag == "BBS")ui->value_X0_or_n->setValue(p * q);
}

void MainWindow::on_value_a_or_q_valueChanged(int arg1){
    q = a = arg1;
    res.clear();
    seq.clear();
    ui->textBrowser->setText("");
    if(flag == "BBS")ui->value_X0_or_n->setValue(p * q);
}

void MainWindow::on_value_c_or_s_valueChanged(int arg1){
    s = c = arg1;
    res.clear();
    seq.clear();
    ui->textBrowser->setText("");
}

void MainWindow::on_value_X0_or_n_valueChanged(int arg1){
    n = X0 = arg1;
    res.clear();
    seq.clear();
    ui->textBrowser->setText("");
}

void MainWindow::on_actionLehmer_triggered(){
    ui->m_or_p->setText("m");
    ui->a_or_q->setText("a");
    ui->c_or_s->setText("c");
    ui->X0_or_n->setText("X0");
    ui->Generate_1->setText("Generate_1");
    ui->value_X0_or_n->setReadOnly(0);
    res.clear();
    flag = "lehmer";
}

void MainWindow::on_actionBBS_triggered(){
    ui->m_or_p->setText("p");
    ui->a_or_q->setText("q");
    ui->c_or_s->setText("s");
    ui->X0_or_n->setText("n");
    ui->Generate_1->setText("Generate");
    p = ui->value_m_or_p->value();
    q = ui->value_a_or_q->value();
    s = ui->value_c_or_s->value();
    ui->value_X0_or_n->setValue(p * q);
    ui->value_X0_or_n->setReadOnly(1);
    seq.clear();
    res.clear();
    flag = "BBS";
}
