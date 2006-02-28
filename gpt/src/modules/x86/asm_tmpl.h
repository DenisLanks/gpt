head <<
"%define orgno 0x08048000\n"
"BITS 32             \n"
"ORG     orgno\n"
"\n"
"ehdr:                                            \n"
"              db      0x7F, \"ELF\", 1, 1, 1       \n"
"      times 9 db      0\n"
"              dw      2                          \n"
"              dw      3                          \n"
"              dd      1                          \n"
"              dd      _start                     \n"
"              dd      phdrdata - $$              \n"
"              dd      0                          \n"
"              dd      0                          \n"
"              dw      ehdrsize                   \n"
"              dw      phdrsize                   \n"
"              dw      2                          \n"
"              dw      0                          \n"
"              dw      0                          \n"
"              dw      0                          \n"
"  \n"
"ehdrsize      equ     $ - ehdr\n"
"\n"
"\n"
"phdrdata:                           \n"
"              dd      1             \n"
"              dd      0             \n"
"              dd      orgno         \n"
"              dd      orgno         \n"
"              dd      filesize      \n"
"              dd      filesize      \n"
"              dd      5             \n"
"              dd      0x1000        \n"
"phdrsize      equ     $ - phdrdata\n"
"\n"
"\n"
"phdr_text:\n"
"              dd      1                 \n"
"              dd      _start_no-ehdr    \n"
"              dd      _start            \n"
"              dd      _start            \n"
"              dd      filesize          \n"
"              dd      filesize          \n"
"              dd      6                 \n"
"              dd      0x1000            \n"
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
"\n"
"%macro exit 1\n"
"    mov eax, 1\n"
"    mov ebx, %1\n"
"    int 80h\n"
"%endmacro\n"
"\n"
"%macro print_lf 0\n"
"  addarg 10\n"
"  call __print_c\n"
"  clargs 1\n"
"%endmacro\n"
"\n"
"%define __MEMORY_SIZE  1048576\n"
"%define __BUFFER_SIZE  1024\n"
"\n";

lib << 
"__imprima_literal:\n"
"    %define string ebp+8\n"
"    begin 0\n"
"\n"
"    mov eax, [string]\n"
"    cmp eax, 0\n"
"    jz .end\n"
"\n"
"    addarg dword [string]\n"
"    call __print\n"
"    clargs 1\n"
"\n"
"\n"
"    .end\n"
"      return\n"
"\n"
"__imprima_inteiro:\n"
"    \n"
"    %define num ebp+8\n"
"\n"
"    \n"
"    %define buffer   ebp-__BUFFER_SIZE\n"
"    begin __BUFFER_SIZE\n"
"    \n"
"    lea eax, [buffer]\n"
"    addarg eax\n"
"    addarg dword [num]    \n"
"    call __itoa\n"
"    clargs 2\n"
"\n"
"    lea eax, [buffer]\n"
"    addarg eax\n"
"    call __print\n"
"    clargs 1\n"
"\n"
"    return\n"
"\n"
"__imprima_real:\n"
"    \n"
"    %define num ebp+8\n"
"\n"
"    \n"
"    %define buffer   ebp-__BUFFER_SIZE\n"
"    begin __BUFFER_SIZE\n"
"\n"
"    lea eax, [buffer]\n"
"    addarg eax\n"
"    addarg dword [num]    \n"
"    call __ftoa\n"
"    clargs 2\n"
"\n"
"    lea eax, [buffer]\n"
"    addarg eax\n"
"    call __print\n"
"    clargs 1\n"
"\n"
"\n"
"    return\n"
"  \n"
"__print_c:\n"
"    \n"
"    %define carac ebp+8\n"
"\n"
"    begin 0\n"
"\n"
"    lea eax, [carac]\n"
"    addarg eax\n"
"    call __print\n"
"    clargs 1\n"
"\n"
"    return\n"
"\n"
"__imprima_caractere:\n"
"    \n"
"    %define carac ebp+8\n"
"    begin 4\n"
"    \n"
"    addarg dword [carac]\n"
"    call __print_c\n"
"    clargs 1\n"
"\n"
"    \n"
"    return\n"
"\n"
"__imprima_logico:\n"
"    \n"
"    %define val ebp+8\n"
"\n"
"    begin 0\n"
"\n"
"    mov eax, [val]\n"
"    cmp eax, 0\n"
"    jz .false\n"
"    mov eax, __str_true\n"
"    jmp .print\n"
"\n"
"    .false:\n"
"      mov eax, __str_false\n"
"\n"
"    .print:\n"
"      addarg eax\n"
"      call __print\n"
"      clargs 1\n"
"\n"
"  \n"
"    return\n"
"\n"
"__strpos:\n"
"    \n"
"    %define string ebp+12\n"
"    %define carac  ebp+8\n"
"\n"
"    begin 0\n"
"\n"
"    mov eax, [string]\n"
"    cmp eax, 0\n"
"    jnz .calc\n"
"\n"
"    mov eax, 0\n"
"    return\n"
"\n"
"    .calc:\n"
"      mov eax, 0\n"
"      .do:\n"
"        mov ebx, [string]\n"
"        mov ecx, [carac]\n"
"        cmp [ebx+eax], cl\n"
"        jz  .break\n"
"\n"
"        cmp [ebx+eax], byte 0\n"
"        jz .notfound\n"
"\n"
"        inc eax\n"
"        jnz .do\n"
"      .break:\n"
"\n"
"    return\n"
"\n"
"    .notfound\n"
"      mov eax, -1\n"
"      return\n"
"\n"
"__strlen:\n"
"    \n"
"    %define string ebp+8\n"
"\n"
"    begin 0\n"
"\n"
"    addarg dword [string]\n"
"    addarg 0\n"
"    call __strpos\n"
"    clargs 2\n"
"\n"
"    return\n"
"\n"
"__print:\n"
"    \n"
"    %define string ebp+8\n"
"\n"
"    begin 0\n"
"\n"
"    addarg dword [string]\n"
"    call __strlen\n"
"    clargs 1\n"
"\n"
"    mov edx, eax\n"
"    mov eax, 4\n"
"    mov ebx, 1\n"
"    mov ecx, [string]\n"
"    int 80h\n"
"\n"
"    return\n"
"\n"
"__is_num:\n"
"    \n"
"    %define carac ebp+8\n"
"\n"
"    begin 0\n"
"\n"
"    cmp byte  [carac], 48\n"
"    jl .false\n"
"\n"
"    cmp byte [carac], 57\n"
"    jg .false\n"
"\n"
"    mov eax, 1\n"
"    return\n"
"\n"
"    .false:\n"
"      mov eax, 0\n"
"      return\n"
"\n"
"__atoi:\n"
"    \n"
"    %define string ebp+8\n"
"  \n"
"    \n"
"    %define num   ebp-4\n"
"    %define m     ebp-8\n"
"    %define i     ebp-12\n"
"    %define len   ebp-16\n"
"    %define negt  ebp-20\n"
"    begin 20\n"
"  \n"
"    mov dword [num], 0\n"
"    mov dword [m], 1\n"
"  \n"
"    addarg dword [string]\n"
"    call __strlen\n"
"    clargs 1\n"
"\n"
"    cmp eax, dword 0\n"
"    jz .ret_zero\n"
"\n"
"    mov dword [len], eax\n"
"    mov dword [i], 0\n"
"\n"
"    \n"
"    %define minus_sig 45 \n"
"    %define plus_sig 43\n"
"    mov eax, [string]\n"
"    xor ebx, ebx\n"
"    mov bl, [eax]\n"
"\n"
"    cmp ebx, minus_sig\n"
"    jz .negative\n"
"\n"
"    cmp ebx, plus_sig\n"
"    jz .positive\n"
"\n"
"    jmp .conv\n"
"\n"
"    .negative\n"
"      mov dword [negt], 1\n"
"      mov eax, [string]\n"
"      inc eax\n"
"      mov [string], eax\n"
"      jmp .conv\n"
"\n"
"    .positive\n"
"      mov dword [negt], 0\n"
"      mov eax, [string]\n"
"      inc eax\n"
"      mov [string], eax\n"
"\n"
"  .conv:\n"
"\n"
"    mov eax, [len]\n"
"    .while:\n"
"      mov eax, dword [i]\n"
"      cmp eax, [len]\n"
"      jg .endwhile      \n"
"      \n"
"      mov ebx, [string]\n"
"      mov ecx, [i]        \n"
"      xor edx, edx\n"
"      mov dl, [ebx+ecx]      \n"
"\n"
"      addarg edx\n"
"      call __is_num\n"
"      clargs 1\n"
"  \n"
"      cmp eax, 0\n"
"      jz .endwhile\n"
"  \n"
"      inc dword [i]\n"
"      jmp .while\n"
"    .endwhile:\n"
"  \n"
"    cmp dword [i], 0\n"
"    jz .ret_zero\n"
"  \n"
"\n"
"    dec dword [i]    \n"
"    \n"
"    .while2:\n"
"      cmp dword [i], 0\n"
"      jl .endwhile2\n"
"\n"
"      \n"
"      mov ebx, [string]\n"
"      mov ecx, [i]\n"
"      xor eax, eax\n"
"      mov al, byte [ebx+ecx]\n"
"\n"
"      \n"
"      sub al, 48\n"
"\n"
"      mul dword [m]      \n"
"\n"
"      \n"
"      add [num], eax\n"
"\n"
"      dec dword [i]\n"
"\n"
"      \n"
"      mov eax, [m]\n"
"      mov ebx, 10\n"
"      mul ebx\n"
"      mov [m], eax\n"
"\n"
"      jmp .while2\n"
"    .endwhile2:\n"
"  \n"
"    cmp dword [negt], 1\n"
"    jnz .return_pos\n"
"\n"
"    mov eax, [num]\n"
"    neg eax\n"
"    return\n"
"   \n"
"    .return_pos\n"
"      mov eax, [num]\n"
"      return\n"
"\n"
"    .ret_zero\n"
"      mov eax, 0\n"
"      return\n"
"\n"
"__atof:\n"
"    \n"
"    %define string ebp+8\n"
"\n"
"    \n"
"    %define negt     ebp-4\n"
"    %define dotpos   ebp-8\n"
"    %define declen   ebp-12\n"
"    %define str_dec  ebp-16\n"
"    %define inte     ebp-20\n"
"    %define deci     ebp-24\n"
"    %define p        ebp-28\n"
"    %define float    ebp-32\n"
"    \n"
"    begin 32\n"
"\n"
"    addarg dword [string]\n"
"    call __strlen\n"
"    clargs 1\n"
"\n"
"    cmp eax, dword 0\n"
"    jz .ret_zero\n"
"\n"
"    \n"
"    %define minus_sig 45 \n"
"    %define plus_sig 43\n"
"    mov eax, [string]\n"
"    xor ebx, ebx\n"
"    mov bl, [eax]\n"
"\n"
"    cmp ebx, minus_sig\n"
"    jz .negative\n"
"\n"
"    cmp ebx, plus_sig\n"
"    jz .positive\n"
"\n"
"    jmp .conv\n"
"\n"
"    .negative\n"
"      mov dword [negt], 1\n"
"      mov eax, [string]\n"
"      inc eax\n"
"      mov [string], eax\n"
"      jmp .conv\n"
"\n"
"    .positive\n"
"      mov dword [negt], 0\n"
"      mov eax, [string]\n"
"      inc eax\n"
"      mov [string], eax\n"
"\n"
"  .conv:\n"
"\n"
"    addarg dword [string]\n"
"    addarg '.'\n"
"    call __strpos\n"
"    clargs 2\n"
"    \n"
"    mov dword [dotpos], eax\n"
"\n"
"    \n"
"    mov eax, [string]\n"
"    add eax, [dotpos]\n"
"    inc eax\n"
"\n"
"    mov [str_dec], eax\n"
"\n"
"    addarg dword [str_dec]\n"
"    call __strlen\n"
"    clargs 1\n"
"    \n"
"    mov dword [declen], eax    \n"
"\n"
"    addarg dword [str_dec]\n"
"    call __atoi\n"
"    clargs 1\n"
"\n"
"    mov dword [deci], eax\n"
"\n"
"    mov eax, [string]\n"
"    add eax, [dotpos]\n"
"    mov [eax], byte 0\n"
"\n"
"    addarg dword [string]\n"
"    call __atoi\n"
"    clargs 1\n"
"\n"
"    mov [inte], eax\n"
"\n"
"    mov eax, dword [declen]\n"
"    \n"
"    addarg 10\n"
"    addarg eax\n"
"    call __pow\n"
"    clargs 2\n"
"\n"
"    mov dword [p], eax\n"
"\n"
"    fninit\n"
"    fld   dword [deci]\n"
"    fdiv  dword [p]\n"
"    fiadd  dword [inte]\n"
"    fstp  dword [float]\n"
"\n"
"    cmp dword [negt], 1\n"
"    jnz .return_pos\n"
"\n"
"    mov eax, [float]\n"
"    or eax, 0x80000000\n"
"    return\n"
"   \n"
"    .return_pos\n"
"      mov eax, [float]\n"
"      return\n"
"\n"
"    .ret_zero\n"
"      mov eax, 0\n"
"      return\n"
"\n"
"    exit 0\n"
"\n"
"__itoa:\n"
"    \n"
"    %define buffer ebp+12\n"
"    %define num ebp+8\n"
"\n"
"    \n"
"    %define sig ebp-4\n"
"    begin 4\n"
"\n"
"    \n"
"    mov eax, [num]\n"
"    mov [sig], eax\n"
"    shr eax, 31\n"
"    mov [sig], eax    \n"
"\n"
"    cmp [sig], dword 0\n"
"    jz .endif\n"
"      neg dword [num]\n"
"    .endif:\n"
"\n"
"    \n"
"    mov ecx, 0\n"
"    mov eax, [num] \n"
"    .trans\n"
"      mov ebx, 10\n"
"      mov edx, 0\n"
"      idiv ebx   \n"
"      add edx, byte 48\n"
"      push edx\n"
"      inc ecx \n"
"    cmp eax, 0\n"
"    jnz .trans\n"
"\n"
"    \n"
"    cmp [sig], dword 0\n"
"    jz .else1\n"
"      %define minus_sig 45\n"
"      mov edx, 1 \n"
"      mov eax, [buffer]\n"
"      mov [eax], byte minus_sig            \n"
"      jmp .endif1\n"
"    .else1:\n"
"      mov edx, 0 \n"
"    .endif1\n"
"    \n"
"    .reorder\n"
"      pop eax\n"
"      mov ebx, [buffer]\n"
"      mov [ebx+edx], eax \n"
"      dec ecx \n"
"      inc edx \n"
"    cmp ecx, 0 \n"
"    jnz .reorder\n"
"\n"
"    return\n"
"\n"
"__ftoa:\n"
"    %define BIAS 127\n"
"\n"
"    \n"
"    %define buffer ebp+12\n"
"    %define num ebp+8\n"
"\n"
"    \n"
"    %define exp    ebp-4\n"
"    %define mant   ebp-8\n"
"    %define left   ebp-12\n"
"    %define sig    ebp-16    \n"
"    %define offset ebp-20\n"
"    %define r      ebp-24\n"
"    %define term   ebp-28\n"
"    %define acc    ebp-32\n"
"    %define tmp    ebp-36\n"
"    %define right  ebp-40\n"
"    \n"
"    %define lst    40    \n"
"  \n"
"    begin lst\n"
"\n"
"    \n"
"    mov eax, [num]\n"
"    mov [sig], eax\n"
"    shr eax, 31\n"
"    mov [sig], eax\n"
"\n"
"    \n"
"    mov eax, [num]\n"
"    and eax, 0x7FFFFFFF\n"
"    mov [num], eax\n"
"\n"
"    \n"
"    mov eax, [num]\n"
"    shr eax, 23\n"
"    mov [exp], eax\n"
"\n"
"    \n"
"    mov eax, [num]\n"
"    and eax, 0x7FFFFF\n"
"    mov [mant], eax\n"
"\n"
"    \n"
"    mov eax, [exp]      \n"
"    mov ebx, [mant]\n"
"    or eax, ebx\n"
"      cmp eax, 0\n"
"      jnz .endif\n"
"      mov dword [tmp], 0x00302E30\n"
"      lea eax, [tmp]\n"
"      mov dword [eax+3], 0x00000030\n"
"      addarg eax\n"
"      addarg dword [buffer]\n"
"      call __strcpy\n"
"      clargs 2 \n"
"      jmp .end\n"
"    .endif:\n"
"\n"
"    \n"
"    sub [exp], dword BIAS\n"
"  \n"
"    \n"
"    or [mant], dword 0x800000\n"
"\n"
"    \n"
"    \n"
"    \n"
"    \n"
"    \n"
"    mov eax, 25\n"
"    sub eax, [exp]\n"
"      cmp eax, 32\n"
"      jg .else1   \n"
"      mov eax, [mant]\n"
"      mov ecx, 23\n"
"      sub ecx, [exp]\n"
"      shr eax, cl\n"
"      mov [left], eax\n"
"      jmp .endif1\n"
"    .else1:\n"
"      mov [left], dword 0\n"
"    .endif1:\n"
"\n"
"    \n"
"    \n"
"    \n"
"    \n"
"    \n"
"    \n"
"    mov eax, 9\n"
"    add eax, [exp]\n"
"      cmp eax, 0\n"
"      jl .else2\n"
"      mov ecx, 9\n"
"      add ecx, [exp]\n"
"      mov eax, [mant]\n"
"      shl eax, cl\n"
"      mov [mant], eax\n"
"      jmp .endif2\n"
"    .else2:\n"
"      mov ecx, [exp]\n"
"      sub ecx, 9\n"
"      mov eax, [mant]\n"
"      shr eax, cl          \n"
"    .endif2:\n"
"\n"
"\n"
"    \n"
"    mov [offset], dword 31\n"
"\n"
"    \n"
"    mov eax, [mant]\n"
"    mov [r], eax\n"
"\n"
"    \n"
"    mov [term], dword 1\n"
"\n"
"    \n"
"    mov [acc], dword 0\n"
"\n"
"\n"
"    fninit\n"
"\n"
"    \n"
"    .while:    \n"
"      mov eax, [offset]\n"
"      cmp eax, 1\n"
"      jz .endwhile\n"
"  \n"
"      \n"
"      mov eax, [r]\n"
"      mov ecx, [offset]\n"
"      shr eax, cl\n"
"      and eax, 1\n"
"        cmp eax, 0\n"
"        jz .endif3\n"
"  \n"
"        \n"
"        mov eax, 2\n"
"        mov ebx, [term]\n"
"        neg ebx\n"
"\n"
"        addarg eax\n"
"        addarg ebx\n"
"        call __pow \n"
"        clargs 2\n"
"\n"
"        mov [tmp], eax\n"
"  \n"
"        fld  dword [acc] \n"
"        fadd dword [tmp]\n"
"        fstp dword [acc]\n"
"      .endif3:\n"
"\n"
"      \n"
"      inc dword [term]\n"
"\n"
"      \n"
"      dec dword [offset]\n"
"      jmp .while\n"
"    .endwhile:\n"
"\n"
"    fninit\n"
"\n"
"    \n"
"    fld dword [acc] \n"
"    mov [tmp], dword 100\n"
"    fimul dword [tmp]\n"
"    \n"
"    frndint\n"
"    \n"
"    fist dword [acc]\n"
"\n"
"    mov eax, [acc]\n"
"    mov [right], eax\n"
"\n"
"\n"
"    \n"
"\n"
"    cmp [sig], dword 0\n"
"    jz .endif5\n"
"      neg dword [left]\n"
"    .endif5:\n"
"\n"
"    addarg dword [buffer]\n"
"    addarg dword [left]\n"
"    call __itoa\n"
"    clargs 2\n"
"    \n"
"    \n"
"    addarg dword [buffer]\n"
"    call __strlen\n"
"    clargs 1\n"
"\n"
"    add eax, dword [buffer]\n"
"    mov [eax], byte '.'\n"
"    inc eax\n"
"    mov [tmp], eax    \n"
"\n"
"    \n"
"    %define buffer2 ebp-lst+4\n"
"    %define bfsize  1024\n"
"    sub  esp, bfsize\n"
"\n"
"    addarg dword [buffer2]\n"
"    addarg dword [right]\n"
"    call __itoa\n"
"    clargs 2\n"
"    \n"
"\n"
"    addarg dword [buffer2]\n"
"    call __strlen\n"
"    clargs 1\n"
"\n"
"    \n"
"    cmp eax, 2\n"
"    jz .endif4\n"
"      %define zero 48\n"
"      xor eax, eax\n"
"      mov ebx, [buffer2]\n"
"      mov al, [ebx]\n"
"      mov [ebx], byte zero\n"
"      mov byte [ebx+1], al\n"
"    .endif4:\n"
"\n"
"    mov eax, [buffer2]\n"
"    mov ebx, [tmp]\n"
"    .append:\n"
"      cmp [eax], byte 0\n"
"      jz .endappend\n"
"      \n"
"      xor ecx, ecx\n"
"      mov cl, [eax]\n"
"      mov [ebx], cl\n"
"      inc eax\n"
"      inc ebx\n"
"      jmp .append\n"
"    .endappend:\n"
"\n"
"    mov [ebx], byte 0\n"
"\n"
"  .end\n"
"    return\n"
"\n"
"__pow:\n"
"    \n"
"    %define base ebp+12\n"
"    %define exp  ebp+8\n"
"\n"
"    \n"
"    %define res  ebp-4\n"
"    %define i    ebp-8\n"
"    %define sig  ebp-12\n"
"    %define tmp  ebp-16\n"
"    begin 14\n"
"\n"
"    \n"
"    mov eax, [exp]\n"
"    mov ecx, 31\n"
"    shr eax, cl\n"
"    mov [sig], eax\n"
"\n"
"\n"
"    \n"
"    mov eax, [sig]\n"
"    cmp eax, 0\n"
"    jz .endif\n"
"      mov eax, [exp]\n"
"      neg eax\n"
"      mov [exp], eax\n"
"    .endif:\n"
"\n"
"    \n"
"    mov [res], dword 1\n"
"\n"
"    \n"
"    mov [i], dword 0\n"
"    .while:\n"
"      mov eax, [i]\n"
"      cmp eax, [exp]\n"
"      jge .endwhile\n"
"\n"
"      \n"
"      mov eax, [res]\n"
"      mul dword [base]\n"
"      mov [res], eax\n"
"\n"
"      \n"
"      inc dword [i]\n"
"      jmp .while\n"
"    .endwhile:\n"
"\n"
"    \n"
"    cmp [sig], dword 0\n"
"    jz .noneg\n"
"    .negative:\n"
"      fninit\n"
"      mov [tmp], dword 0x3F800000 \n"
"  \n"
"      fld   dword [tmp]\n"
"      fidiv dword [res]\n"
"      fstp  dword [res]\n"
"    .noneg:\n"
"\n"
"    mov eax, [res]\n"
"\n"
"    return\n"
"\n"
"matrix_init__:\n"
"    \n"
"    %define matrix      ebp+16\n"
"    %define is_string   ebp+12\n"
"    %define msize       ebp+8\n"
"\n"
"    \n"
"    %define total     ebp-4\n"
"    begin 4\n"
"\n"
"    cmp [is_string], dword 0\n"
"    jnz .else\n"
"      mov eax, [msize]\n"
"      mov [total], eax\n"
"      jmp .endif\n"
"    .else:\n"
"      mov eax, [msize]\n"
"      mov ebx, 32 \n"
"      mul ebx\n"
"      mov [total], eax\n"
"    .endif:\n"
"  \n"
"    mov eax, 0\n"
"    .while:\n"
"      cmp eax, [total]\n"
"      jge .endwhile\n"
"      mov ecx, [matrix]\n"
"      add ecx, eax\n"
"      mov [ecx], byte 0\n"
"      inc eax\n"
"      jmp .while\n"
"    .endwhile:\n"
"\n"
"    return\n"
"\n"
"__matrix_cpy:\n"
"    \n"
"    %define src       ebp+20\n"
"    %define dest      ebp+16\n"
"    %define is_string ebp+12\n"
"    %define msize     ebp-8\n"
"\n"
"    \n"
"    %define total     ebp-4\n"
"    begin 4\n"
"\n"
"    cmp [is_string], dword 0\n"
"    jnz .else\n"
"      mov eax, [msize]\n"
"      mov [total], eax\n"
"      jmp .endif\n"
"    .else:\n"
"      mov eax, [msize]\n"
"      mov ebx, 32 \n"
"      mul ebx\n"
"      mov [total], eax\n"
"    .endif:\n"
"\n"
"\n"
"    mov eax, 0\n"
"    .while:\n"
"      cmp eax, [total]\n"
"      jge .endwhile\n"
"      mov ebx, [src]\n"
"      add ebx, eax\n"
"      mov ecx, [dest]\n"
"      add ecx, eax\n"
"      mov edx, [ecx]\n"
"      mov [ecx], edx\n"
"      inc eax\n"
"      jmp .while\n"
"    .endwhile:\n"
"\n"
"    return\n"
"\n"
"__strcpy:\n"
"    \n"
"    %define src    ebp+12\n"
"    %define dest   ebp+8\n"
"\n"
"    \n"
"    %define src_len     ebp-4\n"
"    begin 4\n"
"\n"
"    addarg dword [src]\n"
"    call __strlen\n"
"    clargs 1\n"
"\n"
"    mov [src_len], eax\n"
"\n"
"    cmp eax, [src_len]\n"
"    jnz .end\n"
"    \n"
"    mov eax, 0\n"
"    mov edx, [dest]\n"
"    .while:\n"
"      cmp eax, [src_len]\n"
"      jge .endwhile\n"
"\n"
"      mov ebx, [src]\n"
"      xor ecx, ecx\n"
"      mov cl, [ebx+eax]\n"
"\n"
"      mov [edx+eax], cl\n"
"\n"
"      inc eax\n"
"      jmp .while\n"
"    .endwhile:\n"
"\n"
"    mov [edx+eax], byte 0\n"
"\n"
"    .end:\n"
"      return\n"
"\n"
"__strcmp:\n"
"    \n"
"    %define left    ebp+12\n"
"    %define right   ebp+8\n"
"\n"
"    \n"
"    %define left_len     ebp-4\n"
"    %define l            ebp-8\n"
"    %define r            ebp-12\n"
"    begin 12\n"
"\n"
"    addarg dword [left]\n"
"    call __strlen\n"
"    clargs 1\n"
"\n"
"    mov [left_len], eax\n"
"\n"
"    addarg dword [right]\n"
"    call __strlen\n"
"    clargs 1\n"
"\n"
"    cmp eax, [left_len]\n"
"    jnz .false\n"
"\n"
"    mov eax, 0\n"
"    .while:\n"
"      cmp eax, [left_len]\n"
"      jge .endwhile\n"
"\n"
"      mov ebx, [left]\n"
"      xor edx, edx\n"
"      mov dl, [ebx+eax]\n"
"\n"
"      mov ebx, [right]\n"
"      xor ecx, ecx\n"
"      mov cl, [ebx+eax]\n"
"      \n"
"      cmp edx, ecx\n"
"      jnz .false\n"
"\n"
"      inc eax\n"
"      jmp .while\n"
"    .endwhile:\n"
"\n"
"    mov eax, 1\n"
"    return\n"
"\n"
"  .false\n"
"    mov eax, 0 \n"
"    return\n"
"\n"
"__malloc:\n"
"    \n"
"    %define size   ebp+8\n"
"\n"
"    begin 0\n"
"\n"
"    cmp [size], dword 0\n"
"    jnz .alloc\n"
"\n"
"    mov eax, 0\n"
"    return\n"
"\n"
"    .alloc:\n"
"      mov eax, __mem        \n"
"      add eax, [__mem_ptr]  \n"
"      add eax, [size]       \n"
"  \n"
"      mov ebx,  __mem      \n"
"      add ebx, __MEMORY_SIZE \n"
"\n"
"      cmp eax, ebx\n"
"      jg .no_memory_left\n"
"\n"
"      \n"
"      mov eax, __mem\n"
"      add eax, [__mem_ptr]\n"
"  \n"
"      \n"
"      mov ebx, [__mem_ptr]\n"
"      add ebx, [size]\n"
"      mov [__mem_ptr], ebx\n"
"\n"
"      return\n"
"    \n"
"   .no_memory_left:\n"
"      addarg __str_no_mem_left\n"
"      call __imprima_literal\n"
"      clargs 1\n"
"      exit 1\n"
"\n"
"__leia_caractere:\n"
"    %define buffer   ebp-__BUFFER_SIZE\n"
"    begin __BUFFER_SIZE\n"
"    \n"
"    \n"
"    lea eax, [buffer]\n"
"    addarg eax\n"
"    addarg __BUFFER_SIZE\n"
"    call __readline\n"
"    clargs 2\n"
"    \n"
"    lea ebx, [buffer]\n"
"    xor eax, eax\n"
"    mov al, [ebx]\n"
"\n"
"    return\n"
"\n"
"__leia_real:\n"
"    %define buffer   ebp-__BUFFER_SIZE    \n"
"    begin __BUFFER_SIZE\n"
"    \n"
"    \n"
"    lea eax, [buffer]\n"
"    addarg eax\n"
"    addarg __BUFFER_SIZE\n"
"    call __readline\n"
"    clargs 2\n"
"    \n"
"    lea eax, [buffer]\n"
"    addarg eax\n"
"    call __atof\n"
"    clargs 1\n"
"\n"
"    return\n"
"\n"
"__leia_inteiro:\n"
"    %define buffer   ebp-__BUFFER_SIZE\n"
"    begin __BUFFER_SIZE\n"
"    \n"
"    \n"
"    lea eax, [buffer]\n"
"    addarg eax\n"
"    addarg __BUFFER_SIZE\n"
"    call __readline\n"
"    clargs 2\n"
"    \n"
"    lea eax, [buffer]\n"
"    addarg eax\n"
"    call __atoi\n"
"    clargs 1\n"
"\n"
"    return\n"
"\n"
"__leia_logico:\n"
"    %define zero_str ebp-4\n"
"    %define buffer   ebp-4-__BUFFER_SIZE\n"
"    begin (4+__BUFFER_SIZE)\n"
"    \n"
"    mov [zero_str], dword 0x00000030 \n"
"\n"
"    \n"
"    lea eax, [buffer]\n"
"    addarg eax\n"
"    addarg __BUFFER_SIZE\n"
"    call __readline\n"
"    clargs 2\n"
"\n"
"    \n"
"    lea eax, [buffer]\n"
"    addarg eax\n"
"    addarg __str_false\n"
"    call __strcmp\n"
"    clargs 2\n"
"\n"
"    cmp eax, 1\n"
"    jz .false\n"
"\n"
"    \n"
"    lea eax, [zero_str]\n"
"    lea ebx, [buffer]\n"
"    addarg eax\n"
"    addarg ebx\n"
"    call __strcmp\n"
"    clargs 2\n"
"\n"
"    cmp eax, 1\n"
"    jz .false\n"
"\n"
"    mov eax, 1\n"
"    return\n"
"\n"
"    .false:\n"
"      mov eax, 0\n"
"      return\n"
"\n"
"__leia_literal:\n"
"    %define string ebp-4\n"
"    begin 4\n"
"\n"
"    addarg __BUFFER_SIZE\n"
"    call __malloc\n"
"    clargs 1\n"
"\n"
"    mov [string], eax\n"
"\n"
"    addarg dword [string]\n"
"    addarg __BUFFER_SIZE\n"
"    call __readline\n"
"    clargs 2\n"
"\n"
"    mov eax, [string]\n"
"    return\n"
"\n"
"__readline:\n"
"    \n"
"    %define buffer   ebp+12\n"
"    %define size     ebp+8\n"
"    begin 0\n"
"\n"
"    \n"
"    mov eax, 3 \n"
"    mov ebx, 0 \n"
"    mov ecx, [buffer]\n"
"    mov edx, [size]\n"
"    int 80h\n"
"\n"
"    \n"
"    mov ebx, [buffer]\n"
"    mov [ebx+eax-1], byte 0\n"
"\n"
"    return\n\n"
"filesize   equ     $ - $$\n";
