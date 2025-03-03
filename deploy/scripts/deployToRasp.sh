#!/bin/bash

projectDir=RaspberryPi
piUserName=team02
piIpAddressLocal=10.21.221.64
piIpAddressRemote=10.21.221.19
piPath=/home/team02
piPass=seameteam2

architecture=$(uname -m)
echo "Detected architecture: $architecture"

# Build docker image with appropriate platform flag
echo "Building docker image to build app..."
if [ "$architecture" = "arm64" ] || [ "$architecture" = "aarch64" ]; then
    echo "Building for ARM64 architecture..."
    docker build -f ./RaspberryPi/deploy/dockerfiles/DockerfileDeployRasp \
        --build-arg projectDir=/$projectDir \
        -t final-app .
else
    echo "Building for non-ARM64 architecture with platform emulation..."
    docker buildx build -f ./RaspberryPi/deploy/dockerfiles/DockerfileDeployRasp \
        --platform linux/arm64  --load \
        --build-arg projectDir=/$projectDir \
        -t final-app .
fi

echo "Remove tmpapp container if it is exist"
docker rm -f tmpapp
echo "Create a tmp container to copy binary"
docker create --name tmpapp final-app
echo "Copy the binary from tmp container"
docker cp tmpapp:/home/$projectDir/InstrumentClusterApp ./InstrumentClusterApp
docker cp tmpapp:/home/$projectDir/HandClusterApp ./HandClusterApp
docker cp tmpapp:/home/$projectDir/MiddleWareApp ./MiddleWareApp
echo "Send binary to local rasp over scp"
sshpass -p "$piPass" scp InstrumentClusterApp MiddleWareApp "$piUserName"@"$piIpAddressLocal":"$piPath"
echo "Send binary to remote rasp over scp"
sshpass -p "$piPass" scp HandClusterApp "$piUserName"@"$piIpAddressRemote":"$piPath"
