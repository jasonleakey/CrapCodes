# alphabets
TRANSITION_ALPHABET begin L1 L2 L3 F1 F2 F3 
EMISSION_ALPHABET 1 2 3 4 5 6
#############################
NAME begin
LINK L1 F1 
TRANS uniform
ENDSTATE 0
EM_LIST None
EMISSION  None
LABEL None
#############################
NAME L1
LINK L2 
TRANS 1.0
ENDSTATE 1
EM_LIST 1 2 3 4 5 6
EMISSION uniform
LABEL L
#############################
NAME L2
LINK L3 
TRANS 1.0
ENDSTATE 1
EM_LIST 1 2 3 4 5 6
EMISSION uniform
LABEL L
#############################
NAME L3
LINK L1 F1 
TRANS uniform
ENDSTATE 1
EM_LIST 1 2 3 4 5 6
EMISSION uniform
LABEL L
#############################
NAME F1
LINK F2 
TRANS 1.0 
ENDSTATE 1
EM_LIST 1 2 3 4 5 6
EMISSION uniform
LABEL F
#############################
NAME F2
LINK F2 F3
TRANS uniform
ENDSTATE 1
EM_LIST 1 2 3 4 5 6
EMISSION uniform
LABEL F
#############################
NAME F3
LINK L1 F1 
TRANS uniform
ENDSTATE 1
EM_LIST 1 2 3 4 5 6
EMISSION uniform
LABEL F
#############################
