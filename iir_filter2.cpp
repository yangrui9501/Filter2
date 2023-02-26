#include "iir_filter2.h"

void IIRFilter2::init_LPF(double _fc1, double _fc2, double _T)
{
    fc1 = _fc1;
    fc2 = _fc2;
    T = _T;

    A0C = 1.0;
    A1C = 2.0 * PI * (fc1 + fc2);
    A2C = 4.0 * PI * PI * fc1 * fc2;

    B0C = 0.0;
    B1C = 0.0;
    B2C = 4.0 * PI * PI * fc1 * fc2;

    coeff_c2d();
}

void IIRFilter2::init_HPF(double _fc1, double _fc2, double _T)
{
    fc1 = _fc1;
    fc2 = _fc2;
    T = _T;

    A0C = 1.0;
    A1C = 2.0 * PI * (fc1 + fc2);
    A2C = 4.0 * PI * PI * fc1 * fc2;

    B0C = 1.0;
    B1C = 0.0;
    B2C = 0.0;

    coeff_c2d();
}

void IIRFilter2::init_BPF(double _wc, double _wb, double _T)
{
    wc = _wc;
    zeta = 0.5 * _wb / _wc;

    A0C = 1.0;
    A1C = 2.0 * zeta * wc;
    A2C = wc * wc;

    B0C = 0.0;
    B1C = 2.0 * zeta * wc;
    B2C = 0.0;

    coeff_c2d_fp();
}

void IIRFilter2::init_NTF(double _wc, double _wb, double _T)
{
    wc = _wc;
    zeta = 0.5 * _wb / _wc;

    A0C = 1.0;
    A1C = 2.0 * zeta * wc;
    A2C = wc * wc;

    B0C = 1.0;
    B1C = 0.0;
    B2C = wc * wc;

    coeff_c2d_fp();
}

const double& IIRFilter2::update(double input_data)
{
    u_in[0] = input_data;

    u_out[0] = 1.0 / A0D * (-A1D * u_out[1] - A2D * u_out[2] + B0D * u_in[0] + B1D * u_in[1] + B2D * u_in[2]);

    u_out[2] = u_out[1];
    u_out[1] = u_out[0];
    u_in[2] = u_in[1];
    u_in[1] = u_in[0];

    return u_out[0];
}

void IIRFilter2::coeff_c2d()
{
    A0D = A0C * 4.0 / (T * T) + A1C * 2.0 / T + A2C;
    A1D = -A0C * 8.0 / (T * T) + 2.0 * A2C;
    A2D = A0C * 4.0 / (T * T) - A1C * 2.0 / T + A2C;

    B0D = B0C * 4.0 / (T * T) + B1C * 2.0 / T + B2C;
    B1D = -8.0 * B0C / (T * T) + 2.0 * B2C;
    B2D = B0C * 4.0 / (T * T) - B1C * 2.0 / T + B2C;
}

void IIRFilter2::coeff_c2d_fp()
{
    kt = wc / (tan(wc * T / 2.0));

    A0D = A0C * kt * kt + A1C * kt + A2C;
    A1D = -2.0 * A0C * kt * kt + 2.0 * A2C;
    A2D = A0C * kt * kt - A1C * kt + A2C;

    B0D = B0C * kt * kt + B1C * kt + B2C;
    B1D = -2.0 * B0C * kt * kt + 2.0 * B2C;
    B2D = B0C * kt * kt - B1C * kt + B2C;
}