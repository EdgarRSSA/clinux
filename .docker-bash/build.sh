IMAGE="clinux:buster";
IMAGE_TARGET="dev";

docker build --rm --tag "${IMAGE}" --target ${IMAGE_TARGET} .
