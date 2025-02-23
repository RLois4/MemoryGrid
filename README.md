# MemoryGrid

**MemoryGrid** is an application designed to improve your memory and cognitive skills, helping you train to memorize numbers, dates, addresses, names, and other types of information. It's especially useful for improving forensic memory skills, enabling you to increase your ability to recall data quickly and accurately.

## How to Use

### Requirements
- Unix-like operating systems (Linux, macOS, etc.)
- `ncurses` library installed on your system

### Compiling the Code

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/memorygrid.git
   cd memorygrid
   ```

2. Compile the code:

   ```bash
   g++ -o memorygrid memorygrid.cpp -lncurses
   ```

3. Run the program:

   ```bash
   ./memorygrid
   ```

### Command-Line Arguments

- `-t <time>`: Sets the time (in seconds) that the numbers stay on the screen. The default is **3 seconds**.
- `-q <quantity>`: Sets the number of digits to be memorized. The value must be between **1 and 8** (default is **7**).

### Example Usage

```bash
./memorygrid -t 5 -q 4
```

This command runs MemoryGrid with a display time of **5 seconds** and a **4-digit** number to memorize.

## Contributing

If you'd like to contribute to MemoryGrid, feel free to fork the repository and submit a pull request. Contributions are welcome!

## License

MemoryGrid is open-source software released under the MIT License. See the LICENSE file for more details.
