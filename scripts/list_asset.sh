#!/bin/bash

# Validate input
if [ "$#" -lt 1 ]; then
   echo "Usage: list_asset <keyword_1> [<keyword_2> ... <keyword_n>]" >&2
   exit 1
fi

# Input variables
csv_file="/Users/markoates/Assets/assets_db.csv"
num_keywords=$#
search_pattern=$1

# Combine all arguments into a grep pattern
shift
for keyword in "$@"; do
   search_pattern="$search_pattern|$keyword"
done

# Search for the combined pattern in the CSV file and count the results
results=$(grep -E "$search_pattern" "$csv_file")
num_results=$(echo "$results" | wc -l)

# Output the results
echo "$results"
echo ""
echo "Number of keywords: $num_keywords"
echo "Number of results: $num_results"


