
outfile=outfile.dat

file=test.set

echo  "#Viterbi     Posterior-Viterbi    1-best      maxAccuracy       Observed" > $outfile 
for f in `cat $file `
do
   ./die_pred1best.py  $f finaldie_labelled.mod 
   ./die_predapvit.py  $f finaldie_labelled.mod  
   ./die_predvit.py    $f finaldie_labelled.mod
   ./die_predma.py     $f finaldie_labelled.mod
   paste $f.vit $f.apv $f.1b  $f.ma $f >> $outfile
done

