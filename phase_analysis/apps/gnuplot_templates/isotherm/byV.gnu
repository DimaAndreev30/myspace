reset

set grid
set xtics 2
set ytics 20

set xlabel "Volume [m3/Kmol]" font "Calibri, 12, thick"
set ylabel "Pressure [bar]" font "Calibri, 12"

plot [0:10][0.0:100.0] \
'data.txt' index 0 using 1:2 title 'isotherm' w l lt 1