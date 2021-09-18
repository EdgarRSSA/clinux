#!/usr/bin/env bash
#
#    LOG-SCRIPT
#
__dirlog_base="/tmp";
__dirlog="${__dirlog_base}/clinux";
__log_out="${__dirlog}/out.log";
__log_err="${__dirlog}/err.log";

# CLEAR LOG DIR
if [[ $1 == "clear" ]]; then

    if [[ ! -d ${__dirlog} ]]; then
        mkdir ${__dirlog};
        exit 0;
    else
        rm -R ${__dirlog};
        mkdir ${__dirlog};
        exit 0;
    fi
fi

# LOG CONSOLE COLORS
COS='\e[38;5;120m'; # label color
COW='\e[38;5;227m'; # warn color
COE='\e[38;5;209m'; # error color
COR='\e[0m'; # reset color

#
LOGCMD="${COS}[$( date +%T:%N )]${COW} $2 ${COR}";
LOGSIMPLE="[$( date +%T:%N )] $2";

if [[ $1 == "run" ]]; then

    UUID="$(cat /proc/sys/kernel/random/uuid)";
    __log_out_t="${__dirlog}/out-${UUID}.log";
    __log_err_t="${__dirlog}/err-${UUID}.log";

    {
        $2 1> $__log_out_t 2> $__log_err_t;
    } &
    wait -n %1 ;
    ecode=$?;

    if [[ ${ecode} != 0 ]];then
        # LOG TO ERROR.LOG
        echo -e ${LOGSIMPLE} >> $__log_err;
        cat $__log_out_t >> $__log_err;
        cat $__log_err_t >> $__log_err;
        echo -e "EXIT:${ecode}" >> $__log_err;

        # LOG TO OUT.LOG
        echo -e ${LOGSIMPLE} >> $__log_out;
        cat $__log_out_t >> $__log_out;
        cat $__log_err_t >> $__log_out;
        echo -e "EXIT:${ecode}" >> $__log_out;

        # CONSOLE ERROR
        echo -e ${LOGCMD} && echo -e "${COE}$(cat $__log_out_t)${COR}" && echo -e "${COE}$(cat $__log_err_t)${COR}"  && echo -e "EXIT:${ecode}";
        exit ${ecode};
    fi
    if [[ ${ecode} == 0 ]];then
        # LOG
        echo -e ${LOGSIMPLE} >> $__log_out;
        cat $__log_out_t >> $__log_out;
        echo -e "EXIT:${ecode}" >> $__log_out;
        # CONSOLE LOG
        echo -e ${LOGCMD} && cat $__log_out_t;
        exit 0;
    fi
fi


if [[ $1 == "runq" ]]; then

    UUID="$(cat /proc/sys/kernel/random/uuid)";
    __log_out_t="${__dirlog}/out-${UUID}.log";
    __log_err_t="${__dirlog}/err-${UUID}.log";

    {
        $2 1> $__log_out_t 2> $__log_err_t;
    } &
    wait -n %1 ;
    ecode=$?;

    if [[ ${ecode} != 0 ]];then
        # LOG TO ERROR.LOG
        echo -e ${LOGSIMPLE} >> $__log_err;
        cat $__log_out_t >> $__log_err;
        cat $__log_err_t >> $__log_err;
        echo -e "EXIT:${ecode}" >> $__log_err;

        # LOG TO OUT.LOG
        echo -e ${LOGSIMPLE} >> $__log_out;
        cat $__log_out_t >> $__log_out;
        cat $__log_err_t >> $__log_out;
        echo -e "EXIT:${ecode}" >> $__log_out;

        # CONSOLE ERROR
        echo -e ${LOGCMD} && echo -e "EXIT:${ecode}";
        exit ${ecode};
    fi
    if [[ ${ecode} == 0 ]];then
        # LOG
        echo -e ${LOGSIMPLE} >> $__log_out;
        cat $__log_out_t >> $__log_out;
        echo -e "EXIT:${ecode}" >> $__log_out;
        # CONSOLE LOG
        echo -e ${LOGCMD};
        exit 0;
    fi
fi



if [[ $1 == "log" ]]; then
    echo -e ${LOGCMD};
    echo -e ${LOGSIMPLE} >> "${__log_out}";
fi
