all: testapp1

testapp1: testapp1.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

install:
	install -d ${DESTDIR}${BINDIR}
	install -m 0755 testapp1 ${DESTDIR}${BINDIR}

uninstall:
	${RM} ${DESTDIR}/testapp1

clean:
	${RM} testapp1
