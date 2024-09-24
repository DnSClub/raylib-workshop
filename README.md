# raylib-workshop
Repo for DNS Raylib Workshop

### Step 1: Clone/download this repo
```
git clone https://github.com/DnSClub/raylib-workshop.git
```
Do it! 🗿

---

### Step 2: Compile raylib from source on your machine
### <ins>[ Windows ]</ins>
If the repo doesn't already open the window.
1. Get G++ compiler:
- Go to [this link](https://winlibs.com/#download-release)
- Download the latest Win64 7-zip archive
- Extract it in :C\
- Add C:\..\mingw64\bin to your PATH variables.
- Confirm by receiving correct path from ```where.exe g++```
2. [Raylib repo](https://github.com/raysan5/raylib) -> Releases -> Source Code zip -> extract zip in C:\
3. Terminal -> navigate to raylib\src -> ```mingw32-make PLATFORM=PLATFORM_DESKTOP```
4. Copy libraylib.a and paste into /lib in project folder

### <ins>[ MacOS ]</ins>
1. Get G++ compiler:\
```brew install gcc```\
```g++ --version```
3. [Raylib repo](https://github.com/raysan5/raylib) -> Releases -> raylib-version_macos.tar.gz -> extract in Users/your_username
4. Copy libraylib.a and paste into /lib in project

### <ins>[ Ubuntu Linux ]</ins>
1. Get G++ compiler:\
```sudo apt update```\
```sudo apt install build-essential```\
```g++ --version```
2. [Raylib repo](https://github.com/raysan5/raylib) -> Releases -> Source Code zip -> extract zip in Home
3. Terminal -> cd into raylib/src -> ```make PLATFORM=PLATFORM_DESKTOP``` -> ```sudo make install```
5. Copy libraylib.a and paste into /lib in project

---

### Step 3: Compile and run main.cpp
1. Open a terminal / the project in your editor
2. ```make```
3. Windows: ```./game.exe```\
   MacOS + Linux: ```./game```
