#!/bin/bash

# Définir le nom du fichier à traiter
fichier="coding-style-reports.log"

while IFS= read -r ligne; do
    IFS=':' read -ra valeurs <<< "$ligne"
    echo "::error title=${valeurs[2]#./} coding style error,file=${valeurs[0]},line=${valeurs[1]}::${valeurs[3]} "
done < "$fichier"
