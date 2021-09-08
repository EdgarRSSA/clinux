# Ejecutar Archivo de compilacion
# Prueba para escribir desde multiples procesos a un archivo.
# Rutas:

outbuild="./out";
runfile="${outbuild}/run";
mainfile="./writer.c";  # bad-exc-open.c <--- Probar errores.
openfile="./writer.example.txt";
if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi
echo -e "[$( date +%T )] MAIN:${mainfile} RUN:${runfile} FILE:${openfile}";

#
# Remover archivo a abrir:
#

if [[ -e ${openfile} ]]; then
    ( echo -e "[$( date +%T )] rm ${openfile}" && rm ${openfile} ) || exit 1;
fi

#
# Compilacion:
#

( echo -e "[$( date +%T )] gcc -o ${runfile} ${mainfile}" && gcc -o "${runfile}" "${mainfile}" ) || exit 1;

#
# Ejecucion:
#

echo -e "[$( date +%T )] ${runfile} ${openfile} (5)";
( ${runfile} ${openfile} 'AB823: ' ) & \
( ${runfile} ${openfile} 'GH763: ' ) & \
( ${runfile} ${openfile} 'YU907: ' ) & \
( ${runfile} ${openfile} 'JK657: ' ) & \
( ${runfile} ${openfile} 'FF657: ' ) & \
( ${runfile} ${openfile} 'TR657: ' ) & \
( ${runfile} ${openfile} 'LÑ333: ' ) & \
( ${runfile} ${openfile} 'OE111: ' ) & \
( ${runfile} ${openfile} 'II763: ' ) & \
( ${runfile} ${openfile} 'XX543: ' ) & \
( ${runfile} ${openfile} 'VB003: ' ) & \
( ${runfile} ${openfile} 'DW878: ' ) & \
( ${runfile} ${openfile} 'ÑA000: ' ) & \
( ${runfile} ${openfile} 'RR122: ' ) & \
( ${runfile} ${openfile} 'HM547: ' ) &
