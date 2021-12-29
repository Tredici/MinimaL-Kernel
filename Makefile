# Makefile per compilare tutti gli elementi del progetto

CC := gcc
CC32 := $(CC) -m32

MINIKERNEL := minikernel

# Da man gcc
#	-ffreestanding
#		Assert that compilation targets a freestanding environment.  This implies
#		-fno-builtin.  A freestanding environment is one in which the standard library may not
#		exist, and program startup may not necessarily be at "main".  The most obvious example
#		is an OS kernel.  This is equivalent to -fno-hosted.
#
#	-fstack-protector
#		Emit extra code to check for buffer overflows, such as stack smashing attacks.  This
#		is done by adding a guard variable to functions with vulnerable objects.  This
#		includes functions that call "alloca", and functions with buffers larger than or equal
#		to 8 bytes.  The guards are initialized when a function is entered and then checked
#		when the function exits.  If a guard check fails, an error message is printed and the
#		program exits.  Only variables that are actually allocated on the stack are
#		considered, optimized away variables or variables allocated in registers don't count.
#
#	-no-pie
#		Don't produce a dynamically linked position independent executable.
#
#	-fno-common
#	-fcommon
#		In C code, this option controls the placement of global variables defined without an
#		initializer, known as tentative definitions in the C standard.  Tentative definitions
#		are distinct from declarations of a variable with the "extern" keyword, which do not
#		allocate storage.
#
#		The default is -fno-common, which specifies that the compiler places uninitialized
#		global variables in the BSS section of the object file.  This inhibits the merging of
#		tentative definitions by the linker so you get a multiple-definition error if the same
#		variable is accidentally defined in more than one compilation unit.
#
#		The -fcommon places uninitialized global variables in a common block.  This allows the
#		linker to resolve all tentative definitions of the same variable in different
#		compilation units to the same object, or to a non-tentative definition.  This behavior
#		is inconsistent with C++, and on many targets implies a speed and code size penalty on
#		global variable references.  It is mainly useful to enable legacy code to link without
#		errors.
#
#		Usato perché un compilatore che ho utilizzato da problemi altrimenti poiché sembra
#		usare l'opzione -fcommon di default.
CFLAGS=-fno-pic -no-pie -fno-stack-protector -ffreestanding -g3 -Wall -fno-common

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
#
#		Per info:
#			https://stackoverflow.com/questions/28474675/arm-common-section-and-fno-common-flag
$(MINIKERNEL): header.o error.o trampoline.o helpers_32bit.o video32bit.o kmain32.o string32.o io32.o
	gcc -g -m32 -nostdlib -T likerops.ld $^ -o $(MINIKERNEL)

.PHONY: rebuild
rebuild: clean $(MINIKERNEL)

.PHONY: launch
launch: $(MINIKERNEL)
	./launch.sh

.PHONY: debug
debug: $(MINIKERNEL)
	./debugging.sh

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

trampoline.o: trampoline.S
	gcc -m32 -c $<

helpers_32bit.o: helpers_32bit.c helpers_32bit.h
	gcc -m32 $(CFLAGS) -c $^ 

io32.o: io32.S io32.h
	gcc -m32 $(CFLAGS) -c $^

video32bit.o: video32bit.c video32bit.h
	gcc -m32 $(CFLAGS) -c $^

string32.o: string32.c string32.h
	gcc -m32 $(CFLAGS) -c $^

kmain32.o: kmain32.c
	gcc -m32 $(CFLAGS) -c $^

.PHONY: clean
clean:
	rm -f *.o *.gch $(MINIKERNEL)

