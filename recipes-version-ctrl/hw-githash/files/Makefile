all: hw-githash

hw-githash: hw-githash.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

install:
	install -d ${DESTDIR}${BINDIR}
	install -m 0755 hw-githash ${DESTDIR}${BINDIR}
	install -d ${DESTDIR}${SYSDIR}/system/
	install -m 0644 ${WRKDIR}/hw-githash.service ${DESTDIR}${SYSDIR}/system/

uninstall:
	${RM} ${DESTDIR}/hw-githash

clean:
	${RM} hw-githash
