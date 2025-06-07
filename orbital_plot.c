#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Membuka pipe ke program GNUPlot dengan mode "persistent" agar window plot tetap terbuka
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    // Memeriksa apakah pipe ke GNUPlot gagal diinisialisasi
    if (gnuplotPipe == NULL)
    {
        perror("Error open pipe to GNUPlot\n"); // Menampilkan pesan error jika pipe gagal dibuka
        return 1;
    }

    // Menulis command-command GNUPlot ke pipe
    fprintf(gnuplotPipe, "set title 'Orbital Position Over Time'\n"); // Mengatur judul plot
    fprintf(gnuplotPipe, "set xlabel 'x (m)'\n");                     // Mengatur label sumbu x
    fprintf(gnuplotPipe, "set ylabel 'y (m)'\n");                     // Mengatur label sumbu y
    fprintf(gnuplotPipe, "set grid\n");                               // Mengaktifkan grid pada plot
    fprintf(gnuplotPipe, "set datafile separator ','\n");
    fprintf(gnuplotPipe, "plot 'orbital_data.csv' using 2:3 notitle with linespoints lw 0.5 lt rgb 'red'\n");

    pclose(gnuplotPipe); // Menutup pipe ke GNUPlot
    return 0;
}
