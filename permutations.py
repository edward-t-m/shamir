#!/usr/bin/python
import sys
import itertools

fname=str(sys.argv[1])
threshold=int(sys.argv[2])

# get our list of shares
shares = [] 
with open (fname, 'rt') as in_file: 
    for line in in_file:
        shares.append(line)  
    

# generate permutations
permutations=list(itertools.permutations(shares,threshold))


permutation = 1

# write each set into its own file
for index in range(len(permutations)):
    permutationfname=fname+"-perm"+str(permutation)
    with open (permutationfname, 'wt') as permutationfile:
        permutation_subindex = 0
        while permutation_subindex < threshold:
            permutation_line = str(permutations[index][permutation_subindex])
            permutationfile.write(permutation_line)
            permutation_subindex=permutation_subindex+1
    permutation=permutation+1


