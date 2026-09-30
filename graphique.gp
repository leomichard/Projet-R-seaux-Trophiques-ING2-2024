file = "data.txt"
stats file using 0:0 nooutput
set title system("grep '^#' ".file." | head -n1 | sed 's/# //g'")
set terminal png size 800,600 enhanced font "Arial,12"
set output "graphique.png"
set xlabel "Temps (tour)"
set ylabel "Nombre (en milliers)"
set grid
plot file using 1:2 with linespoints title "Données"
