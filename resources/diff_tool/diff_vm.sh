
./resources/diff_tool/bin/zaz_asm resources/diff_tool/champions/debug.s &&
./resources/diff_tool/bin/zaz_corewar -v 8 -d $1 -a resources/diff_tool/champions/debug.cor > ./resources/diff_tool/results/zaz.dump &&
#./resources/diff_tool/bin/zaz_corewar -v 8 -d $1 -a resources/diff_tool/champions/compiled/Stargate0_1.cor > ./resources/diff_tool/results/zaz.dump &&
./vm/corewar -dump $1 resources/diff_tool/champions/debug.cor > ./resources/diff_tool/results/me.dump &&
diff -a ./resources/diff_tool/results/zaz.dump ./resources/diff_tool/results/me.dump
