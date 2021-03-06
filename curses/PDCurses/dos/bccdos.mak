# Borland MAKE Makefile for PDCurses library - DOS BC++ 3.0+
#
# Usage: make -f [path\]bccdos.mak [DEBUG=] [target]
#
# where target can be any of:
# [all|demos|pdcurses.lib|testcurs.exe...]

# Change the memory MODEL here, if desired
MODEL = l

O = obj

!ifndef PDCURSES_SRCDIR
PDCURSES_SRCDIR = ..
!endif

!include $(PDCURSES_SRCDIR)\version.mif
!include $(PDCURSES_SRCDIR)\libobjs.mif

osdir      = $(PDCURSES_SRCDIR)\dos

!ifdef DEBUG
CFLAGS      = -N -v -y -DPDCDEBUG
!else
CFLAGS      = -O -md
!endif

CPPFLAGS   = -I$(PDCURSES_SRCDIR)

BUILD      = $(CC) -1- -K -G -rd -d -w-eff -w-par -c \
-m$(MODEL) $(CFLAGS) $(CPPFLAGS)

LIBEXE      = tlib /C /E

LIBCURSES   = pdcurses.lib

all:   $(LIBCURSES) $(DEMOS)

clean:
   -del *.obj
   -del *.lib
   -del *.map
   -del *.exe

demos:   $(DEMOS)

$(LIBCURSES) : $(LIBOBJS) $(PDCOBJS)
   -del $@
   $(LIBEXE) $@ @$(osdir)\bccdos.lrf
   -copy $(LIBCURSES) panel.lib

.autodepend

{$(srcdir)\}.c.obj:
   $(BUILD) $<

{$(osdir)\}.c.obj:
   $(BUILD) $<

{$(demodir)\}.c.obj:
   $(BUILD) $<

.c.obj:
   $(BUILD) $<

.obj.exe:
   $(CC) -m$(MODEL) -e$@ $** $(LIBCURSES)

tuidemo.exe:   tuidemo.obj tui.obj $(LIBCURSES)
   $(CC) -m$(MODEL) -e$@ $**

tui.obj: $(demodir)\tui.c $(demodir)\tui.h $(PDCURSES_CURSES_H)
   $(BUILD) -I$(demodir) $(demodir)\tui.c

tuidemo.obj: $(demodir)\tuidemo.c $(PDCURSES_CURSES_H)
   $(BUILD) -I$(demodir) $(demodir)\tuidemo.c

PLATFORM1 = Borland C++ 3.1
PLATFORM2 = Borland C/C++ 3.1 for DOS
ARCNAME = pdc$(VER)bcc

!include $(PDCURSES_SRCDIR)\makedist.mif
