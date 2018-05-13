# chall-shellql

A shellcoding web challenge.

The intended solution is to write shellcode to: make a raw SQL query to the SQL server connection on fd 4 (opened in the PHP code), and output the flag.

One complication is that the php scripts are running as `cgi-bin`, which means that your output must follow the cgi-bin format, otherwise no output for you (500).

So you must send `Content-type: text/html\n\n` first, then the output.

Check out [exploit.py](exploit/exploit.py) and [shellcode.s](exploit/shellcode.py).

`deployment` has the Vagrantfile and ansible script necessary.

`exploit` has the exploit that works.

`src` has the source for the extension and the php files.

TAGS: web, shellcode

LEVEL: easy/med

STATUS: ready

AUTHOR: adamd

TESTED BY: nobody. 

