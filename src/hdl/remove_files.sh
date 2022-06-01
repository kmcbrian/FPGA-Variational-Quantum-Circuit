# Deletes all files written in 'input' file
#!/bin/bash
input="generated_files.txt"
while IFS= read -r line
do
  rm "$line"
done < "$input"
rm "$input"
echo "Deleted all generated HDL files"
