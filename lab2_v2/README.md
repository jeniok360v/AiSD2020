gcc zad1.c -o zad1
./zad1 --type insert --comp inc

gcc zad2.c -o zad2
./zad2 --type merge --comp inc --stat plotNAME.txt 1 2>stderr.txt

1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100



1. Size
2. Amount of compares
3. Amount of array assigments
4. Compares/size
5. Assignments/size
6. Time

plot "plot.txt" using 1:6 title 'merge' with lines, \
"plot2.txt" using 1:6 title 'quick' with lines

plot "quickplot.txt" using 1:6 title 'quick' with lines, \
"dpqsplot.txt" using 1:6 title 'dual-pivot' with lines, \
"mergeplot.txt" using 1:6 title 'merge' with lines

plot "quickplot.txt" using 1:6 title 'quick' with lines, \
"mergeplot.txt" using 1:6 title 'merge' with lines, \
"dpqsplot.txt" using 1:6 title 'dual-pivot' with lines

plot "quickplot.txt" using 1:2 title 'quick' with lines, \
"dpqsplot.txt" using 1:2 title 'dual-pivot' with lines, \
x*log(x)*1.49, \
x*log(x)*0.86

plot "quickplot.txt" using 1:3 title 'quick' with lines, \
"dpqsplot.txt" using 1:3 title 'dual-pivot' with lines

plot "Sinsertplot.txt" using 1:6 title 'insert' with lines, \
"Smergeplot.txt" using 1:6 title 'merge' with lines, \
"Squickplot.txt" using 1:6 title 'quick' with lines, \
"Sdpqsplot.txt" using 1:6 title 'dual-pivot' with lines

plot "insertplot1000.txt" using 1:6 title 'insert' with lines, \
"mergeplot1000.txt" using 1:6 title 'merge' with lines, \
"quickplot1000.txt" using 1:6 title 'quick' with lines, \
"dpqsplot1000.txt" using 1:6 title 'dual-pivot' with lines, \
"hybridplot1000.txt" using 1:6 title 'hybrid' with lines

plot "quickplot100000.txt" using 1:6 title 'quick' with lines, \
"15hybridplot100000.txt" using 1:6 title 'hybrid15' with lines, \
"5hybridplot100000.txt" using 1:6 title 'hybrid5' with lines, \
"9hybridplot100000.txt" using 1:6 title 'hybrid9' with lines, \
"50insertplot100000.txt" using 1:6 title 'insert' with lines