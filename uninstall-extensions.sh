#!/bin/bash

# Uninstall each extension listed in extensions.txt
while read extension; do
    code --uninstall-extension "$extension"
done < extensions.txt
