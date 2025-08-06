<br />


  <h1 align="center">Instrument Cluster</h1>

    A real-time vehicle speed and data display.


    <br />


    ![Cluster GIF](https://raw.githubusercontent.com/SEAME-pt/Team02-RaspberryPi/readme/assets/cluster.gif)


    ·


    <a href="https://github.com/SEAME-pt/Team02-Cluster/issues/new?labels=bug&template=bug-report.yml">Report Bug</a>


    ·


    <a href="https://github.com/SEAME-pt/Team02-Cluster/issues/new?labels=enhancement&template=feature-request.yml">Request Feature</a>





## Table of Contents


1. [About The Project](#about-the-project)


   - [Built With](#built-with)


2. [Usage](#usage)


4. [Contributing](#contributing)


5. [License](#license)


6. [Contact](#contact)


7. [Acknowledgments](#acknowledgments)




## About The Project






The **Instrument Cluster** is designed to provide real-time speed data from a PiRacer car on a graphical interface (GUI). The application is split across two devices: the **Jetson Nano** handles all the processing tasks, while the **Raspberry Pi** is used solely for rendering the Qt-based display. Both devices receive speed data simultaneously from the sensor via the Controller Area Network (CAN) protocol. The Jetson Nano processes the data for any necessary computations (such as filtering, calculations, etc.), and the Raspberry Pi renders the GUI with the processed speed data.




This architecture allows for improved performance by offloading processing to the Jetson Nano while simplifying the display connection on the Raspberry Pi. Check it out the pheripherals Readme to better understand about the project architecture.






This project offers hands-on experience with software engineering, embedded systems, and automotive communication protocols, with a focus on performance optimization through a modular system design. 




### Project Goals:


- **Design and implement** a Qt-based graphical user interface (GUI) for displaying speed data on the Raspberry Pi.


- **Use the Jetson Nano** for handling all processing tasks related to speed data and mathematical calculations.


- **Integrate** a Raspberry Pi with an Arduino-based speed sensor using the CAN protocol.


- **Display real-time speed** data on the instrument cluster.


- **Test the application** in realistic driving scenarios.


- **Document** the entire project, including system architecture, software design, and implementation details.




**BONUS:** Display battery level on the instrument cluster.








### Architecture Overview








- **Jetson Nano:** Handles all the computational tasks and mathematical processing for the instrument cluster. It processes speed sensor data and other inputs before sending them to the Raspberry Pi.


- **Raspberry Pi:** Dedicated to rendering the GUI with Qt, displaying the processed data received from the Jetson Nano over CAN bus.




---










### Built With




This section lists the major frameworks, libraries, and tools used in this project.





#### Technologies and Frameworks





- [![Qt](https://img.shields.io/badge/Qt-41CD52?style=for-the-badge&logo=qt&logoColor=white)](https://www.qt.io/)


- [![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://www.python.org/)


- [![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)





#### Communication Protocols





- [![SPI](https://img.shields.io/badge/SPI-Protocol-000000?style=for-the-badge)](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)


- [![I2C](https://img.shields.io/badge/I2C-Protocol-000000?style=for-the-badge)](https://en.wikipedia.org/wiki/I%2F2C)


- [![CAN Bus](https://img.shields.io/badge/CAN%20Bus-Protocol-000000?style=for-the-badge)](https://www.kvaser.com/can/)





🗂️ [Check here](https://github.com/SEAME-pt/Team02-RaspberryPi/blob/80-task-object-detection-in-cluster/MiddleWare/src/can-id-reference-table.md) the CAN ID Reference Table





#### Hardware





- [![Jetson Nano](https://img.shields.io/badge/Jetson%20Nano-Developer%20Kit-76B900?style=for-the-badge&logo=nvidia&logoColor=white)](https://developer.nvidia.com/embedded/jetson-nano)


- [![Raspberry Pi](https://img.shields.io/badge/Raspberry%20Pi-C51A4A?style=for-the-badge&logo=raspberry-pi&logoColor=white)](https://www.raspberrypi.org/)


- [![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)





---





### Usage


Once the application is up and running, the instrument cluster will display `real-time speed data` and the `vehicle's battery status` on an LCD screen. The data is continuously updated as it is received **via the CAN bus**.





This project can be deployed and tested in two main environments:





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


<!-- 


A demonstration of the running application can be seen in the GIF below:





[DEMONSTRATION GIF WILL BE ATTACHED] -->


---





## Testing





We use **LCOV** for test coverage analysis to ensure the reliability and quality of the codebase. Follow the steps below to run the tests:





1. Navigate to the `RaspberryPi/tests` directory:


  ```bash


  cd RaspberryPi/tests


  ```





2. After the tests are executed, a coverage report will be generated. Run the test script:


  ```bash


  ./test.sh


  ```





Make sure all tests pass and the coverage meets the project's standards before submitting any changes. 





## The Team 🤝


> Together, we've collaborated to bring this project to life, combining our knowledge, skills, and experience every step of the way. It has been a great journey of learning and growing as a team.





  - <a href="https://github.com/Rui-Pedro-Pires">Rui Pires</a>


  - <a href="https://github.com/ziliolu">Luiza Zilio</a>


  - <a href="https://github.com/luis-ffe">Luis Filipe Carvalho</a>


  - <a href="https://github.com/mjorgecruz">Jorge Cruz</a>





## Contributing





Contributions are what make the open source community such an amazing place to learn, inspire, and create. **Any contributions you make are greatly appreciated.**





If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement". Don't forget to give the project a star! Thanks again!





1. Fork the repository


2. Create a new branch for your feature (`git checkout -b feature-name`)


3. Commit your changes (`git commit -am 'Add feature'`)


4. Push to the branch (`git push origin feature-name`)


5. Open a pull request





---





## License





Distributed under the MIT License. See `LICENSE` for more information.





---





## Acknowledgments





- **Qt Framework:** [Qt](https://www.qt.io/) – A cross-platform framework for GUI applications.


- **Jetson Nano:** [NVIDIA Jetson Nano](https://developer.nvidia.com/embedded/jetson-nano) – A powerful single-board computer for processing tasks.


- **Raspberry Pi Foundation:** [Raspberry Pi](https://www.raspberrypi.org/) – The small, powerful computer that powers the display side of the project.


- **Arduino:** [Arduino](https://www.arduino.cc/) – A versatile open-source electronics platform used for sensor data collection.


- **CAN Bus Protocol:** [CAN Protocol](https://www.kvaser.com/can/) – The communication protocol used to connect different ECUs in the vehicle.