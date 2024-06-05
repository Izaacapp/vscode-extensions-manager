# VS Code Extensions Manager

This repository contains scripts to manage Visual Studio Code extensions. It includes scripts to list, uninstall, and reinstall extensions. These scripts are useful for quickly setting up a clean development environment or transferring your extensions to a new setup.

## Scripts

- `extensions.txt`: A file that lists all your current VS Code extensions.
- `uninstall-extensions.sh`: A script to uninstall all extensions listed in `extensions.txt`.
- `reinstall-extensions.sh`: A script to reinstall all extensions listed in `extensions.txt`.

## Usage

1. **Save your current extensions to a file**:
    ```bash
    code --list-extensions > extensions.txt
    ```

2. **Uninstall all extensions**:
    ```bash
    chmod +x uninstall-extensions.sh
    ./uninstall-extensions.sh
    ```

3. **Reinstall all extensions**:
    ```bash
    chmod +x reinstall-extensions.sh
    ./reinstall-extensions.sh
    ```