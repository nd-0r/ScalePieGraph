# Interactive Scale Pie Graph

![](https://imgur.com/TFRwULf)

## Introduction

The Scale Pie Graph is an interactive visualization and synthesizer for musical scales. Using a dataset, the application enables playing the notes of the scales with different waveforms along with visualizing the intervals of the scale and resizing them to create new sounds.

## Dependencies

- [gcc] or [clang] or [MSVC 2015+][visual-studio]
- [libcinder]
- [cmake]
- [jsoncpp] (included in CMakeLists.txt)
- [catch2] (for testing, included in CMakeLists.txt)

## Quick Start

### MacOS

1. Install required dependencies

```console
$ brew install gcc cmake
```

2. Download and build cinder using the instructions [here](https://courses.grainger.illinois.edu/cs126/sp2021/notes/cinder-installation-notes/)

3. Clone this repository into a folder with the path ```{cinder}/my-projects/``` inside your Cinder installation.

4. Build the application

```console
$ cmake --build ./
$ open Debug/scale-pie-graph/scale-pie-graph.app
```

## Dataset

This application operates using a dataset of scales. This dataset must be dragged and dropped onto the application window. The dataset must conform to the following json schema:

```
{"scales": [
  {
    "name": "Hilbert",
    "intervals": [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11],
    "description": "A scale of diatonic intervals"
  },
  {
    "name": "Nothing",
    "frequencies": [
      261.6255653006,
      392.4383479509
    ],
    "description": "A scale of frequencies"
  }
]}
```

## Controls

### Keyboard

| Key       | Action                                                      |
|---------- |-------------------------------------------------------------|
| `a s d f g h j k l ; '`       | Start a note                                           |
| `spacebar`       | Stop the playing note                                            |
| `q` | Switch to sine oscillator                                                        |
| `w`       | Switch to triangle oscillator                                          |
| `e`       | Switch to square oscillator    |
| `r`       | Switch to sawtooth oscillator   |
| `up/down`       | Transpose                                           |
| `+/-`       | Change number of octaves |

### Mouse

- Click keys to play notes
- Click and drag to play notes in succession
- Drag handles on the pie graph to create custom scales

[visual-studio]: https://www.visualstudio.com/
[gcc]: https://gcc.gnu.org/
[clang]: https://clang.llvm.org/
[cmake]: https://cmake.org/
[catch2]: https://github.com/catchorg/Catch2.git
[jsoncpp]: https://github.com/open-source-parsers/jsoncpp.git
[libcinder]: https://www.libcinder.org/download