#!/bin/bash 
#
# Test many many runs of splitting and recombining, each run testing every permutation of when recombining
# Ensure that the recombined result always matches the original seed
# Intermediate data stored under tests folder
#

if [ "$#" -lt 1 ]; then
    echo "Split a test seed into shares, recombine every permutation (order) of those shares. Repeat 'runs' times"
    echo "Usage "$0" runs"
    exit
fi

seed=`echo legal winner thank year wave sausage worth useful legal winner thank yellow` 
threshold=3
outofmshares=3

#
# Make filenames a bit more manageable
#
subdir=testoutput
weakenedweakhash=`echo $seed|sed 's/ //g'|md5|cut -c1-16` 
namestub=`echo $seed|cut -d' ' -f 1-2|sed 's/ /-/g'`-$weakenedweakhash-$threshold"of"$outofmshares
echo $namestub

make
if [ ! -d $subdir ]; then
	mkdir $subdir
fi
	
tmp=$subdir/result.tmp
retvals=$subdir/summary-$namestub

if [ -f $retvals ]; then
	rm $retvals
fi

for ((run = 1; run <= "$1"; run++))
do
	echo "Run $run" 
	echo -n "Run $run: " >> $retvals
	fname=`echo run$run-$namestub|sed 's/ //g'` 
	rm $subdir/shares-$fname* 2> /dev/null
	echo "Splitting into shares the seed " $seed
	echo $seed |  ./shamir39-split -t $threshold -n $outofmshares -d -D > $subdir/shares-$fname; echo -n $? >> $retvals
	echo -n " " >> $retvals  # space separate the split result from the multiple combine results
	python permutations.py  $subdir/shares-$fname $threshold
	date > $tmp
	echo -n "Combining each permutation of shares"
	for i in $subdir/shares-$fname-* 
	do 
		echo -n $i" "  >> $tmp
		echo -e -n "\n"Permutation: $i
		cat $i | ./shamir39-combine -t $threshold -d -D >> $tmp; echo -n $? >> $retvals
	done
	mv $tmp $subdir/combines-$fname
	echo " " >> $retvals
done
errors=`grep -v 0000 $retvals|wc -l` # TODO cludgy holey regex, needs improving
echo -e "\n\n"Run completed `date` with $errors errors.
if [ "$errors" -ne 0 ] 
then
	echo Check \'$retvals\', shown below, and corresponding shares and combines files to see which shares failed.
	cat $retvals
fi 
	
