#!/bin/bash

# Path to Adobe Illustrator app
ILLUSTRATOR_APP="/Applications/Adobe Illustrator 2023/Adobe Illustrator.app"

# Path to the JSX script
JSX_SCRIPT_PATH="/Users/markoates/Repos/allegro_flare/scripts/Illustrator/export_1000.jsx"

# Function to run the script in an open instance of Illustrator
run_jsx_in_open_illustrator() {
   osascript <<EOD
      tell application "Adobe Illustrator"
         do javascript POSIX file "$1"
      end tell
EOD
}

# Check if Illustrator is already running
if pgrep -xq "Adobe Illustrator"; then
   echo "Adobe Illustrator is already running. Sending script to the open instance..."
   # Run the JSX script in the already open instance
   run_jsx_in_open_illustrator "$JSX_SCRIPT_PATH"
else
   echo "Adobe Illustrator is not running. Launching Illustrator and running the script..."
   # Use the open command to launch Illustrator and run the script
   open -a "$ILLUSTRATOR_APP" --args -r "$JSX_SCRIPT_PATH"
fi

