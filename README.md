# b-remindR
Minimal reminder app written in Qt (C++)

NOTE: This is a personal project, created for personal use, licensed under the GPLv3 license. Only tested on GNU/Linux!

Dependencies: qt5 and a c++ compiler

How to install:
* git clone https://github.com/rdmc10/b-remindR
* cd b-remindR
* cmake .
* make
* ./b-remindR    


Example use case: 

![image](https://user-images.githubusercontent.com/66037895/154042125-ab6b2257-672d-4bb5-a2a7-ad67325d1a2b.png)

Once you click the "Start all timers" button, every timer will be started. Once a timer ends, a pop-up notification 
from the system tray will show up with the message that you chose. If you want a timer to start over again after it times out
you can check the "Loop" checkbox.

If you want to keep the running timers on without resetting them but still want to add new timers, you can do so with the "Update" button.
This will let the running timers untouched but will start whichever new timer you added.
