reset

set grid
set xtics 0.2
set ytics 100

set xlabel "Methane concentration (c1)" font "Calibri, 12, thick"
set ylabel "Pressure [Bar]" font "Calibri, 12"

set key left top
set key box linestyle 1 lc rgb 'black' lw 1 opaque

plot [-0.01:1.01][-10:510] \
\
'output.txt' index 0 using  9:1 title '' w l lw 2 lc 'black', \
''           index 0 using 10:1 title '' w l lw 2 lc 'black', \
\