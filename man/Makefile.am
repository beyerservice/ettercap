include $(top_srcdir)/Makefile.am.common

man_MANS = ettercap.8 ettercap_curses.8 etterlog.8 etterfilter.8 etter.conf.5

if PLUGINS
   man_MANS += ettercap_plugins.8
endif

EXTRA_DIST = $(man_MANS)

CLEANFILES = *.8 *.5 *.ps *.pdf

MAN2PS = groff -mandoc -Tps

if PS2PDF
pdf: $(addsuffix .pdf, $(basename $(man_MANS)))
	echo $(addsuffix .pdf, $(basename $(man_MANS)))
.PHONY: pdf
%.pdf: %.ps
	$(ps2pdf) $< > $@
endif

%.ps: %.5
	$(MAN2PS) $< > $@

%.ps: %.8
	$(MAN2PS) $< > $@
