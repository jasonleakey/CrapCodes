#!/usr/bin/env python
#
# test baum-wlech learning
#

import sys
sys.path.append('../hmm/')

import tr_obj
import HMM_IO
import algo_HMM
import string

if len(sys.argv) < 2:
   print "usage :", sys.argv[0], " proteinset"
   sys.exit(-1)

pset = open(sys.argv[1]).readlines()

# read all proteins
trobjlist = []
for protname in pset:
#    print protname.strip()+".io"
    prot = open(protname.strip()).readlines()
    seq = []
    labels = []
    for line in prot:
        v = line.split()
        seq.append(v[0])
        labels.append(v[-1])
    trobjlist.append(tr_obj.TR_OBJ(seq, labels, name=protname.strip()))

#for o in trobjlist:
#    print o.name
#    print len(o.seq[0]),o.seq
hmm = HMM_IO.get_hmm('initdie.mod')
algo_HMM.Baum_Welch(hmm, trobjlist, Scale='Yes', labels='Yes', maxcycles=100, tolerance=1e-4, verbose='y')
hmm.write_for_humans('finaldie_labelled.mod')
