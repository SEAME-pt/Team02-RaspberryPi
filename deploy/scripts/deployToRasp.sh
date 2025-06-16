#!/bin/bash

# Load environment variables from RaspberryPi/.env
source "$(dirname "$0")/../../.env"

architecture=$(uname -m)

check_ssh_connection() {
    local host=$1
    local user=$2
    echo "Checking connection to $host..."
    # Test SSH login
    if sshpass -p "$PI_PASSWORD" ssh "$user@$host" exit; then
        echo "Successful connection to $host..."
        return 0
    fi
    echo "NO connection to $host..."
    return 1
}

# Build docker image with appropriate platform flag
echo "Building docker image to build app..."
if [ "$architecture" = "arm64" ] || [ "$architecture" = "aarch64" ]; then
    echo "Building for ARM64 architecture..."
    docker build -f ./RaspberryPi/deploy/dockerfiles/DockerfileDeployRasp \
        --build-arg projectDir=/$PROJECT_DIR \
        -t final-app .
else
    echo "Building for non-ARM64 architecture with platform emulation..."
    docker buildx build -f ./RaspberryPi/deploy/dockerfiles/DockerfileDeployRasp \
        --platform linux/arm64  --load \
        --build-arg projectDir=/$PROJECT_DIR \
        -t final-app .
fi

echo "Remove tmpapp container if it exists"
docker rm -f tmpapp
echo "Create a tmp container to copy binary"
docker create --name tmpapp final-app
echo "Copy the binary from tmp container"
docker cp tmpapp:/home/$PROJECT_DIR/InstrumentClusterApp ./InstrumentClusterApp
docker cp tmpapp:/home/$PROJECT_DIR/MiddleWareApp ./MiddleWareApp

# if check_ssh_connection "$PI_IP_ADDRESS" "$PI_USERNAME"; then
    echo "Stopping services on Raspberry Pi..."
    sshpass -p "$PI_PASSWORD" ssh "$PI_USERNAME@$PI_IP_ADDRESS" "sudo systemctl stop middleware.service && pkill InstrumentClusterApp"

    echo "Sending binaries to Raspberry Pi over SCP..."
    sshpass -p "$PI_PASSWORD" scp InstrumentClusterApp MiddleWareApp "$PI_USERNAME@$PI_IP_ADDRESS:$PI_PATH_BIN"
    sshpass -p "$PI_PASSWORD" scp ./$PROJECT_DIR/ZenohConfig/InstrumentClusterConfig.json ./$PROJECT_DIR/ZenohConfig/MiddleWareConfig.json "$PI_USERNAME@$PI_IP_ADDRESS:$PI_PATH_ETC"

    echo "Sending font files to Raspberry Pi over SCP to $PI_PATH_FONTS"
    sshpass -p "$PI_PASSWORD" scp -r ./RaspberryPi/deploy/fonts "$PI_USERNAME@$PI_IP_ADDRESS:$PI_PATH_FONTS"
    echo "Restarting middleware service..."
    sshpass -p "$PI_PASSWORD" ssh "$PI_USERNAME@$PI_IP_ADDRESS" "sudo systemctl start middleware.service"
# fi
