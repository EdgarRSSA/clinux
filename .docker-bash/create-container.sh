CONTAINER="clinux1";
IMAGE="clinux:buster";
SSHPORTPUBLISH="2222:22";

docker run -itd --name ${CONTAINER} -p ${SSHPORTPUBLISH} ${IMAGE} /bin/bash
