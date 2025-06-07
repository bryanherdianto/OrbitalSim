#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Inisialisasi konstanta-konstanta yang diperlukan
double G = 6.67430e-11;  // Konstanta gravitasi
double M_SUN = 1.989e30; // Massa matahari dalam kilogram

// Define struct untuk menyimpan state dari planet, yaitu posisi dan kecepatan dalam arah x dan y
typedef struct
{
    double x, y;
    double vx, vy;
} State;

// Fungsi untuk menghitung turunan (dx/dt, dy/dt, dvx/dt, dvy/dt)
State get_derivatives(State s)
{
    State d_s;

    // Hitung jarak planet dari matahari
    double r = sqrt(s.x * s.x + s.y * s.y);

    // Hitung faktor percepatan gravitasi
    double accel_factor = -G * M_SUN / (r * r * r);

    // Hitung turunan posisi, yaitu kecepatan
    d_s.x = s.vx;
    d_s.y = s.vy;

    // Hitung turunan kecepatan, yaitu percepatan
    d_s.vx = accel_factor * s.x;
    d_s.vy = accel_factor * s.y;

    return d_s;
}

// Fungsi untuk mengaplikasikan metode Runge-Kutta 4th Order (RK4)
State integrate_rk4(State current_s, double h)
{
    State k1 = get_derivatives(current_s);

    State temp_s2;
    temp_s2.x = current_s.x + 0.5 * h * k1.x;
    temp_s2.y = current_s.y + 0.5 * h * k1.y;
    temp_s2.vx = current_s.vx + 0.5 * h * k1.vx;
    temp_s2.vy = current_s.vy + 0.5 * h * k1.vy;
    State k2 = get_derivatives(temp_s2);

    State temp_s3;
    temp_s3.x = current_s.x + 0.5 * h * k2.x;
    temp_s3.y = current_s.y + 0.5 * h * k2.y;
    temp_s3.vx = current_s.vx + 0.5 * h * k2.vx;
    temp_s3.vy = current_s.vy + 0.5 * h * k2.vy;
    State k3 = get_derivatives(temp_s3);

    State temp_s4;
    temp_s4.x = current_s.x + h * k3.x;
    temp_s4.y = current_s.y + h * k3.y;
    temp_s4.vx = current_s.vx + h * k3.vx;
    temp_s4.vy = current_s.vy + h * k3.vy;
    State k4 = get_derivatives(temp_s4);

    State next_s;
    next_s.x = current_s.x + (h / 6.0) * (k1.x + 2.0 * k2.x + 2.0 * k3.x + k4.x);
    next_s.y = current_s.y + (h / 6.0) * (k1.y + 2.0 * k2.y + 2.0 * k3.y + k4.y);
    next_s.vx = current_s.vx + (h / 6.0) * (k1.vx + 2.0 * k2.vx + 2.0 * k3.vx + k4.vx);
    next_s.vy = current_s.vy + (h / 6.0) * (k1.vy + 2.0 * k2.vy + 2.0 * k3.vy + k4.vy);

    return next_s;
}

int main()
{
    // Posisi dan kecepatan awal suatu objek
    State obj_state;
    printf("Masukkan posisi (x, y) dan kecepatan (vx, vy) dalam m/s:\n");
    scanf("%lf %lf %lf %lf", &obj_state.x, &obj_state.y, &obj_state.vx, &obj_state.vy);

    // Step size dan total waktu simulasi (dalam detik)
    double time_step, total_time;
    printf("Masukkan step size dan total waktu simulasi dalam detik:\n");
    scanf("%lf %lf", &time_step, &total_time);

    // Jumlah step yang akan dilakukan
    int num_steps = (int)(total_time / time_step);

    // Buka file CSV untuk output
    FILE *file = fopen("orbital_data.csv", "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Tulis header CSV
    fprintf(file, "time_s,x_m,y_m\n");

    // Tulis posisi awal
    double current_time = 0.0;
    fprintf(file, "%.6f,%.6e,%.6e\n", current_time, obj_state.x, obj_state.y);

    // Loop simulasi
    for (int i = 0; i < num_steps; ++i)
    {
        obj_state = integrate_rk4(obj_state, time_step);
        current_time += time_step;
        fprintf(file, "%.6f,%.6e,%.6e\n", current_time, obj_state.x, obj_state.y);
    }

    // Tutup file
    fclose(file);

    return 0;
}