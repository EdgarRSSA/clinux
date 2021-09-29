#!/usr/bin/env bash
LOG="./../../logger.sh";
${LOG} "clear";

# Compilar y Ejecutar

outbuild="./out";
runfile="${outbuild}/run";
mainfile="./cwd.c";

if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

$LOG "log" "PWD:${PWD} MAIN:${mainfile} RUN:${runfile}";

#
# Compilacion:
#

$LOG "run" "gcc -D DEBUG -o ${runfile} ${mainfile}" || exit $?;

#
# RUN
#
$LOG "run" "${runfile}" "export CWD_DIR=${HOME}" "unset CWD_DIR";
