
### ✅ Option 1: Deploy on Raspberry Pi LCD





To deploy the interface on a Raspberry Pi with an attached LCD display:





1. Make sure you're in the **root directory** of the repository.


2. Update the `.env` file located in the root directory:


  - Change the `PI_IP_ADDRESS` to the IP address of your Raspberry Pi.


  - Update the `CREDENTIALS` with the username (`PI_USERNAME`) and password (`PI_PASSWORD`) for your Raspberry Pi.





2. Run the deployment script from the root repository:





  ```bash


  ./RaspberryPi/deploy/scripts/deployToRasp.sh


  ```





4. Restart the application to apply the changes. The executables will be placed in `PI_PATH_BIN` in your Raspberry Pi, make sure to change that if necessary. 





### ✅ Option 2: Simulate on a Local Machine





For testing purposes, you can simulate the application on your local machine:





1. Install the required dependencies as listed in the `requirements.txt` file.


2. Run the application locally using:





  ```bash


  ./RaspberryPi/deploy/deployLocal/deployLocal.sh


  ```





3. Ensure the CAN bus data is being simulated or fed into the application for testing.
