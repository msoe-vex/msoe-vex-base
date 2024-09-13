# msoe-vex-base

## The base project for MSOE Vex Projects

### Installing Required Components:
- Install Git (https://git-scm.com). Use all the default settings if you're not sure. 
- Install VSCode
- Install PROS Extension for VSCode
- Install C++ extension for VSCode (if your project does not compile or runs into IntelliSense Problems, downgrade to 1.18.4)

### Cloning the repo
#### Options 1: Using the terminal
- If it's your first time using a terminal, please ask if you have questions! The terminal is an awesome tool for programmers and we'd love to help you get more comfortable with it
- Open Git Bash (press the Windows key and type in git bash, though you can use another terminal if you're more comfortable with that one, i.e. PowerShell)
- Navigate to a folder where you want the project to be copied to
    - Some useful terminal navigation commands
    - `pwd`: shows the folder the terminal is currently in (by default, git bash will start in your user folder, for the write of this readme as an example that's `/c/users/gagnonl`)
    - `cd`: changes to a directory 
        - For example, in directory `home/`, typing `cd test` will navigate to `home/test/` as long as that folder exists
        - `cd ..` goes up one folder, for example in `home/test/` will navigate to `home/`
    - `ls`: lists all files and folders in the directory
    - `mkdir` makes a new folder in the current location, for example, in `home/`, `mkdir test` will make a new folder `test`, but you will remainin `home/`
- Use the command `git clone https://github.com/msoe-vex/msoe-vex-base.git`. Note that running this command will make a new folder for you! So running this command in `home/` will make the folder `home/msoe-vex-base`, thought you'll still need to change into the directory.

#### Option 2: Using GitHub Desktop
- Note that this will probably require you to have a GitHub account, and if you don't have one you might want to use the terminal
- Download GitHub desktop
- Go to File -> Clone Repository
- Select URL
- Pick a path where you want the project to live to put under local path
- Paste the repo URL into the URL field `https://github.com/msoe-vex/msoe-vex-base.git`
- Press clone

#### You can also use another Git client that you're more comfortable with if you already know one!

### Opening the project
- Launch VSCode
- Open folder in VSCode
- Open a terminal in VSCode (View -> Terminal, or Ctrl+`)
- Make sure that on the left of the terminal you're in a PROS Terminal
- Type `pros m` in the terminal to build the project, and you're done!
If you have any questions about this process, please ask!

### Notes:
- Project may not compile by default if you already have gcc or g++ installed on your machine (might happen if you're in the C/C++ class), though there is a workaround that you can ask Luke about
