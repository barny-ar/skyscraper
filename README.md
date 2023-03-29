# 4x4 Skyscraper Puzzle Solver

Welcome to the 4x4 Skyscraper Puzzle Solver! This project is a C program that solves 4x4 Skyscraper puzzles using a recursive brute-force algorithm.

## Table of Contents

1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Example](#example)

## Introduction

A Skyscraper puzzle is a logic puzzle where the objective is to place a building of each height (1 to N) in each row and column of an NxN grid, subject to clues given for each row and column. In a 4x4 Skyscraper puzzle, the building heights range from 1 to 4. The clues are the number of visible buildings when looking at the grid from a specific direction (top, right, bottom, left). A taller building will block the view of any shorter building behind it.

This program takes 4 sets of input, one for each direction (top, right, bottom, left), and returns a solved puzzle based on the given clues.

## Installation

1. Clone this repository to your local machine:

` git clone https://github.com/Lemma-Barnabas/skyscraper `

2. Change to the repository directory:

` cd skyscraper-puzzle-solver `

3. Compile the C program:

` gcc -o skyscraper_solver main.c `

## Usage

After compiling, run the program with the input clues as arguments in the following order: top, right, bottom, left.
<prev>

` ./skyscraper_solver 1 2 3 4 2 3 4 1 3 4 1 2 4 1 2 3 `

Each set of clues must have exactly 4 space-separated integers.

## Example

Input:

Top: 1 2 3 4
Right: 2 3 4 1
Bottom: 3 4 1 2
Left: 4 1 2 3

Run the program:

` ./skyscraper_solver 1 2 3 4 2 3 4 1 3 4 1 2 4 1 2 3 `


Output:
<prev>
```bash

1 2 3 4
2 3 4 1
3 4 1 2
4 1 2 3

```
</prev>
