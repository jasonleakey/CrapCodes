
echo "This test the learning program" > Results.txt
echo "for the case of single sequence" >> Results.txt
echo "The model which produced die*" >> Results.txt
echo "is theoreticalModel.mod" >> Results.txt
echo "the final and intial models are: finaldie_labelled.mod and initdie.mod " >> Results.txt
echo "Running please wait!"
./test_die.py learn.set >>Results.txt
echo "Finished! look at Results.txt"
