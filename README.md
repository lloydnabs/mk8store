# MK8 App Store
A graphical frontend to the [get package manager](https://github.com/vgmoose/libget) for downloading and managing mario kart 8 mods on the wii u.


### Wii U
To run this program, a Wii U with access to the Homebrew Launcher is required. This can be done on any firmware. To run the Homebrew Launcher, see the tutorial [here](https://wiiu.hacks.guide).

Extract the latest [hb-appstore](https://github.com/vgmoose/hb-appstore/releases) to `sd:/wiiu/apps/appstore/`, and run "hb App Store" from within Homebrew Launcher. When you're done, you can press the Minus (-) button to exit.

### Building for Wii U (with WUT)
The below instructions are currently for Linux and macOS
1. Install [dkp-pacman](https://devkitpro.org/viewtopic.php?f=13&t=8702)
2. Setup [wiiu-fling](https://gitlab.com/QuarkTheAwesome/wiiu-fling#wiiu-fling) according to the instructions
3. Install sdl2, wut, devkitPPC and other dependencies (on macOS, use `wut-osx` instead of `wut-linux`)
```
sudo dkp-pacman -S wut-linux wiiu-sdl2 devkitPPC wiiu-libromfs wiiu-sdl2_gfx wiiu-sdl2_image wiiu-sdl2_ttf wiiu-sdl2_mixer ppc-zlib ppc-bzip2 ppc-freetype ppc-libpng ppc-mpg123 wiiu-curl-headers ppc-pkg-config wiiu-pkg-config
```
4. Once the environment is setup:
```
git clone --recursive https://github.com/vgmoose/hb-appstore.git
cd hb-appstore
make -f Makefile.wiiu
```

If all goes well, `appstore.rpx` should be sitting in the current directory.

### Building for PC (with Buck)
This project is moving towards [Buck](https://github.com/facebook/buck) to build and [Buckaroo](https://github.com/LoopPerfect/buckaroo/) for dependency management.

1. Install a [precompiled Buck](https://github.com/facebook/buck/releases), and [precompiled Buckaroo](https://github.com/LoopPerfect/buckaroo/releases) for your platform, or build them from source
2. Run the following:
```
git clone https://github.com/vgmoose/hb-appstore.git
cd hb-appstore
buckaroo install
buck build :hb-appstore
```

Currently sdl2 is manually linked in the `.buckconfig`, as a buckaroo port is not yet available, so SDL2 will need to be installed via the system package manager (see below). After running the above, there should be a binary sitting in `./buck-out/gen/hb-appstore`.

#### Using GNU Makefile
There's a separate makefile for building the SDL2 app for PC, if you don't want to try the Buck build. Below instructions are for Ubuntu, but should be similar on other platforms:
```
sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-gfx-dev zlib1g-dev gcc g++ git
git clone --recursive https://github.com/vgmoose/hb-appstore.git
cd hb-appstore
make -f Makefile.pc
```

### License
This software is licensed under the GPLv3.

#### Maintainers
- [vgmoose](https://github.com/vgmoose)
- [pwsincd](https://github.com/pwsincd)
- [rw-r-r_0644](https://github.com/rw-r-r-0644)
- [crc32](https://github.com/crc-32)
- [Lloyd Nabbit](https://github.com/lloydnabs)

#### Contributing
If you want me to add your mod/s to the repository dm me on Discord at Lloyd Nabbit#6457
