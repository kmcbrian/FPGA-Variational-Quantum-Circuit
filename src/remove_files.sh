#!/bin/bash
input="generated_files.txt"
while IFS= read -r line
do
  echo "Deleting $line"
  rm "$line"
done < "$input"
rm "$input"

