# Read from the file file.txt and print its transposed content to stdout.
awk '
{
    for (i = 0; i < NF; i++) {
        words[i][NR] = $(i+1);
    }
    num_rows = NR;
}
END {
    for (i in words) {
        for (j in words[i]) {
            if (j == num_rows) {
                printf "%s\n", words[i][j]
            } else {
                printf "%s ", words[i][j]
            }
        }
    }
}
' file.txt
