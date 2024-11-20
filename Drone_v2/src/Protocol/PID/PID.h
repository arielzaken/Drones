#include <stdint.h>
#include <bits/stdc++.h> 
int32_t clamp(int32_t value, int32_t min, int32_t max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
class PID {
    private:
    int32_t kp, ki, kd;
    int32_t error, prev_error, integral;
    int32_t output;
    int32_t max_value;
    
    public:
    PID(int32_t p, int32_t i, int32_t d,int32_t max_value) : kp(p), ki(i), kd(d),max_value(max_value), error(0), prev_error(0), integral(0), output(0) {}
    
    int32_t update(int32_t setpoint, int32_t measured_value) {
        error = setpoint - measured_value;
        integral += error;
        int32_t derivative = error - prev_error;
        output = kp * error + ki * integral + kd * derivative;
        prev_error = error;
        output = clamp(output, max_value, -max_value); // Limit the output to -200 to 200
        return output;
    }
};