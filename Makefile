# Makefile per compilare tutti gli elementi del progetto

MINIKERNEL := minikernel

# Da man gcc
#	-nostdlib
#		Do not use the standard system startup files or
#		libraries when linking.  No startup files and only the
#		libraries you specify are passed to the linker, and
#		options specifying linkage of the system libraries,
#		such as -static-libgcc or -shared-libgcc, are ignored.
#	-T script
#		Use script as the linker script.  This option is
#		supported by most systems using the GNU linker.  On
#		some targets, such as bare-board targets without an
#		operating system, the -T option may be required when
#		linking to avoid references to undefined symbols
#
#		In pratica, usarlo quando si compila qualcosa bare metal
#		tipo un OS per far quadrare i pezzi.
$(MINIKERNEL): header.o error.o
	gcc -g -m32 -nostdlib -T likerops.ld $^ -o $(MINIKERNEL)

.PHONY: launch
launch: $(MINIKERNEL)
	./launch.sh

# Opzioni:
#	-c		è per arrestarsi subito dopo la compilazione
#	-m32	dalla doc
#		"Generate code for a 16-bit, 32-bit or 64-bit
#		environment. The -m32 option sets int, long, and pointer
#		types to 32 bits, and generates code that runs on any
#		i386 system."
# Per approfondire:
#	https://gcc.gnu.org/onlinedocs/gcc-10.2.0/gcc/x86-Options.html#x86-Options
header.o: header.S
	gcc -m32 -c header.S

error.o: error.S
	gcc -m32 -c $<

.PHONY: clean
clean:
	rm -f *.o $(MINIKERNEL)

