# Ejecutar Archivo de compilacion
# Prueba para escribir desde multiples procesos a un archivo.
# Rutas:

outbuild="./out";
runfile="${outbuild}/runwrite";
mainfile="./write-offset-block.c";
openfile="./text.example.txt";
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

echo -e "[$( date +%T )] ${runfile} ${openfile} #(0-14) (15)";
( ${runfile} ${openfile} 'AB823:' 0 ) & \
( ${runfile} ${openfile} 'GH763:' 1 ) & \
( ${runfile} ${openfile} 'YU907:' 2 ) & \
( ${runfile} ${openfile} 'JK657:' 3 ) & \
( ${runfile} ${openfile} 'FF657:' 4 ) & \
( ${runfile} ${openfile} 'TR657:' 5 ) & \
( ${runfile} ${openfile} 'LÑ333:' 6 ) & \
( ${runfile} ${openfile} 'OE111:' 7 ) & \
( ${runfile} ${openfile} 'II763:' 8 ) & \
( ${runfile} ${openfile} 'XX543:' 9 ) & \
( ${runfile} ${openfile} 'VB003:' 10 ) & \
( ${runfile} ${openfile} 'DW878:' 11 ) & \
( ${runfile} ${openfile} 'ÑA000:' 12 ) & \
( ${runfile} ${openfile} 'RR122:' 13 ) & \
( ${runfile} ${openfile} 'HM547:' 14 ) &
