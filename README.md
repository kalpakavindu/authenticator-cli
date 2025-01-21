# Authenticator CLI

Terminal integrated 2FA Authentication tool

## Setup

Clone the repo and cd into it
```bash
git clone https://github.com/kalpakavindu/authenticator-cli.git
cd ./authenticator-cli
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
