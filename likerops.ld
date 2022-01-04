/**
 * Script per il linker.
 * Per il formato vedere qui:
 *  https://sourceware.org/binutils/docs/ld.html
 */

/**
 * [3.4.3 Commands Dealing with Object File Formats]
 *  OUTPUT_FORMAT(bfdname)
 *      The OUTPUT_FORMAT command names the BFD format to use
 *      for the output file (see BFD). Using
 *      OUTPUT_FORMAT(bfdname) is exactly like using ‘--oformat
 *      bfdname’ on the command line (see Command-line Options).
 *      If both are used, the command line option takes
 *      precedence.
 */
/* OUTPUT_FORMAT(elf64-little) */

/**
 * [3.4.5 Other Linker Script Commands]
 *  OUTPUT_ARCH(bfdarch)
 *      Specify a particular output machine architecture.
 *      The argument is one of the names used by the BFD
 *      library (see BFD). You can see the architecture of an
 *      object file by using the objdump program with the ‘-f’
 *      option.
 *  BFD: https://sourceware.org/binutils/docs/ld.html#BFD
 *  [6 BFD]
 *      [...] You can use objdump -i (see objdump in The GNU
 *      Binary Utilities) to list all the formats available for
 *      your configuration.
 *  objdump: https://sourceware.org/binutils/docs/binutils/objdump.html#objdump
 */
/* OUTPUT_ARCH(i386) */
/**
 * [3.4.1 Setting the Entry Point]
 * Non dovrebbe servire (ci pensa il bootloader a invocare la
 * routine di ingresso) ma lo metto comunque.
 */
ENTRY(_start)


/**
 * Per specificare al linker come assemblare il tutto.
 * See:
 *  https://sourceware.org/binutils/docs/ld.html#SECTIONS
 *
 * [3.6 SECTIONS Command]
 *  If you do not use a SECTIONS command in your linker script,
 *  the linker will place each input section into an identically
 *  named output section in the order that the sections are
 *  first encountered in the input files. If all input sections
 *  are present in the first file, for example, the order of
 *  sections in the output file will match the order in the
 *  first input file. The first section will be at address zero.
 *
 *  Poichè ci serve che l'header multiboot sia all'inizio della
 *  sezione .text dobbiamo forzare il linker a riordinare il
 *  tutto.
 *
 *  Bisogna ricordare, inoltre, che gli indirizzi che si
 *  troveranno nel codice di boot sono FISICI e non saranno
 *  rilocati automaticamente al caricamento di questo sistema
 *  minimale.
 *
 *  Serve ricordare, inoltre, che il primo MB di memoria fisica
 *  va tenuto vuoto dal codice perché contiene cose mappate in
 *  memoria (memoria video incluse) ed è bene, pertanto, evitare
 *  di combinare disastri.
 */
/**
 * Per ispezionare il formato del file prodotto usare readelf:
 *  https://sourceware.org/binutils/docs/binutils/readelf.html
 */
SECTIONS
{
    /**
     * Per il formato dei campi vedere:
     *  [3.6.1 Output Section Description]
     *      The WHITESPACE AROUND SECTION IS REQUIRED, so that
     *      the section name is unambig uous. The colon and the
     *      curly braces are also required. The comma at the
     *      end may be required if a fillexp is used and the
     *      next sections-command looks like a continuation of
     *      the expression. The line breaks and other white
     *      space are optional.
     *
     * Per capire come specificare le sezioni da includere
     * vedere [3.6.4 Input Section Description].
     * Per i dettagli su ciò che va a destra dell'uguale vedere
     * [3.6.4.1 Input Section Basics]
     */
    /**
     * Il primo MB deve rimanere vuoto altrimenti è un disastro
     *
     * [3.10.5 The Location Counter]
     *  The special linker variable dot ‘.’ always contains the
     *  current output location counter.
     */
    . = 0x100000;
    /**
     * La seconda è la sezione .text che deve iniziare con
     * l'header multiboot
     */
    .text : { *(.multiboot_header) *(.text) }
    /**
     * Poi si mette rodata che penso sia generata dal processo
     * di compilazione per i file con constanti globali e cose
     * così "constexpr". Nella pratica non saprei.
     */
    .rodata : { *(.rodata) }
    /**
     * Si ricordi che nella definizione dell'header multiboot
     * erano stati nominati i simboli:
     *      - _end_of_data
     *      - _end_of_bss
     *  Questi vengono definiti ora e diventano disponibili
     *  durante il processo di linking.
     *  Per approfondimenti:
     *      [3.5 Assigning Values to Symbols]
     *      [3.5.1 Simple Assignments] mostra un esempio
     *          The special symbol name ‘.’ indicates the
     *          location counter. You may only use this within
     *          a SECTIONS command. See Location Counter.
     */
    /**
     * Poi quella per i dati rw, che credo siano le variabili
     * globali
     */
    .data : { *(.data) _end_of_data = .; }
    /**
     * Infine, si mette la parte bss che non dovrebbe occupare
     * spazio nel file ma essere generata solo al momento del
     * caricamento.
     */
    .bss : { *(.bss) _end_of_bss = .; }
    /**
     * E alla fine si scarta tutto il resto per evitare
     * stranezze.
     * [3.6.7 Output Section Discarding]
     *      The special output section name ‘/DISCARD/’ may be
     *      used to discard input sections. Any input sections
     *      which are assigned to an output section named
     *      ‘/DISCARD/’ are not included in the output file. 
     */
    "/DISCARD/" : { *(*) }
}
