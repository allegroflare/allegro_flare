// Get the active document
var doc = app.activeDocument;

// Get the file name without the .ai extension
var file_name = doc.name.replace(/\.ai$/i, '');

// Set the export options
var export_options = new ExportOptionsPNG24();
export_options.horizontalScale = 1000;  // Scale to 1000%
export_options.verticalScale = 1000;    // Scale to 1000%
export_options.artBoardClipping = true; // Export artboard only
export_options.transparency = true;     // Preserve transparency

// Get the file path of the active document and create a new file path for the PNG
var file_path = doc.fullName.parent.fsName + "/" + file_name + "-1000x.png";

// Export the active artboard as PNG
var export_file = new File(file_path);
doc.exportFile(export_file, ExportType.PNG24, export_options);

// Notify the user
alert("SUCCESS! \n\nArtboard exported as PNG at 1000% scale: " + file_path);

