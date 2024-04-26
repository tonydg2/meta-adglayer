all: hw-githash-test

hw-githash-test: hw-githash-test.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

install:
	install -d ${DESTDIR}${BINDIR}
	install -m 0755 hw-githash-test ${DESTDIR}${BINDIR}

uninstall:
	${RM} ${DESTDIR}/hw-githash-test

clean:
	${RM} hw-githash-test
