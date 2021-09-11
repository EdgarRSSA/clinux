#!/usr/bin/env bash
LOG="./../../logger.sh";
${LOG} "clear";

# Ejecutar Archivo de compilacion
# Prueba de  procesos para intentar abrir un archivo unico

#
# Rutas:
#

outbuild="./out";
runfile="${outbuild}/run";
mainfile="./exc-open.c";  # bad-exc-open.c <--- Probar errores.
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

$LOG "log" "${runfile} ${openfile} (5)";
( ${runfile} ${openfile} ) & \
( ${runfile} ${openfile} ) & \
( ${runfile} ${openfile} ) & \
( ${runfile} ${openfile} ) &\
( ${runfile} ${openfile} ) &
wait
