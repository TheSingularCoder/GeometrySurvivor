# 🔺 GEOMETRY SURVIVOR



https://github.com/user-attachments/assets/6cb0c860-23c6-44ef-b5db-feb2e4f9ca85



https://github.com/user-attachments/assets/e09da08b-298b-4150-bca1-6bd5015b9412



This is a top-down geometrical survival game where you upgrade your weapons and defeat waves of enemies.

## 🏗️ Architecture

The game uses an **EC (Entity-Component)** architecture, where each entity contains all of its own information, handling its own updates, rendering, etc. While this approach is not as flexible or cache-friendly as a pure ECS (due to cache misses), it is a massive improvement over traditional OOP. Entities act like "Legos", easily built from various interchangeable components.

Components manage themselves, and all hold a reference to their parent entity to share information (e.g., the `SpriteComponent` needing the position from the `TransformComponent`). When a component needed specific variations but fulfilled the same purpose, I used the **CRTP (Curiously Recurring Template Pattern)** technique. This allows them to share the same internal ID as their base class, meaning the manager can call the same functionality without needing to know if the entity is an *AI Summoner* or an *AI Sniper*.

The game is divided into **States**, and the core engine holds a pointer to the current state. To connect these states and share information between them, I implemented the **Blackboard pattern**, allowing all states to write down and update the data other states might need.

## 🛠️ Media & Libraries

The game is built using **SDL2**. Instead of using raw C pointers, I created a custom RAII wrapper to modernize the library for C++, ensuring proper memory management with automatic destructors. 

The code uses:
* **C++17**
* **SDL2** for rendering and window management.
* Smart Pointers (`std::unique_ptr`, `std::shared_ptr`) for safe memory handling.
* std::function (lambdas)
* Standard Template Library (STL) for data structures and functional callbacks.

## 🚀 How to Build and Run

### 1. Install Dependencies
Make sure you have a C++ compiler, CMake, and the SDL2 development libraries installed on your system. For Debian/Ubuntu-based systems, you can install them via terminal:

sudo apt update
sudo apt install build-essential cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
cmake -DCMAKE_BUILD_TYPE=Release ..
make
