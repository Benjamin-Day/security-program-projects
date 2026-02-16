# Simple Cyber Security Projects

A collection of projects demonstrating skills in low-level programming, systems programming, and network security. These were completed as part of my security program.

**Author:** Benjamin Day

**Date:** 2022

---

## Projects

### 1. x64 Assembly Socket Client
**Language:** x86-64 Assembly (NASM)

A socket client written entirely in x86-64 assembly using direct Linux syscalls (no libc). Connects to a server, requests random bytes, sorts them using a counting sort algorithm implemented in pure assembly, and writes results to a file.

**Highlights:**
- Direct syscall interface for socket, mmap, and file I/O operations
- Counting sort algorithm in x86-64 assembly
- Dynamic memory allocation via `mmap`/`munmap`
- Input validation and error handling

**Build & Run:**
```bash
nasm -f elf64 x64Client.nasm -o x64Client.o
ld x64Client.o -o x64Client
./x64Client
```

---

### 2. Hex Dump Program
**Language:** C

A hex dump utility that displays binary file contents in a formatted table with hexadecimal values, ASCII character representations, and offset addresses. Detects and displays the file's magic number.

**Build & Run:**
```bash
gcc hexdump.c -o HexDump
./HexDump
```

**Sample Output:**
```
Magic number: 0x43202f2f        File Type: //C
=================================================================================
| Offset |                  Hexadecimal Data                 | Character Format |
=================================================================================
| 000000 | 2f 2f 20 43 72 65 61 74   65 64 20 62 79 20 42 65 | //.Created.by.Be |
```

---

### 3. Malware Sample Sorter
**Language:** Python 3

A file organization utility for malware analysis workflows. Scans a directory, generates SHA-256 hashes for each file, then sorts files into subdirectories by extension and renames them using their hash as an identifier.

**Features:**
- Recursive directory traversal
- SHA-256 file hashing
- Automatic extension-based folder creation
- ASCII directory tree visualization

**Run:**
```bash
python3 sampleSorter.py
```

---

### 4. Vulnerability Port Scanner
**Language:** Python 3

A multi-threaded network scanner that identifies open ports, grabs service banners, and cross-references discovered services against known vulnerabilities using `searchsploit`.

**Features:**
- TCP port scanning across the full port range
- Banner grabbing with HTTP HEAD requests
- Automated vulnerability lookup via `searchsploit`
- Multi-threaded scanning with `ThreadPoolExecutor`
- Timestamped report generation

**Prerequisites:**
- `searchsploit` installed on the system

**Run:**
```bash
python3 portScanner.py
```

---

## Tech Stack

| Project | Language | External Tools |
|---|---|---|
| x64 Assembly Client | x86-64 Assembly | NASM, ld |
| Hex Dump Program | C | GCC |
| Malware Sample Sorter | Python 3 | None |
| Port Scanner | Python 3 | searchsploit |

All projects rely on standard libraries with no additional package dependencies.
