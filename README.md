```markdown
# Electronic Journal

This is an electronic journal project written in C++. The project consists of three main files:

- `exceptions.hpp` — a header file containing exception classes for error handling.
- `journal.hpp` — a header file containing the `Journal` class, which implements the functionality of the electronic journal.
- `main.cpp` — the main file containing the program's entry point.

## Building the Project

To build the project, you will need a C++ compiler (e.g., `g++`).

1. Ensure that you have a C++ compiler installed. If not, install it:
   - For Linux: `sudo apt install g++`
   - For macOS: `xcode-select --install`
   - For Windows: install [MinGW](http://www.mingw.org/) or use [MSVC](https://visualstudio.microsoft.com/).

2. Clone the repository (if you haven't already):
   ```bash
   git clone https://github.com/your-username/electronic-journal.git
   cd electronic-journal
   ```

3. Compile the project:
   ```bash
   g++ -o electronic_journal main.cpp
   ```

4. Run the program:
   ```bash
   ./electronic_journal
   ```

## Project Structure

- **`exceptions.hpp`** — contains exception classes used for error handling in the program.
- **`journal.hpp`** — contains the `Journal` class, which implements the core logic of the electronic journal (adding, deleting, editing entries, etc.).
- **`main.cpp`** — the program's entry point. This is where the journal is initialized and user interaction takes place.

## Usage

After running the program, you will see a menu where you can:
- Add a new entry to the journal.
- View existing entries.
- Edit or delete entries.
- Exit the program.

## Example

```plaintext
Welcome to the Electronic Journal!
1. Add an entry
2. View entries
3. Edit an entry
4. Delete an entry
5. Exit
Choose an action: 1
Enter student name: Ivan Ivanov
Enter grade: 5
Entry successfully added!
```
