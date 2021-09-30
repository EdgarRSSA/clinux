#!/usr/bin/env bash
LOG="./../../logger.sh";
${LOG} "clear";

# Ejecutar Archivo de compilacion
# Prueba para escribir desde multiples procesos a un archivo.
# Rutas:

outbuild="./out";
runfile="${outbuild}/run";
mainfile="./simple-unsafe.c";

if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

$LOG "log" "PWD:${PWD} MAIN:${mainfile} RUN:${runfile}";

#
# Compilacion:
#

$LOG "run" "gcc -ggdb -o ${runfile} ${mainfile}" || exit $?;


#
# RUN
#
$LOG "log" "Use -> ${runfile}";
