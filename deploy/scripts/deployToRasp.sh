#!/bin/bash

projectDir=RaspberryPi
piUserName=team02
piIpAddressLocal=10.21.221.64
piIpAddressRemote=10.21.221.64
piPathBin=/opt/vehicle/bin
piPathEtc=/opt/vehicle/etc/zenoh
piPass=seameteam2
architecture=$(uname -m)

check_ssh_connection() {
    local host=$1
    local user=$2
    echo "Checking connection to $host..."
    # Test SSH login
    if sshpass -p "$piPass" ssh "$user@$host" exit; then
        return 0
    fi
    return 1
}

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
# docker cp tmpapp:/home/$projectDir/InstrumentClusterApp ./InstrumentClusterApp
docker cp tmpapp:/home/$projectDir/HandClusterB ./HandClusterB
docker cp tmpapp:/home/$projectDir/MiddleWareApp ./MiddleWareApp

# if check_ssh_connection "$piIpAddressLocal" "$piUserName"; then
#     echo "Stopping services on local Raspberry Pi..."
#     sshpass -p "$piPass" ssh "$piUserName"@"$piIpAddressLocal" "sudo systemctl stop middleware.service && pkill InstrumentClus"
    
#     echo "Send binary to local rasp over scp"
#     sshpass -p "$piPass" scp InstrumentClusterApp MiddleWareApp "$piUserName"@"$piIpAddressLocal":"$piPathBin"
#     sshpass -p "$piPass" scp ./$projectDir/ZenohConfig/InstrumentClusterConfig.json ./$projectDir/ZenohConfig/MiddleWareConfig.json "$piUserName"@"$piIpAddressLocal":"$piPathEtc"
    
#     echo "Restarting services on local Raspberry Pi..."
#     sshpass -p "$piPass" ssh "$piUserName"@"$piIpAddressLocal" "sudo systemctl start middleware.service"

#     echo "InstrumentCluster will restart on next login"
# else
#     echo "ERROR: Cannot connect to local Raspberry Pi at $piIpAddressLocal"
# fi

if check_ssh_connection "$piIpAddressRemote" "$piUserName"; then
    echo "Stopping services on local Raspberry Pi..."
    sshpass -p "$piPass" ssh "$piUserName"@"$piIpAddressLocal" "sudo systemctl stop middleware.service && pkill InstrumentClus"
    
    echo "Stopping service on remote Raspberry Pi..."
    sshpass -p "$piPass" ssh "$piUserName"@"$piIpAddressRemote" "pkill HandCluster"
    
    
    sshpass -p "$piPass" ssh "$piUserName"@"$piIpAddressRemote" \
    "echo '$piPass' | sudo -S mkdir -p $piPathBin $piPathEtc && sudo chown -R $piUserName:$piUserName /opt/vehicle"

    echo "Send binary to remote rasp over scp"
    sshpass -p "$piPass" scp HandClusterB MiddleWareApp "$piUserName"@"$piIpAddressRemote":"$piPathBin"

    # echo "Restarting services on local Raspberry Pi..."
    # sshpass -p "$piPass" ssh "$piUserName"@"$piIpAddressLocal" "sudo systemctl start middleware.service"


fi
