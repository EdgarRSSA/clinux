#!/usr/bin/env bash
LOG="./../../logger.sh";
${LOG} "clear";

#
# Ejecutar Archivo de compilacion
# Consulta y cambio de banderas (flags) de archivos usando FCNTL
#

# Rutas:

outbuild="./out";
runfile="${outbuild}/run";
mainfile="./check.c";
openfile="./check.example.txt";
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

$LOG "run" "${runfile} ${openfile}" || exit $?;
