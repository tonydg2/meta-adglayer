all: test-app2

test-app2: test-app2.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

install:
	install -d ${DESTDIR}${BINDIR}
	install -m 0755 test-app2 ${DESTDIR}${BINDIR}

uninstall:
	${RM} ${DESTDIR}/test-app2

clean:
	${RM} test-app2
