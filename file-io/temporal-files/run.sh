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
mainfile="./tmpfiles.c"; ## CHANGE TO './mkstemp-file.c'

if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

$LOG "log" "PWD:${PWD} MAIN:${mainfile} RUN:${runfile} FILE:temporal";

#
# Compilacion:
#

$LOG "runq" "gcc -o ${runfile} ${mainfile}" || exit $?;

#
# Ejecucion:
#

$LOG "log" "${runfile}";

{
    ${runfile} &
    ( sleep 1 && ls -lA ./ ) &
}
wait
