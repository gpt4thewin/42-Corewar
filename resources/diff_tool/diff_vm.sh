
./resources/diff_tool/bin/zaz_asm resources/diff_tool/champions/debug.s
./resources/diff_tool/bin/zaz_corewar -a -v 4 -d $1 -a resources/diff_tool/champions/debug.cor resources/diff_tool/champions/debug.cor > ./resources/diff_tool/results/zaz.dump
./vm/corewar -dump $1 -v 4 resources/diff_tool/champions/debug.cor resources/diff_tool/champions/debug.cor > ./resources/diff_tool/results/me.dump
diff -a ./resources/diff_tool/results/zaz.dump ./resources/diff_tool/results/me.dump
