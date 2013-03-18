#!/usr/bin/env python
# 
# 1-best decoding
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
#   if integer 0-100 use this lines 
#   list=[string.atof(x)/100.0 for x in v]
    seq.append(list)
obj=tr_obj.TR_OBJ(seq,labels,name=sys.argv[1]) 

trobjlist=[obj]
#hmm=HMM_IO.Build_HMM('msgigipor.mod').get_HMM()
hmm=HMM_IO.get_hmm(sys.argv[2])
for o in trobjlist:
#    print "NAME ",o.name
    (bestpath,val)=algo_HMM.one_best_AK(hmm,o.seq,Scale='yes')
    file=open(o.name+'.1b','w')
    for i in range(o.len): 
         file.write(str(i+1)+'\t'+str(bestpath[i])+'\n')
    file.close()

