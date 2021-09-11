#!/usr/bin/env bash
LOG="./../../logger.sh";
${LOG} "clear";

#
# Ejecutar Archivo de compilacion
# Prueba para escribir desde multiples procesos a un archivo.
#
# Rutas:

outbuild="./out";
runfile="${outbuild}/run";
mainfile="./writer.c";  # bad-exc-open.c <--- Probar errores.
openfile="./writer.example.txt";
if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

$LOG "log" "PWD:${PWD} MAIN:${mainfile} RUN:${runfile} FILE:${openfile}";

#
# Remover archivo a abrir:
#

if [[ -e ${openfile} ]]; then
    $LOG "run" "rm ${openfile}" || exit $?;
fi

#
# Compilacion:
#

$LOG "runq" "gcc -o ${runfile} ${mainfile}" || exit $?;

#
# Ejecucion:
#

$LOG "log" "${runfile} ${openfile} (15)";
( ${runfile} ${openfile} 'AB823: ' ) & \
( ${runfile} ${openfile} 'GH763: ' ) & \
( ${runfile} ${openfile} 'YU907: ' ) & \
( ${runfile} ${openfile} 'JK657: ' ) & \
( ${runfile} ${openfile} 'FF657: ' ) & \
( ${runfile} ${openfile} 'TR657: ' ) & \
( ${runfile} ${openfile} 'LÑ333: ' ) & \
( ${runfile} ${openfile} 'OE111: ' ) & \
( ${runfile} ${openfile} 'II763: ' ) & \
( ${runfile} ${openfile} 'XX543: ' ) & \
( ${runfile} ${openfile} 'VB003: ' ) & \
( ${runfile} ${openfile} 'DW878: ' ) & \
( ${runfile} ${openfile} 'ÑA000: ' ) & \
( ${runfile} ${openfile} 'RR122: ' ) & \
( ${runfile} ${openfile} 'HM547: ' ) &
wait
