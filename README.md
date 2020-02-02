# addrfinder
Windows function address finder and metasploit block_api hash calculator

# Compiling
32 bits
```
gcc.exe addrfinder.c -o addrfinder32.exe -m32
```
64 bits
```
gcc.exe addrfinder.c -o addrfinder64.exe -m64
```

# Running
32 bits
```
addrfinder32.exe kernel32.dll WinExec
addrfinder - windows address resolution program - by M4v3r1ck - v.01

[+] kernel32.dll!WinExec address found at 0x74D8D220
[+] kernel32.dll!WinExec msf block_api hash is 0x876F8B31
```
64 bits
```
addrfinder64.exe kernel32.dll WinExec
addrfinder - windows address resolution program - by M4v3r1ck - v.01

[+] kernel32.dll!WinExec address found at 0x00007FFEDBB3F090
[+] kernel32.dll!WinExec msf block_api hash is 0x876F8B31
```
