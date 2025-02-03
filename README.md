# Authenticator CLI

Terminal integrated 2FA Authentication tool.

Use `authenticator.exe -h` to get help message.

```txt
Usage:
    authenticator.exe [global-options] command [command-options] [arguments...]

Commands:
    add                 Add new account.
    list                List available accounts.
    view                View an account.
    rename              Change account name.
    delete              Delete an account.

Global options:
    --help,-h           Get help.
```

To get help on commands
```txt
authenticator.exe -h <command>
```

## Setup

Clone the repo and cd into it
```bash
git clone https://github.com/kalpakavindu/authenticator-cli.git
cd ./authenticator-cli
```
Create the data file on the root of the project.
```bash
# On windows
echo "" >> data.txt

# On unix
touch data.txt
```

Build the project
```bash
cmake . -B build
# Debug build
cmake --build build --config Debug
# Release build
cmake --build build --config Release
```

Install
```bash
# For Debug build
cmake --install build --config Debug
# For Release buil
cmake --install build --config Release
```
