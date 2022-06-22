#pragma once
#include <Arduino.h>
// 2021-12-31

// Second-order Filter
class FILTER2
{
public:
    // Initialize type of filter, cut-off frequency, and sample time
    void Init_LPF(double _fc1, double _fc2, double _T); // Low-pass filter (LPF)
    void Init_HPF(double _fc1, double _fc2, double _T); // High-pass filter (HPF)
    void Init_BPF(double _wc, double _wb, double _T); // Band-pass filter (BPF)
    void Init_NTF(double _wc, double _wb, double _T); // Notch-filter (NTF)
    
    // Use this function filtering the 'input_data'
    void Filter2(double *input_data, double *filtered_data);

private:
    double fc1, fc2; // Cutoff frequency (Hz) (for LPF & HPF)
    double wc;       // Center frequency (rad/sec) (for BPF & NTF)
    double zeta;     // Damping ratio
    double T;        // Sample interval
    double u_in[3];  // Input Signal
    double u_out[3]; // Output Signal (Filtered Signal)
    double kt; // Factor for frequency pre-warping

    double A0D, A1D, A2D, B0D, B1D, B2D; // Coefficients of discrete-time transfer function
    double A0C, A1C, A2C, B0C, B1C, B2C; // Coefficients of continuous-time transfer function

    void coeff_c2d(); // Convert continuous-time coefficients to discrete-time one
    void coeff_c2d_fp(); // Similar to coeff_c2d() but with frequency pre-warping (FP)
    void Init_Para(); // Function for Paramter Setting
};
