
\       ****        GF      ****

\ Name    : GF
\ Version : 0.2
\ Aim     : Provide word set for every day administrative goals
\ Author  : (c) 2020-2021, Alexander (Shurko) Stadnichenko
\ License : BSD
\ Started : 2020-08-02
\ Updated : 2021-01-18
\ Fileupd : 2021-01-18


: this-script-current-path
    s" /home/Main/Scripts/Gf/gf.common.fs" ;

' this-script-current-path alias gf-path

: gf-launcher
    s" /home/Main/Scripts/Gf/gf.common" ;

: default-shell-workdir
    s" /home/share" ;


cr cr ." GF included. Type 'gf-help' for details" cr cr


: gf-help
    cr
    cr ." GF help"
    cr
    cr ." this-script-current-path, gf-path - current path for [reload] this script"
    cr ." mk-gf-symbolink - link to gf-launcher in /usr/bin"
    cr ." reload-gf - reload this script"
    cr ." bb - bye"
    cr
    cr ." .current-shell-workdir - print current work dir"
    cr ." >current-shell-workdir - setup current work dir"
    cr
    cr ." pwd - just invoke 'pwd'"
    cr ." cls - clear screen"
    cr ." spn - shutdown (poweroff) now"
    cr ." reboot - reboot machine"
    cr ." suspend - invoke 'systemctl suspend'"
    cr ." shred-s , shred-v - shred silent/verbosely"
    cr ." bkp - make dump of '/home' to HD"
    cr ." mk-symbolink - invoke 'ln -s'"
    cr ." rm-file - invoke 'rm'"
    cr ." ls - invoke 'ls'"
    cr ." type-files - list of files recursively"
    cr cr ;


: reload-gf
    gf-path included cr ;


create sbuff align 1024 allot
0 value sused

: +str
    sbuff sused +
    swap dup sused + to sused
    move ;

: .sbuff sbuff sused cr type cr ;

: rsbuff 0 to sused ;

: ""    s" " ;
: "bl"  s"  " ;

: +bl
    "bl" +str ;

: buff
    sbuff sused ;

: shell-eval
    buff system ;




create shell-workdir-global-nstr 0 , 1024 allot

: nstr>fstr
    dup cell+ swap @ ;

: shell-workdir-current->fstr
    shell-workdir-global-nstr nstr>fstr ;

: .current-shell-workdir
    shell-workdir-current->fstr type ;

: >current-shell-workdir ( addr len -- )
    dup >r
    shell-workdir-global-nstr cell+ swap move
    r> shell-workdir-global-nstr ! ;

default-shell-workdir >current-shell-workdir


\ A bit of aliases for short shell commands


: template
    rsbuff
    s"  somestr" +str shell-eval ;

: bb bye ;

: cls
    s" clear" system ;

: pwd
    s" pwd" system ;

: spn
    s" shutdown -P now" system ;

: reboot
    s" reboot" system ;

' reboot alias reb

: shred-s ( a u -- )
    rsbuff
    s" shred -uzn1 " +str +str
    shell-eval ;

: shred-v ( a u -- )
    rsbuff
    s" shred -uvzn1 " +str +str
    shell-eval ;

: bkp
    s" cd /home/Main/Scripts && sudo ./d2.bash.sh" system ;

: mk-symbolink
    rsbuff
    s" ln -s " +str
    +str +bl +str
    shell-eval ;

: mk-gf-symbolink
    s" /usr/bin/gf"
    gf-launcher
    mk-symbolink ;

: rm-file
    rsbuff
    s" sudo rm " +str +str shell-eval ;

: ls ( raw-str len -- )
    rsbuff
    s" ls " +str +str shell-eval ;

: +"cd-<current-shell-workdir>-&&"
    s" cd " +str
    shell-workdir-current->fstr +str
    s"  && " +str ;

: crypt-3gpp
    rsbuff
    +"cd-<current-shell-workdir>-&&"
    s" find . -name '*.3gpp' -type f -printf '%p\0' | xargs -0 -n1 -I 'somename-dot-3gpp' openssl enc -e -aes-256-cbc -in 'somename-dot-3gpp' -out 'somename-dot-3gpp'.a32" +str
    shell-eval ;

: shred-s-3gpp
    rsbuff
    +"cd-<current-shell-workdir>-&&"
    s" find . -name '*.3gpp' -type f -printf '%p\0' | xargs -0 -n1 shred -uzn1 " +str
    shell-eval ;

: shred-v-3gpp
    rsbuff
    +"cd-<current-shell-workdir>-&&"
    s" find . -name '*.3gpp' -type f -printf '%p\0' | xargs -0 -n1 shred -uvzn1 " +str
    shell-eval ;

: type-files
    rsbuff
    +"cd-<current-shell-workdir>-&&"
    s" find . -name '*' -type f -printf '%p\0' | xargs -0 -n1 echo " +str
    shell-eval ;

: suspend
    s" systemctl suspend" system ;



















