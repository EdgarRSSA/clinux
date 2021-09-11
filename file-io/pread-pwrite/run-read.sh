#!/usr/bin/env bash
LOG="./../../logger.sh";
${LOG} "clear";

# Ejecutar Archivo de compilacion
# Prueba para escribir desde multiples procesos a un archivo.

#
# Rutas:
#
outbuild="./out";
runfile="${outbuild}/runread";
prerun="./run-write.sh";
mainfile="./read-offset-block.c";
openfile="./text.example.txt";
if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

$LOG "log" "PWD:${PWD} MAIN:${mainfile} RUN:${runfile} FILE:${openfile}";

#
# Revisar archivo 'openfile'
#

if [[ ! -e ${openfile} ]]; then
    $LOG "log" "Run first 'bash ${prerun}'";
    exit 1;
fi

#
# Compilacion:
#

$LOG "run" "gcc -o ${runfile} ${mainfile}" || exit $?;

#
# Ejecucion:
#

$LOG "log" "${runfile} ${openfile} (15)";
( ${runfile} ${openfile} 0 ) & \
( ${runfile} ${openfile} 1 ) & \
( ${runfile} ${openfile} 2 ) & \
( ${runfile} ${openfile} 3 ) & \
( ${runfile} ${openfile} 4 ) & \
( ${runfile} ${openfile} 5 ) & \
( ${runfile} ${openfile} 6 ) & \
( ${runfile} ${openfile} 7 ) & \
( ${runfile} ${openfile} 8 ) & \
( ${runfile} ${openfile} 9 ) & \
( ${runfile} ${openfile} 10 ) & \
( ${runfile} ${openfile} 11 ) & \
( ${runfile} ${openfile} 12 ) & \
( ${runfile} ${openfile} 13 ) & \
( ${runfile} ${openfile} 14 ) &
wait
