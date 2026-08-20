# SkollDice - Truly Random Dice Generator

[<img title="" src="file:///home/skollwarynz/DnD_truly_random_dice/SkollDice/assets/SkollDice_icon.png" alt="Build and Release All" width="235">]()
![License MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

This project is a dice generator for RPG games that actually implements full random generation of the numbers used as results for the dice.

---

## 📑 Table of Contents

1. [Introduction](#introduction)
2. [Project Structure](#project-structure)
3. [Architecture](#architecture)
4. [Calling All Artists & Designers!](#calling-all-artists--designers)
5. [How to Report a Bug](#how-to-report-a-bug)
6. [Suggestions](#suggestion)
7. [Donation](#donation)

---

## Introduction

The idea is to use the entropy inside the computer or phone of the user to produce fully randomized numbers. The code is open source to let each programmer and Game Master control and eventually inspect any sort of problem with the number generation.

The goal is to fix the shortcomings of both physical and digital dice, helping all players fully enjoy true randomization.

For any suggestion or expansion, you can open an issue, and if useful, I will add the feature.

## Project Structure

The repository is organized into two main directories:

- **`SkollDice/`** -> Contains the cross-platform graphical application (written in C using [LVGL](https://lvgl.io) and SDL2) for desktop, mobile, and Linux (AppImage).
- **`SkollDice_bot/`** -> Contains the dedicated Discord bot for rolling dice directly in chat. Made using [Concord](https://github.com/Cogmasters/concord) library for Discord API.

Each directory presents another README with screenshot or specifics about the project inside. 

## Architecture

The program uses a proven method to produce normally distributed fully random numbers:

- **Simple linear method**: The method is explained in section 5.1 of the [NIST Special Publication 800-90A](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-90Ar1.pdf), so for the full explanation you can read the document directly.

The idea is to produce a single number (a 1-dice throw) using the simple linear method, as it is recommended for it. When the program produces multiple dice throws, the generator automatically uses the complex linear method to produce better results.

Each byte is read from `/dev/urandom` because it produces fully cryptographically secure randomized numbers on POSIX systems. As we generate each byte of the number, we secure full randomization through the use of the linear method.

For Windows, the function used is `RtlGenRandom`, which produces a similar behavior to `urandom`.

## Calling Artists & Designers!

While I was creating SkollDice I didn't have time to focus on graphics in general. It would be amazing if any of you collaborated and using the Fork command tried to implement a more useful GUI. If you're not a programmer do not worry because even the official Icon for SkollDice was made by hand!

I really love art and Design so I decided to publish the 3D Blender model used for the Icon creations. Inside SkollDice/Assets you can download the original model and feel free to interpret and redesign it as you wish! I would be glad if any of you wanted to merge their request with a new logo or GUI.

## How to Report a Bug

If you find a bug, please go to the "Issues" section and open a new one where you try to explain the input and behavior of the program so I can work on fixing it. Thank you!

## Suggestion

This was my real first big project, so I'm neither an icon designer nor a professional Discord bot programmer. Any suggestions are welcome, and I will evaluate minor graphic changes over time.

## Donation

This project was long and difficult to implement, and I'm currently working on a smartphone version to let any user have the commodity of using SkollDice. If you find this project important or useful, feel free to make a donation through "Buy me a Coffee" to support my work on open-source creation and all the other projects I'm currently creating for the programmers of the future.
