set terminal png size 1024,768 font "Times-New-Roman,16"
set output "MCManySamples.png"

set xlabel "Ilosc losowan"
set ylabel "wartosc całki"
Shadecolor = "#80E0A080"
plot "data.dat" using 1:4:5 with filledcurve fc rgb Shadecolor title "Zakres niepewności" ,"data.dat" using 1:2 w l lw 2 lt rgb "#312512" notitle, "" using 1:3 w l title "wynik dokładny"

set output "MCOneSample.png"

plot "data2.dat" using 1:2 w l lw 2 lt rgb "#312512" notitle, "" using 1:3 w l title "wynik dokładny"
