## 
## Makefile.am 
##

AM_CFLAGS=-I$(top_srcdir)/include -I$(top_srcdir)/include/dicom
AM_LDFLAGS=

bin_PROGRAMS = mri_label2vol
mri_label2vol_SOURCES=mri_label2vol.c
mri_label2vol_LDADD= $(addprefix $(top_builddir)/, $(LIBS_MGH))
mri_label2vol_LDFLAGS=$(OS_LDFLAGS)

# TESTS=test.py

# EXTRA_DIST= test.py

# Our release target. Include files to be excluded here. They will be
# found and removed after 'make install' is run during the 'make
# release' target.
EXCLUDE_FILES=""
include $(top_srcdir)/Makefile.extra
