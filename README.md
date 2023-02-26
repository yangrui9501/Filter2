# Second-Order IIR Filters

- Since Jun 23, 2022
- This library implements the second-order infinite impulse response (IIR) filters
- Filter types:
  - Low pass filter
  - High pass filter
  - Notch filter (band-rejection filter)
  - Band-pass filter

## Initialization

For the what filter is used, please call one of the following function to initialize the filter object:

```cpp
// Initialize type of filter, cut-off frequency, and sample time
void init_LPF(double _fc1, double _fc2, double _T); // Low-pass filter (LPF)
void init_HPF(double _fc1, double _fc2, double _T); // High-pass filter (HPF)
void init_BPF(double _wc, double _wb, double _T); // Band-pass filter (BPF)
void init_NTF(double _wc, double _wb, double _T); // Notch-filter (NTF)
```

For instance,

```cpp
IIRFilter2 filter;

filter.init_LPF(1.0, 1.0, 0.001); // Initialize a low-pass filter with double cut-off frequency 1.0 and with the sampling interval of 0.001 seconds.
```

## Filter Update

Call the `update()` function for every timer routine:

```cpp
double filter_out = filter.update(data); // data is the measured signal to be filtered.
```

## Example: LPF

```cpp
#include <Arduino.h>
#include <iir_filter2.h>

double noise, data;
double filter_out;
double Ts = 0.001;
int idx = 0;
double t = 0.0;

IIRFilter2 filter;

void setup()
{
    Serial.begin(115200);
    filter.init_LPF(10.0, 10.0, Ts);
}

void loop()
{
    static unsigned long t_enter;
    
    if (micros() -t_enter >= 1000)
    {
        t_enter = micros();
        
        t = (double)(idx) * Ts;        
        noise = (double)(random(-1000, 1000)) / 1000.0;    
        data = sin(2.0*PI*t) + noise;

        filter_out = filter.update(data);

        idx++;

        Serial.printf("%.3f %.3f\n", data, filter_out);
    }
}
```
![image](https://user-images.githubusercontent.com/91120147/221400779-43297500-d633-4265-bbe1-6b017a49da48.png)
