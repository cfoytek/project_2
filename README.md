
# A CLI Text Editor Based on NCurses
This repository hosts a vim-like CLI text editor that was produced for a project in one of my classes. It uses a 2D character array to buffer and perform operations on a text file in-memory, and the NCurses library to display the buffer and changes to the buffer to the screen.

This text editor should not be used as either an example of the right way to do things, nor should it be used to edit text files in general. In fact, it is here expressly as an example of why you should plan projects and not wait until the last minute to start them.

## Compilation
The text editor is compiled with GNU Make and NCurses. Most unix-like systems are shipped with NCurses, but if you don't have it, it can be downloaded [here](https://invisible-island.net/ncurses/), or you can use your favorite package manager to get it.

## Controls
The text editor has 2 modes, NORMAL and INSERT. The editor is initialized in the NORMAL mode, and entering into INSERT mode is done by pressing 'i'. All operations are captured as single keypresses in NORMAL mode. Below is a list of all operations:

 - q - quits the program
 - w - writes the file buffer to disk
 - d - deletes the line that the cursor is on
 - y - copies the line that the cursor is on into a copy buffer
 - p - pastes the text in the copy buffer to the line below the cursor
 - n - inserts a new line below the cursor
 - i - enter into INSERT mode
 - ESC - enter into NORMAL mode

## Limitations
Due to time constraints several things in the text editor are not possible. First, when typing at the end of a line, text will be wrapped at the end of the terminal screen onto the next line. However, this is not real line-wrapping. A newline character is appended to the end of the current line and a new line is inserted into the file buffer below the current line and the cursor is moved to that position. Because of this design choice it is not currently possible to wrap text by inserting characters in the center of the line, the program simply will not allow you to insert anymore characters.

The above design choice and aforementioned time constraints also led to our file-buffer handling code and screen display code being more tightly coupled than they should be. While still working on the projects I thought about ways that it could be redesigned to decouple these two subsystems to the point that the buffer handling code could be dropped into another project as a plug-and-play backend for another user interface -- possibly a GUI. 

## Redesign
> This section is under construction and ongoing. I have plans to redesign and re-implement this project from scratch using a gap buffer to make writing to the file buffer less expensive, and to decouple the backend file handling from the front end display code. 

