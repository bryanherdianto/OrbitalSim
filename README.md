# Orbital Simulation with Runge-Kutta Method

> Bryan Herdianto 2306210885

Program ini mensimulasikan gerakan orbit benda langit menggunakan metode numerik Runge-Kutta orde 4 (RK4). Program ini akan menghitung posisi dan kecepatan benda langit dari waktu ke waktu berdasarkan hukum gravitasi Newton.

## Komponen Proyek

Proyek ini terdiri dari dua program C utama:

1. **orbital_sim.c** - Melakukan simulasi numerik
2. **orbital_plot.c** - Memvisualisasikan lintasan orbit menggunakan GNUPlot

## Cara Kerja

### Simulasi Orbit (orbital_sim.c)

Program ini mengimplementasikan Runge-Kutta orde 4 secara numerik untuk menghitung lintasan orbit:

- Menggunakan hukum gravitasi universal Newton
- Melacak posisi (x,y) dan kecepatan (vx,vy) dari waktu ke waktu
- Menghasilkan data ke file CSV untuk analisis dan visualisasi lebih lanjut

Komponen utama:
- Struct `State`: Menyimpan posisi dan kecepatan dalam arah x dan y
- Fungsi `get_derivatives()`: Menghitung turunan berdasarkan gaya gravitasi
- Fungsi `integrate_rk4()`: Mengimplementasikan metode integrasi Runge-Kutta orde 4

### Visualisasi (orbital_plot.c)

Program ini membuat visualisasi lintasan orbit:

- Menggunakan GNUPlot melalui pipe
- Membaca data dari file CSV yang dihasilkan oleh orbital_sim.c
- Membuat plot 2D dari lintasan orbit

## Cara Penggunaan

1. **Compile kedua program**:
   ```bash
   gcc orbital_sim.c -o orbital_sim -lm
   gcc orbital_plot.c -o orbital_plot
   ```

2. **Jalankan simulasi**:
   ```bash
   ./orbital_sim
   ```
   Lalu, kita harus memasukkan:
   - Posisi awal (x, y) dalam meter
   - Kecepatan awal (vx, vy) dalam meter per detik
   - Ukuran step size waktu dan total waktu simulasi dalam detik

3. **Hasilkan plot**:
   ```bash
   ./orbital_plot
   ```
   Ini akan menampilkan grafik yang menunjukkan lintasan orbit dari benda yang disimulasikan.

## Contoh Input

Untuk membuat simulasi orbit mirip Bumi, gunakan input berikut:
- Posisi: (1.5e11, 0)
- Kecepatan: (0, 3e4)
- Step size waktu: 86400 (1 hari)
- Total waktu: 31536000 (1 tahun)