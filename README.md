# PGE Window Simulator

A header-only extension library for the olc::PixelGameEngine that enables the creation of PGE-like windows inside a PGE application. It allows multiple interactive, resizable, movable, and closable windows to exist within a single PGE screen.
Similarly to PGE, the library provides a Window class that the user makes derived classes of, and each class must override functions that get called when the window gets created, updated or destroyed. The user can even make multiple instances of the same derived Window class.
All of the windows run on the same thread, and as such they are synchronized with each other.

Example image:
<img width="799" height="580" alt="windowsimDemo" src="https://github.com/user-attachments/assets/fe73a784-982a-4f3a-b2b5-909224b9c7a0" />
