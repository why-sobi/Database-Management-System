# Game Management System

A comprehensive system for managing players and games using Binary Search Trees (BST) data structure.

## Features

- **Player Management**
  - Add new players
  - Search for players by ID
  - Delete players
  - Edit player information
  - View top N players
  - Show player details

- **Game Management**
  - Add new games
  - Search for games by ID
  - Delete games
  - Edit game information

- **Tree Visualization**
  - Show N layers of the tree
  - Display layer numbers
  - Show paths in the tree

- **Data Persistence**
  - Save data to CSV files
  - Load data from files

## Data Structures

- Binary Search Trees (BST) for both players and games
- Custom Queue implementation for tree traversal
- Specialized BST for tracking games played by players

## Getting Started

### Prerequisites
- C++ compiler
- Standard Template Library (STL)

### Installation
Usage:
The system provides an interactive menu with the following options:

Insert Player/Game
Search and Retrieve
Delete Entry
Save Data to CSV
Show N Layers
Show Layer Number
Show Path
Edit Entry
Top N Players
Show Player Details
Check if Player Has Played Game

File Structure:
runner.cpp - Main program file
header.h - Header file containing class definitions
class.h - Class implementations
Games.txt - Game data storage
Players.txt - Player data storage
