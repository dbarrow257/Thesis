#!/bin/bash

if [[ $# -ne 1 ]]; then
  echo "Need one argument"
  exit
fi

echo "`date +%s` $(pdfinfo $1 | grep "Pages:" | sed -e "s/^Pages: *//") $(pdftotext $1 - | wc -w) $(pdfinfo $1 | grep "File size:" | sed -e "s/^File size: *//" | sed -e "s/ bytes$//")" >> $1.stats
echo "Added PDF statistics to file $1.stats"

root -l -b -q 'plotstats.C'
