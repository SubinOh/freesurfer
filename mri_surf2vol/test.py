#!/usr/bin/env python
import sys, os, os.path as op
sys.path.append(op.join(op.dirname(sys.argv[0]), '../python'))
import freesurfer.test as fst

rt = fst.RegressionTest()

rt.run('mri_surf2vol --o vol.mgz --subject cvs_avg35 --so lh.white lh.thickness --so rh.white rh.thickness')
rt.mridiff('vol.mgz', 'vol_ref.mgz')

rt.cleanup()
