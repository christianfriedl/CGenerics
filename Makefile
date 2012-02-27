install:
	cp makeman.pl ~/bin
	(cd src; make install)
%:
	(cd src; make $<)
