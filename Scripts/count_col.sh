#!/bin/bash

input="thesis.pdf"
output="thesis.pdf.printstats"

# Count the pages with colour in thesis
gs -o - -sDEVICE=inkcov ${input} &> ${output}

# Regex for black page looks like this
black=$(grep -o '0\.00000  0\.00000  0\.00000' ${output} | wc -l)
total=$(grep -o '0\.[0-9][0-9][0-9][0-9][0-9]  0\.[0-9][0-9][0-9][0-9][0-9]  0\.[0-9][0-9][0-9][0-9][0-9]' ${output} | wc -l)
# Check total agrees with number of pages
totalpdf=$(pdfinfo ${input} | grep Pages | awk '{print $2}')
if [[ total -ne totalpdf ]]; then
  echo "Found a different number of pages using GhostScript inkcov than pdfinfo"
  echo "Time to debug!"
  exit
fi
color=$(( $total - $black ))

echo "Number of black pages: " $black &> ${output}
echo "Number of color pages: " $color >> ${output}
echo "Number of total pages: " $total >> ${output}


# Count the number of words in main document
words=$(pdftotext -f 1 -l 221 ${input} - | wc -w)
echo "-----" >> ${output}
echo "Number of words from 1 to 221: " $words >> ${output}

