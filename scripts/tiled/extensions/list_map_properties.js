


function myCustomFunction()
{
  // Get the currently active map
  var map = tiled.activeAsset;

  // Check if a map is open
  if (map !== null && map.isTileMap) {
      var properties = map.properties();
      // Display map custom properties
      //tiled.log("=== Map Custom Properties " + properties.length + " ===");
      //for (var propName in map.properties) {
          //tiled.log(propName + ": " + map.property(propName));
      //}

      for (var propName in properties) {
          tiled.log(propName + ": " + properties[propName]);
      }

      //// Specify the path to your custom rules map file
      //var rulesMapPath = "path/to/your/custom_rules_map.tmx";

      //// Check if the custom rules map file exists
      //var rulesMap = new TiledMap(rulesMapPath);
      //if (rulesMap !== null) {
          //// Perform autoMap using the custom rules map
          //map.autoMap(rulesMap);

          //// Output a message indicating success
          //console.log("AutoMap successfully applied using custom rules map.");
      //} else {
          //// Output an error message if the custom rules map file doesn't exist
          //console.error("Error: Custom rules map not found at " + rulesMapPath);
      //}
  } else {
      // Output an error message if no map is open
      tiled.log("Error: No tile map is currently open in Tiled.");
  }


      tiled.alert("Foobar", "boobaz");

}




var tool = tiled.registerTool("PlaceRectangles", {
    name: "Place Rectangles",

    mousePressed: function(button, x, y, modifiers) {
      myCustomFunction();
    },
})




/*
// Create a new action (button) with a unique ID
var action = tiled.createQAction({
    text: "Custom Button",
    icon: "path/to/your/icon.png", // Replace with the path to your icon
    onTriggered: myCustomFunction // Call the explicitly defined function
});

// Add the action to the toolbar
tiled.addMenuAction(action);

// Output a message indicating success
console.log("Custom button added to the toolbar.");
*/



