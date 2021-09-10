# Ejecutar Archivo de compilacion
# Prueba para escribir desde multiples procesos a un archivo.
# Rutas:

outbuild="./out";
runfile="${outbuild}/runread";
prerun="./run-write.sh";
mainfile="./read-offset-block.c";
openfile="./text.example.txt";
if [[ ! -d ${outbuild} ]]; then
    mkdir ${outbuild}
fi
echo -e "[$( date +%T )] MAIN:${mainfile} RUN:${runfile} FILE:${openfile}";

#
# Correr primero 'prerun'
#

if [[ ! -e ${openfile} ]]; then
    ( echo -e "[$( date +%T )] bash ${prerun}" && bash ${prerun} && sleep 2 && echo "" ) || exit 1;

fi

#
# Compilacion:
#

( echo -e "[$( date +%T )] gcc -o ${runfile} ${mainfile}" && gcc -o "${runfile}" "${mainfile}" ) || exit 1;

#
# Ejecucion:
#

echo -e "[$( date +%T )] ${runfile} ${openfile} (15)";
( ${runfile} ${openfile} 0 ) & \
( ${runfile} ${openfile} 1 ) & \
( ${runfile} ${openfile} 2 ) & \
( ${runfile} ${openfile} 3 ) & \
( ${runfile} ${openfile} 4 ) & \
( ${runfile} ${openfile} 5 ) & \
( ${runfile} ${openfile} 6 ) & \
( ${runfile} ${openfile} 7 ) & \
( ${runfile} ${openfile} 8 ) & \
( ${runfile} ${openfile} 9 ) & \
( ${runfile} ${openfile} 10 ) & \
( ${runfile} ${openfile} 11 ) & \
( ${runfile} ${openfile} 12 ) & \
( ${runfile} ${openfile} 13 ) & \
( ${runfile} ${openfile} 14 ) &
