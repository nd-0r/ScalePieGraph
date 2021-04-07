# World Scale Pie Graph Visualization

## Description

### The Interactive Pie Graph

For my CS 126 final project, I would like to build an interactive visualization for musical scales. The centerpiece of this visualization will be a pie graph with flexible partitions. This pie chart will represent the division of a musical octave into intervals. There will be a number of world scales pre-loaded in the program with corresponding pie charts from which the user can choose. These scales will be accessible through a dropdown menu or a scrollable drawer next to the pie graph. In addition, the visualization will be interactive: the user will be able to manipulate the size of the partitions by dragging sliders on the vertices of the pie sections. The user will also be able to construct their own pie graph by adding and removing sections of the graph. Specifically, the user should be able to add sections by clicking an addition button in the top right corner, and remove sections by selecting them with the mouse pointer and removing them with a subtraction button in the top right corner.

### The Keyboard

In addition to the interactive pie graph, the user will be able to play the visualized scale through a keyboard on the bottom edge of the screen. The keyboard sections will resize dynamically based on the number of intervals in the pie graph. These keyboard sections will correspond to keys on the physical computer keyboard (i.e. ```a,s,d,f,...,l```) as space permits. 

## Why I want to do this project

While this project might appear mundane, it provides rich opportunity to explore intersections of computer science and music that are of interest to me:

1. __Computational Musicology__
    - This project gives me the opportunity to explore musical scales of different world musics that interest me and I would learn how to represent these scales as C++ objects.
2. __Digital Audio Synthesis__
    - This project gives me the opportunity to explore rudimentary sound synthesis through the cinder library. In implementing the stretch goals (see below), I would learn how to integrate the midi protocol in c++.

### My background

In addition to the interest I have in learning more about this project, I have significant background knowledge in these areas. From the music side I am a violinist and jazz pianist and I've tested out of the entire music theory/musicianship/piano sequence here at the University of Illinois. I have also spent a bit of time researching the musical scales that I plan to implement. From the technical side, I have done some basic signal processing and sound synthesis in Python and with the JUCE library in C++, but I expect it to be significantly different with the Cinder library.

## Timeline

|Week|Goals|
--- | --- 
1| Build scale class and core audio components.
2| Integrate scale and audio components with basic, non-interactive pie chart with dropdown menu for scales. Start working on interactivity for pie chart and keyboard.
3| Add interactivity to pie chart and keyboard and polish interface.

## Stretch goals:

- save/load scales from files
- illuminate sections of the pie graph based on keyboard input
- implement a polyphonic keyboard
  - color sections on in the pie chart based on acoustic dissonance
- implement midi support
- implement resizable windows
- implement basic sound controls
  - envelope
  - filter
