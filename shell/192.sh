# Read from the file words.txt and output the word frequency list to stdout.
awk '{for (i = 1; i <= NF; i++) {dict[$i]++}} END{for (k in dict) {print k, dict[k]}}' words.txt | sort -n -r -k2
