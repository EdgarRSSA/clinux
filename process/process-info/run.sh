#!/usr/bin/env bash
LOG="./../../logger.sh";
${LOG} "clear";

# Ejecutar Archivo de compilacion
# Prueba para escribir desde multiples procesos a un archivo.
# Rutas:

outbuild="./out";
runfile="${outbuild}/run";
mainfile="./basic-info.c";

if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi

$LOG "log" "PWD:${PWD} MAIN:${mainfile} RUN:${runfile}";

#
# Compilacion:
#

$LOG "run" "gcc -o ${runfile} ${mainfile}" || exit $?;

#
# Process info
#
$LOG "log" "PID_MAX: $( cat /proc/sys/kernel/pid_max )";

#
# RUN
#
$LOG "run" "${runfile} argument1 argument2";
