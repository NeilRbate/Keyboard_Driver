# 🖥️ A Simple Linux Keyboard Device Driver

## 📌 Overview

This project is a **Linux device driver for a keyboard**, developed for learning purposes. It is designed to interact with the **Linux kernel (version 6.10.12)** and manage keyboard input at a low level.

## ✨ Features

- Detects **key press and release** events
- Registers a **character device** in `/dev/keyboard_module`
- Implements **interrupt handling** for key events
- Logs key events to the file `/tmp/keyboard_log`
- Fully compatible with **Linux Kernel 6.10.12**

## 🚀 Installation Guide

### 1️⃣ Clone the Repository
```sh
git clone git@github.com:NeilRbate/Keyboard_Driver.git
cd Keyboard_Driver
```

### 2️⃣ Build the Driver
```sh
make
```

### 3️⃣ Plug your keyboard and Udev load it, you can verify the installation

Check if the module is loaded:
```sh
dmesg | tail -n 20
lsmod | grep keyboard_driver
```

### 4️⃣ Unload the Module if needed, Udev unload it when keyboard is unpluged
```sh
sudo rmmod keyboard_driver
```
```sh
make clean
```

## 📄 Usage Instructions

Once the driver is loaded, it registers a device in `/dev/keyboard_module`. You can interact with it using:
```sh
cat /dev/keyboard_module
```

## 🛠️ Prerequisites

- Linux Kernel **6.10.12**
- GNU Make
- GCC Compiler
- Udev

## ⚠️ Important Notice
This driver is created **for learning purposes only** and is **not intended for production environments**, it's only work with **my keyboard**, each key is registered by hand.

## 📜 License
This project is licensed under the GNU GENERAL PUBLIC LICENSE. See the LICENSE file for details.

## 👨‍💻 Author

[Julien Barbate](https://github.com/NeilRbate)

---
⭐ If you find this project useful, consider giving it a star!

