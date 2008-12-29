#! /bin/awk -f
BEGIN { FS="[^a-zA-Z1-9]+"}

{ for (i=1; i<=NF; i++)
     words[$i]++
}

END { for (i in words)
    print i, words[i]
}
