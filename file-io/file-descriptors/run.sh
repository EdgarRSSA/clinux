# Ejecutar Archivo de compilacion
# Duplicar FD de archivos
# Rutas:

outbuild="./out";
runfile="${outbuild}/run";
mainfile="./duplicate-3.c"; // SELECT THE DUCPLICATE-#.C TYPE
openfile="./alfa.example.txt";
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

echo -e "[$( date +%T )] ${runfile} ${openfile}";
( ${runfile} ${openfile} ) & \
( ${runfile} ${openfile} ) & \
( ${runfile} ${openfile} ) & \
( ${runfile} ${openfile} ) &
