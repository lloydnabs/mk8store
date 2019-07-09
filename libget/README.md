# libget
[![Build Status](https://travis-ci.org/vgmoose/libget.svg?branch=master)](https://travis-ci.org/vgmoose/libget) [![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://opensource.org/licenses/GPL-3.0)

get is a mini package manager that is used as the backend to [Homebrew App Store](http://github.com/vgmoose/hb-appstore) to allow more formal package management.

## Why?
**libget** is intended for use in smaller systems, such as homebrew'd video game consoles, where there is code execution but not a full stack of tools that package managers usually utilize, such as shell scripts or external libraries.

For documentation, metadata syntax, and repo setup, see [the wiki](https://github.com/vgmoose/get/wiki).

## Usage
### Setting up repos
A "repos.json" file should be present on the local machine, in the same directory as the `get` binary. See [repos.json](https://github.com/vgmoose/get/blob/master/.get/repos.json) for what this file should look like. If this file does not exist, depending on the use case (such as on the Wii U) a default repos.json should automatically be generated.

When `get` runs, it will go through the enabled repos in that config file, and try to make a GET request to `/repo.json`, which should contain (on the remote server) a listing of all of the packages and descriptions. Here is an example of what the remote's repo.json with one package looks like:
```
{
  "packages": [
    {
      "name": "space",
      "title": "Space Game",
      "author": "vgmoose",
      "description": "Shoot rocks in outer space, and stuff",
      "version": "1.0.0"
    }
  ]
}
```

The python script [repogen.py](https://github.com/vgmoose/get/blob/master/web/repogen.py) can generate the above repo.json file and the zip file structure explained below. It turns folders in the [packages](https://github.com/vgmoose/get/tree/master/web/packages) directory into zip files in `zips`.

### Installing a package
Installing a package requires the desired package name to exist in one of the repos, and for a GET to `/zips/$PKG_NAME.zip` to resolve. For example, to download the package `space` from above, the following command would be used:
```
./get space
```

It will try to fetch `/zips/space.zip` from the repo that contains the `space` package, and save it in `sd:/`.

### Listing all available packages
All available remote packages and their current status on disk will be listed.
```
./get -l
```

### Searching for a specific package
Search for a given string in the remote packages' name and description.
```
./get -s spa
```

### Removing an installed package
Any installed packages specified after the `--delete` flag will be removed
```
./get --delete space
```

This command parses the `manifest.install` file fetched when the package was installed, and uses it to determine which files to remove. Currently empty folders are left behind after the files are deleted.

## Building for PC
This project uses [Buck](https://github.com/facebook/buck) to build and [Buckaroo](https://github.com/LoopPerfect/buckaroo/) for dependency management.

1. Install a [precompiled Buck](https://github.com/facebook/buck/releases), and [precompiled Buckaroo](https://github.com/LoopPerfect/buckaroo/releases) for your platform, or build them from source
2. Run the following:
```
git clone https://github.com/vgmoose/libget.git
buckaroo install
buck build :get
```

The get CLI binary should now be sitting in: `./buck-out/gen/get`

## Building without Buck
You can also use the old Makefile to build the project. You will need to obtain the following dependencies: zlib, libcurl, rapidjson, and minizip

For your convenience, rapidjson and minizip sources are included in this repo in the `./src/libs` folder.

## Including the library
The easiest way to include the project is to use Buck and Buckaroo in your project, and run:
```
buckaroo add github.com/vgmoose/libget
```

But you can also manually include it by downloading the repo and pointing to the root folder in your Makefile. See Makefile for information on how the library can be used from a GNU Makefile.

## License
This software is licensed under the GPLv3.

Contributors:
- rw-r-r_0644 - manifest file parsing code
- zarklord - zip folder extraction library

### Contributing
It's not required, but running a clang-format before making a PR helps to clean up styling issues:
```
find . \( -name "*.cpp" -or -name "*.hpp" \) -not -path "./src/libs/*" -exec clang-format -i {} \;
```
