#include "calculator.h"
#include "ui_calculator.h"
#include <iostream>
using namespace std;

const double PI =   3.141592653589793238462643383279;
const double e =    2.718281828459045235360287471352;
const double ln_2 = 0.693147180559945309417232121458;
bool rad = 1;
bool ok = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::on_btnHello_clicked()
{
    static int count = 0;
    QString strCount;

    // display text message in first label
//    ui->lblHello->setText(ui->Input->displayText());
}



/**
 * General functions
 */

/* returns n! */
double factorial(int n) { // n must be less than or equal to 20 to fit within the 64 bit signed integer limit
    if (n==0) return 1;
    return n*factorial(n-1);
}

/* returns b^x */
double iterativePow(double b, int x) { // not to be used with large values of x
    double ans = 1;
    if (x>0) for (int i = 0; i<x; ++i)
        ans*=b;
    else for (int i = 0; i>x; --i)
        ans/=b;
    return ans;
}



/**
 * Trigonometric functions
 */

/* Converts to radians, and converts angle to be within [0, 2PI) */
double convert(double x, bool inRad) {
    if (!inRad) x*=0.0174533;
    int divRes = (int)(x/(2*PI));
    return x - divRes*2*PI;
}

/* returns sin(x) */
double SIN(double x) {
    x = convert(x, rad);
    double T = 0;
    for (int n = 0; n<100; ++n) {
        double an = ((int)iterativePow(-1, n%2) * iterativePow(x, 2*n+1)) / (factorial(2*n+1)); // general term of Maclaurin Series for sin(x)
        if (abs(an) < 0.000000000001) // alternating series error bound, omits "an" if less than 10^-12
            return T;
        T += an;
    }
}

/* returns cos(x) */
double COS(double x) {
    x = convert(x, rad);
    double T = 0;
    for (int n = 0; n<100; ++n) {
        double an = ((int)iterativePow(-1, n%2) * iterativePow(x, 2*n)) / (factorial(2*n)); // general term of Maclaurin Series for cos(x)
        if (abs(an) < 0.000000000001) // alternating series error bound, omits "an" if less than 10^-12
            return T;
        T += an;
    }
}

/* returns tan(x) */
double TAN(double x) {
    return SIN(x)/COS(x);
}

/* returns csc(x) */
double CSC(double x) {
    return 1/SIN(x);
}

/* returns sec(x) */
double SEC(double x) {
    return 1/COS(x);
}

/* returns cot(x) */
double COT(double x) {
    return COS(x)/SIN(x);
}



/**
 * Exponential and logarithmic functions
 */

/* returns e^x */
double ePow(double x) {
    double T = 0;
    int a = (int)x;
    for (int n = 0; n<200; ++n) {
        T += ((iterativePow(e, a)*iterativePow(x-a, n)) / factorial(n)); // genereal term of Taylor series for e^x centered about x=a
        double M = iterativePow(e, x+1);
        if (abs((M*iterativePow(x-a, n+1)/factorial(n+1))) < 0.000000000001) // Lagrange error bound to guarantee error less than 10^-12
            return T;
    }
}

/* returns ln(x) when 0.5<x<3.5 */ // although the radius of convergence is 2, near the bounds it converges too slowly
double naturalLog(double x) {
    double T = ln_2;
    for (int n = 1; n<200; ++n) {
        double an = (((int)iterativePow(-1, n%2+1))*iterativePow(x-2, n)) / (iterativePow(2, n)*n); // general term of Taylor series for ln(x) centered about x=2
        if (abs(an) < 0.000000000001) // alternating series error bound, omits "an" if less than 10^-12
            return T;
        T += an;
    }
}

/* returns ln(x) */
double LN(double x) {
    int n1 = 0, n2 = 0;
    while (x>3.5) {
        x/=2;
        ++n1;
    }
    while (x<0.5) {
        x*=2;
        ++n2;
    }
    return naturalLog(x) + n1*ln_2 - n2*ln_2;
}

/* returns b^x */
double POW(double b, double x) {
    double T = 0;
    int a = (int)x;
    for (int n = 0; n<200; ++n) {
        T += ((iterativePow(b, a)*iterativePow(LN(b), n)*iterativePow(x-a, n)))/factorial(n);
        // cout << ((iterativePow(b, a)*iterativePow(ln(b), n)*iterativePow(x-a, n)))/factorial(n) << endl;
        double M = iterativePow(b, x+1)*iterativePow(LN(b), n+1);
        if (abs((M*iterativePow(x-a, n+1)/factorial(n+1))) < 0.000000000001) // Lagrange error bound to guarantee error less than 10^-12
            return T;
    }
}



/**
 * Display functions
 */

void Calculator::on_PI_clicked()
{
    ui->Input->setText(QString::number(PI, 'g', 30));
}

void Calculator::on_e_clicked()
{
    ui->Input->setText(QString::number(e, 'g', 30));
}

void Calculator::on_sin_clicked()
{
    double res = SIN(ui->Input->displayText().toDouble(&ok));
    if (abs(res) < 0.000000000001) res = 0;
    ui->Output->setText(QString::number(res, 'g', 9));
}

void Calculator::on_cos_clicked()
{
    double res = COS(ui->Input->displayText().toDouble(&ok));
    if (abs(res) < 0.000000000001) res = 0;
    ui->Output->setText(QString::number(res, 'g', 9));
}

void Calculator::on_tan_clicked()
{
    double res = TAN(ui->Input->displayText().toDouble(&ok));
    if (abs(res) < 0.000000000001) res = 0;
    ui->Output->setText(QString::number(res, 'g', 9));
}

void Calculator::on_csc_clicked()
{
    double res = CSC(ui->Input->displayText().toDouble(&ok));
    if (abs(res) < 0.000000000001) res = 0;
    ui->Output->setText(QString::number(res, 'g', 9));
}

void Calculator::on_sec_clicked()
{
    double res = SEC(ui->Input->displayText().toDouble(&ok));
    if (abs(res) < 0.000000000001) res = 0;
    ui->Output->setText(QString::number(res, 'g', 9));
}

void Calculator::on_cot_clicked()
{
    double res = COT(ui->Input->displayText().toDouble(&ok));
    if (abs(res) < 0.000000000001) res = 0;
    ui->Output->setText(QString::number(res, 'g', 9));
}

void Calculator::on_epow_clicked()
{
    double res = ePow(ui->Input->displayText().toDouble(&ok));
    ui->Output->setText(QString::number(res, 'g', 9));
}

void Calculator::on_ln_clicked()
{
    double res = LN(ui->Input->displayText().toDouble(&ok));
    ui->Output->setText(QString::number(res, 'g', 9));
}

void Calculator::on_xpow2_clicked()
{
    double res = POW(ui->Input->displayText().toDouble(&ok), 2);
    ui->Output->setText(QString::number(res, 'g', 9));
}

void Calculator::on_sqrt_clicked()
{
    double res = POW(ui->Input->displayText().toDouble(&ok), 0.5);
    ui->Output->setText(QString::number(res, 'g', 9));
}

void Calculator::on_clear_clicked()
{
    ui->Input->setText("");
    ui->Output->setText("");
}
