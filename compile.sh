#!/usr/bin/env bash
LOG="./logger.sh";
${LOG} "clear";

# Ejecutar Archivo de compilacion
# Prueba para escribir desde multiples procesos a un archivo.
# Rutas:

outbuild="./out";
runfile="${outbuild}/run";
mainfile="$1";

if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

$LOG "log" "PWD:${PWD} MAIN:${mainfile} RUN:${runfile}";

#
# Compilacion:
#

$LOG "run" "gcc -o ${runfile} ${mainfile}" || exit $?;

#
# RUN
#
$LOG "run" "${runfile} $2";
