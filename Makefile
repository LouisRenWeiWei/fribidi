TARFILE=fribidi-0.10.4.tar.gz
TARDIR=fribidi-0.10.4

CONFIGURE_FLAG= --prefix=/usr --mandir=\$${prefix}/share/man --infodir=\$${prefix}/share/info

all: build

unpack: unpack-stamp
unpack-stamp: $(TARFILE)
	-rm -rf $(TARDIR)
	tar zxf $(TARFILE)
	for P in `ls patches/*.diff 2>/dev/null`; do \
	    (cd $(TARDIR) && patch -p1) < $$P; \
	done
	touch $@

build: build-stamp
build-stamp: unpack-stamp
	install -d build/fribidi
#	cd $(TARDIR) && aclocal
#	cd $(TARDIR) && autoheader
#	cd $(TARDIR) && libtoolize -c --force
#	cd $(TARDIR) && automake -i --foreign
#	cd $(TARDIR) && autoconf

	cd build/fribidi && ../../$(TARDIR)/configure  --prefix=/usr --mandir=\$${prefix}/share/man --infodir=\$${prefix}/share/info
	cd build/fribidi && make $(MAKE_DEFINES)

	touch $@

install: install-stamp
install-stamp: build-stamp
	P=`pwd`/$(INSTALL_PREFIX) && cd build/fribidi && make install prefix=$$P/debian/tmp/usr

	touch $@

clean:
	rm -rf build 
	rm -rf $(TARDIR)
	rm -f build*-stamp install*-stamp unpack-stamp
	rm -f *~ patches/*~
	rm -f fribidi_test

test:	build
	cd build/fribidi && make test check
	gcc -static -o fribidi_test fribidi_test.c -Lbuild/fribidi/.libs -lfribidi -I$(TARDIR)
	./fribidi_test
	@echo "All Debian Package tests passed succesfully."
