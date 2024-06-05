#!/bin/bash

# Reinstall each extension listed in extensions.txt
while read extension; do
    code --install-extension "$extension"
done < extensions.txt
