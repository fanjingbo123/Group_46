- [Telecom](#telecom)
  - [Introduction](#introduction)
  - [Features](#features)
  - [System Architecture](#system-architecture)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
  - [Deployment](#deployment)
    - [Setting up the Arduino Mega 2560](#setting-up-the-arduino-mega-2560)
    - [Setting up the ESP32-CAM](#setting-up-the-esp32-cam)
    - [Operating the Vehicle](#operating-the-vehicle)
  - [Video tranformation](#video-tranformation)
- [IoT](#iot)
  - [Introduction](#introduction-1)
  - [Features](#features-1)
  - [Getting Started](#getting-started-1)
    - [Prerequisites](#prerequisites-1)
  - [Usage](#usage)
- [E-commerce](#e-commerce)
  - [Instructions for Use](#instructions-for-use)
    - [Environment](#environment)
    - [Setup](#setup)
    - [Additional Configuration](#additional-configuration)
  - [File Structure](#file-structure)
    - [Java Project](#java-project)
    - [webapp](#webapp)
  - [Code Explanation](#code-explanation)


## Telecom

### Introduction

The Telecom subsystem of the Group_46 project establishes a sophisticated communication layer for a smart, autonomous vehicle navigating through a maze. This subsystem handles live video streaming over Wi-Fi, enabling real-time monitoring of the vehicle's maneuvers, and manages the vehicle's movements using ultrasonic sensors.

### Features

- Real-Time Streaming Protocol (RTSP) server for live video streaming
- Wi-Fi communication for remote monitoring and control
- Autonomous navigation using ultrasonic sensors
- Dual-part control system utilizing both Arduino Mega 2560 and ESP32-CAM

### System Architecture

The vehicle's control logic is split between two main components: the Arduino Mega 2560 and the ESP32-CAM.

- **Arduino Mega 2560**: Responsible for the vehicle's movement logic, it processes input from three ultrasonic sensors to navigate through the maze and controls the motors to steer the vehicle.
- **ESP32-CAM**: Manages the Wi-Fi connectivity and video streaming, it broadcasts the live feed from the vehicle and communicates over the channels set up for data transmission.

### Getting Started

These instructions will guide you through setting up the project on your local machine for development, testing, and deployment purposes.

#### Prerequisites

- Arduino IDE or compatible software
- ESP32-CAM module and Arduino Mega 2560 board
- Access to a Wi-Fi network
- Python environment (for running the RTSP server script)

### Deployment

#### Setting up the Arduino Mega 2560

1. Open the `CarMovingFinal.ino` script with the Arduino IDE.
2. Upload the script to your Arduino Mega 2560 board.
3. Ensure the ultrasonic sensors and motors are connected as per the script's documentation.
4. Power up the Arduino board; the vehicle should now be capable of autonomous movement within the maze.

#### Setting up the ESP32-CAM

1. Configure the ESP32-CAM module with the provided scripts to establish the Wi-Fi connection and set up the video stream.
2. Verify the Wi-Fi name, connection method, and data transmission channel as per the script's output.
3. Ensure the camera is operational and streaming data over the configured Wi-Fi network.

#### Operating the Vehicle

Once both systems are up and running:

1. Place the vehicle at the maze's entrance.
2. Power up the system; the camera will initiate automatically, and the vehicle will start navigating through the maze.
3. Monitor the vehicle's progress through the live video feed streaming over Wi-Fi.


### Video tranformation
`rtsp_video_server_wlan_1.py`

- **Functionality**: This script sets up an RTSP server to stream video over WLAN, allowing for real-time monitoring of the vehicle's environment.
- **How it works**: 
  1. Configures the network interface for video streaming.
  2. Establishes an RTSP server to handle the video stream.
  3. Manages the capture and transmission of video frames, utilizing callback functions for different stages of the RTSP session.
- **Usage**: 
  ```
  python rtsp_video_server_wlan_1.py
  ```



## IoT

### Introduction

The IoT subsystem of the Group_46 project is dedicated to real-time object detection and data handling for a smart, autonomous vehicle capable of navigating through a maze. This subsystem processes video streams, performs object detection, trains detection models, and handles the transfer of image data, contributing to the vehicle's decision-making process.

### Features

- Real-time object detection with YOLO (You Only Look Once)
- GUI for result display and comparison
- Model training capabilities
- Data transfer and storage functionalities

### Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

#### Prerequisites

Before you begin, ensure you have met the following requirements:

- Python 3.8 or later
- Libraries and dependencies as listed in `requirements.txt`
- YOLOv3 or other compatible models
- Adequate hardware (GPU recommended) for running deep learning models

### Usage

`real_time_detect.py`

- **Functionality**: This script uses the YOLO algorithm for real-time object detection in video frames.

- **Usage**: 

  ```
  python real_time_detect.py
  ```

- **Details**: The script initializes the YOLO model, accesses a video feed, processes the video frames to detect objects, and displays the video stream with bounding boxes and labels around the detected objects.

`result_gui.py`

- **Functionality**: Provides a GUI for comparing and viewing images before and after object detection.

- **Usage**: 

  ```
  python result_gui.py
  ```

- **Details**: The script loads images from specified directories and displays them side-by-side in a simple GUI, allowing for easy comparison. Users can navigate through the images using the provided buttons.

`train_model.py`

- **Functionality**: Used for training the YOLO model with a specific dataset.

- **Usage**: 

  ```
  python train_model.py
  ```

- **Details**: The script loads a pre-trained YOLO model and trains it on a specified dataset to improve its accuracy. The trained model is saved for future use in object detection tasks.

`transfer_data.py`

- **Functionality**: Receive video streams in RTSP format from Telecom group cameras, and insert the detected paths of treasure images and exploration times into the database.

- **Usage**: 

  ```
  python transfer_data.py
  ```

- **Details**: The script captures video frames, performs object detection on each, saves annotated frames to a directory, and inserts relevant records into a database.


## E-commerce

### Instructions for Use

#### Environment

- **Operating System**: Windows 10
- **JDK**: 17.0.8.1
- **Server**: Tomcat v8.5
- **IDE**: Eclipse JEE 2023-06
- **Database**: MySQL 8.0.33 (winx64)
- **DB Management Tool**: MySQL Workbench 8.0 CE

#### Setup

Before running the application, please follow the steps below:

1. Ensure the `javawebdb` database table has been imported into your MySQL instance.
2. Update the database connection code within the project to use your machine's MySQL username and password. Specifically, changes need to be made in `RecordDao.java` and `DBConnect.java`.
3. Verify that the MySQL service is running.
4. Start the Tomcat server.
5. In Eclipse, right-click on the `testWeb1` project and select "Run As" to run the application.

#### Additional Configuration

- In the `server.xml` file, update the `<Context>` element's `docBase` attribute to point to the correct folder on your machine. This path should be consistent with the folder used by IoT students for storing pictures.

   ```xml
   <Context crossContext="true" docBase="C:\Users\12975\Pictures\" path="/upload" reloadable="true"></Context>
   ```

### File Structure

The project is organized into a Java project and a `webapp` directory, each with specific roles and files.

#### Java Project

- **dao**: This folder contains the implementation files for the Data Access Objects (DAOs), crucial for interacting with the database.
- **db**: This directory includes the files necessary for establishing and managing database connectivity.
- **vo**: Here, you'll find the Value Objects (VOs), such as `RecordInfo` and `UserInfo`, which represent the discovery record information and user information, respectively.

**Note**: The files `RecordDao.java` and `DBConnect.java` contain crucial database connection information. It's imperative to update the username and password in these files to match your local MySQL credentials.

#### webapp

- **jsp**: This folder houses the JSP files responsible for rendering the user interface. The key files include:
  - `error.jsp`: Engages when there's an input error, informing the user of the incorrect input.
  - `register.jsp`: Serves as the user registration interface.
  - `userinterface.jsp`: Acts as the main user interface.
  - `welcome.jsp`: Functions as the landing page after successful user login.
- **lib**: Contains all the necessary JAR packages required for the project's operation.

### Code Explanation

This section delves into the specifics of the key components within the E-commerce subsystem, providing a detailed explanation of the code and its functionality.

`UserDAO.java` & `UserDAOImpl.java`

These interfaces and classes are part of the Data Access Object (DAO) layer, crucial for interacting with the database to perform operations related to user data.

- **UserDAO.java**: Defines the contract for user operations. The `queryByUserInfo` method is declared here, specifying an operation to check the existence of a user based on provided user information.
- **UserDAOImpl.java**: Implements the operations declared in the UserDAO. The `queryByUserInfo` method is defined here, which interacts with the database to check if user credentials are valid.

`DBConnect.java`

This file is responsible for managing the database connection.

- **DBConnect.java**: It initializes the connection to the database and provides a method to retrieve this connection. This is where you configure the database URL, user, and password.

`UserInfo.java` & `RecordInfo.java`

These files define the structure of data objects used within the application.

- **UserInfo.java**: Represents a user entity with fields like username and password, and methods to access them (getters and setters).
- **RecordInfo.java**: Represents a record entity within the system, containing various attributes of a record and a list of image paths related to the record.

`UserLoginServlet.java` & `resgisterServlet.java`

These servlets handle HTTP requests and responses for user login and registration.

- **UserLoginServlet.java**: Manages the user login process. It takes the username and password from the request, checks them against the database, and then redirects to either a success or error page.
- **resgisterServlet.java**: Manages the user registration process. It retrieves user details from the request, validates them, and if valid, adds the new user's information to the database.

`RecordDao.java`

This file is part of the DAO layer and interacts with the database to manage record information.

- **RecordDao.java**: Contains methods for saving and retrieving record data. The `saveRecord` method adds a new record to the database, while the `getAllRecords` method retrieves all saved records.