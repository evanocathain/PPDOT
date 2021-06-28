
set title "P-Pdot Diagram"
set ylabel "log(Pdot)"
set xlabel "log(P/second)"

#set term postscript enhanced color solid
#set output "ppdot.ps"

set key top left
set key spacing 1.3
set key box

set logscale xy
#plot 'all_psrcat','intermittent_psrs' pt 5 ps 2,'rrats' pt 5 ps 2

plot 'all_psrcat' title "PSRCAT", 'rrats' pt 5 ps 1 title "Original RRATs", 'my_rrats' pt 5 ps 1 title "PMSingle Sources", 'magnetars_confirmed' using 3:4 title "Magnetars"
