#!/bin/bash

# Validate input
if [ "$#" -ne 1 ]; then
   echo "Usage: list_asset <asset_key>" >&2
   exit 1
fi

# Input variables
asset_key=$1
csv_file="/Users/markoates/Assets/assets_db.csv"

# Search for the asset in the CSV file
grep "$asset_key" "$csv_file"

