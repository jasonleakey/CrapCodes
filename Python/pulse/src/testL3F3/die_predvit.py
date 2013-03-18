#!/usr/bin/env python
#
# 
# viterbi decoding
#

import sys
sys.path.append('../Src')
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
#    list=[string.atof(x)/100.0 for x in v]
    seq.append(list)
    labels.append(v[-1])
obj=tr_obj.TR_OBJ(seq,labels,name=sys.argv[1]) 

trobjlist=[obj]
#hmm=HMM_IO.Build_HMM('msgigipor.mod').get_HMM()
hmm=HMM_IO.get_hmm(sys.argv[2])
for o in trobjlist:
#    print "NAME ",o.name
    (bestpath,bestval)=algo_HMM.viterbi(hmm,o.seq)
    file=open(o.name+'.vit','w')
    pos=1
    for i in range(o.len):
#         print hmm.states[bestpath[i]].name
         if bestpath[i] in hmm.emits:
             lab=str(hmm.states[bestpath[i]].label)
             file.write(str(pos)+'\t'+lab+'\n')
             pos+=1
    file.close()

