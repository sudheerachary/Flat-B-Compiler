./bcc $1 2> dump.ll
llvm-as dump.ll -o dump.bc
lli dump.bc
rm dump*
