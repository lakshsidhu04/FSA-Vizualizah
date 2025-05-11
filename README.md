# Finite Automata Visualizer

This project is a C++ implementation of a **Finite State Automaton (NSA)** simulator. It generates visual representations (DOT files) at each step of input processing and can be used to create animated GIFs showing how the Automation transitions between states. It currently supports DFA and NFA.

## 📂 Project Structure

```
.
├── DOTFiles/                     # Contains DOT files for each run
├── src/
│   └── FSA/
│       ├── NFA/
│       │   ├── NFA.cpp           # NFA implementation
│       │   └── NFA.h             # NFA header file
│       └── DFA/
│           ├── DFA.cpp           # DFA implementation
│           └── DFA.h             # DFA header file
├── main.cpp                      # Entry point
├── README.md
└── Makefile
```

## 🚀 Features

- Models an NFA with transitions, start and accept states
- Visualizes each step of input processing as a DOT graph
- Highlights active states and transitions used at every step
- Can be used with Graphviz to generate animated GIFs

## 🛠️ Requirements

- C++17 or later
- [Graphviz](https://graphviz.org/) (for visualizing DOT files)
- `dot`, `convert` (from ImageMagick) if generating GIFs

## 🔧 Build and Run

1. **Compile the code**
   ```bash
   g++ -std=c++17 main.cpp src/NFA.cpp -o nfa_visualizer
   ```

2. **Run the program**
   ```bash
   ./nfa_visualizer
   ```

3. **(Optional) Convert DOT files to images**
   ```bash
   mkdir images
   for dot in DOTFiles/*.dot; do
       dot -Tpng "$dot" -o "images/$(basename "${dot%.dot}").png"
   done
   ```

4. **(Optional) Create animated GIF**
   ```bash
   convert -delay 100 images/*.png -loop 0 nfa_simulation.gif
   ```

## 🧪 Example

Given an input string `"abba"`, the tool will generate:
- `instance_0.dot` (initial state)
- `instance_1.dot` (after reading `'a'`)
- `instance_2.dot` (after `'b'`)
- and so on...

Each step highlights:
- Active states in **blue**
- Accepting + active states in **green**
- Transitions used in **red**

## 📸 Sample Output

![Sample GIF](nfa_simulation.gif)

## 🧱 Future Improvements

- Support ε-transitions
- Deterministic Finite Automaton (DFA) version
- Web-based visualization with live simulation

## 📜 License

MIT License
