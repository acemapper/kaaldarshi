# kaaldarshi
A code written in C++ that helps with the time stomping. It simply means that when you place your files on the disk, forensics can easily catch it by looking at the time it was created. 
Kaaldarshi from the hindi word - meaning someone who can look back and forth into the time, can help you with this bypass. You can modify the file creation time of any file that you drop and match it with an older timestamp on the system.

Limitations:
 - The file modify time will still be the latest modified time.
 - Cant change the timestamp on a shared drive.
