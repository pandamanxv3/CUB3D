# Cub3D Project README

## Overview
Cub3D is a school project developed in C, inspired by the classic game "Wolfenstein 3D." It's an educational exercise in 3D graphics programming, focusing on the ray-casting technique to simulate a first-person navigation through a maze. The project is built using the MinilibX graphics library, a lightweight programming interface designed for X-Window System, primarily used in academic settings for teaching basic graphics programming.

## Programming Language
- **C**: The entire project is implemented in C, providing a challenging yet educational experience in low-level graphics programming.

## Key Features
- **3D Ray-Casting**: Simulates realistic 3D maze navigation using ray-casting principles.
- **Texture and Color Management**: Implements different textures for walls based on their orientation and allows customizable colors for the floor and ceiling.
- **Interactive Controls**: Includes keyboard controls for navigation and camera rotation.
- **Map Parsing**: The program reads `.cub` files to generate the 3D maze, with strict rules for map layouts including walls, empty spaces, and player start position.
- **Window Handling**: Efficiently manages window operations like minimization and closing.

## Running the Project
- The program is executed by passing a `.cub` file as an argument, which contains the map and texture information for the maze.
- **Dependencies**: Requires the MinilibX library, which is tailored for Unix-based systems and provides the necessary functions for window management and basic drawing.


