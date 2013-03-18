#!/usr/bin/env python
#
# posterior-viterbi decoding 
#

import sys
libPath='/home/piero/hmm/Src/'
sys.path.append(libPath)
import tr_obj
import HMM_IO
import algo_HMM
import string

if len(sys.argv)<3:
   print "usage :",sys.argv[0]," proteinfile modfile"
   sys.exit(-1)


#    print protname.strip()+".io"
prot=open(sys.argv[1]).readlines()
seq=[]
labels=[]
for line in prot:
    v=line.split()
    list=v[0]
#   if integer 0-100 use this lines 
#   list=[string.atof(x)/100.0 for x in v]
    seq.append(list)
obj=tr_obj.TR_OBJ(seq,labels,name=sys.argv[1]) 

trobjlist=[obj]
hmm=HMM_IO.get_hmm(sys.argv[2])
for o in trobjlist:
#    print "NAME ",o.name
    (bestpath,bestval)=algo_HMM.ap_viterbi(hmm,o.seq)
    file=open(o.name+'.apv','w')
    pos=1
    for i in range(o.len): 
#         print hmm.states[bestpath[i]].name
         if bestpath[i] in hmm.emits: 
             file.write(str(pos)+'\t'+str(hmm.states[bestpath[i]].label)+'\n')
             pos+=1
    file.close()

