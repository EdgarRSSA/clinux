#!/usr/bin/env bash
LOG="./../../logger.sh";
${LOG} "clear";

#
# Ejecutar Archivo de compilacion
# Duplicar FD de archivos
#

# Rutas:

outbuild="./out";
runfile="${outbuild}/run";
mainfile="./duplicate-2.c"; # SELECT THE DUCPLICATE-#.C TYPE
openfile="./alfa.example.txt";
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

$LOG "log" "${runfile} ${openfile} (4)";
( ${runfile} ${openfile} ) & \
( ${runfile} ${openfile} ) & \
( ${runfile} ${openfile} ) & \
( ${runfile} ${openfile} ) &
wait
