#!/usr/bin/env bash
LOG="./../logger.sh";
${LOG} "clear";

# Compilar y Ejecutar

outbuild="./out";
runfile="${outbuild}/run";
mainfile="./read.c";
addfiles="./__read.c";

if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

$LOG "log" "PWD:${PWD} MAIN:${mainfile} ADDS:${addfiles} RUN:${runfile}";

#
# Compilacion:
#

$LOG "run" "gcc -D DEBUG -o ${runfile} ${mainfile} ${addfiles}" || exit $?;

#
# RUN
#
$LOG "run" "${runfile} .";
