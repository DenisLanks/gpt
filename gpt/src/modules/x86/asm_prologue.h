/* Common definitions */

_head <<
"\n"
"%macro  begin 1\n"
"    push    ebp \n"
"    mov     ebp,esp\n"
"  %if %1\n"
"    sub     esp,%1\n"
"  %endif\n"
"%endmacro\n"
"\n"
"%macro return 0\n"
"    mov esp, ebp\n"
"    pop ebp  \n"
"    ret\n"
"%endmacro\n"
"\n"
"%macro addarg 1\n"
"    push %1\n"
"%endmacro\n"
"\n"
"%macro clargs 1\n"
"    add esp, 4 * %1\n"
"%endmacro\n"
"\n"
"%macro print_lf 0\n"
"  addarg 10\n"
"  call print_c\n"
"  clargs 1\n"
"%endmacro\n"
"\n"
"%define SIZEOF_DWORD 4\n"
"%define MEMORY_SIZE  1048576\n"
"%define BUFFER_SIZE  1024\n"
"\n";
