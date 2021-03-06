#!/bin/tcsh -ef

echo PWD `pwd`

# CNY-BCH template subjects
set CNYBCH_TEMPLATE_SUBJECTS_DIR = $FREESURFER_HOME/average/CNYBCH

set CNYBCH_SUBJECTS = (Template1 Template2 Template3 Template4 Template5 Template6 Template7 Template8 Template9 Template10 Template11 Template12 Template13 Template14 Template15 Template16 Template17 Template18 Template19 Template20 Template21 Template22 Template23 Template24 Template25 Template26)
set CNYBCH_AGES     = (9 7 6 5 18 12 0 0 3 8 10 10 18 4 2 14 3 16 0 12 0 15 5 17 16 0 ) # age at MRI scan (mo)

set CNYBCH_GMWM_SUBJECTS = (Template5 Template6 Template8 Template10 Template13 Template18 Template20 Template22)
set CNYBCH_GMWM_AGES = (18 12 0 8 18 16 12 15) # (mo)

set CNYBCH_NEONATES      = (Template7 Template8 Template19 Template21 Template26)
set CNYBCH_NEONATEAGES   = (3 4 1 2 4) # days (first two computed from weeks)

set CNYBCH_AROUNDONE     = (Template11 Template12 Template6 Template20 Template16)
set CNYBCH_AROUNDONEAGES = (10    10    12    12    14) #mo
