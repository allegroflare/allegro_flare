

function myCustomFunction()
{
  // Get the currently active map
  var map = tiled.activeAsset;

  // Check if a map is open
  if (map !== null && map.isTileMap) {
      var properties = map.resolvedProperties();

      // Interate through the properties and locate "AutomappingStyle"
      for (var propName in properties) {
         var enum_value = properties[propName].value;
         tiled.log(propName + ": " + enum_value);

         if (propName == "AutomappingStyle")
         {
            //tiled.log("value: " + properties[propName].value);
            if (enum_value === 0)
            {
               tiled.log("Applying forest tilemap rules");
               var rules_file = "/Users/markoates/Repos/SomePlatformer/bin/data/maps/fantasy_forest_rules/rules.txt"
               map.autoMap(rules_file);
            }
            if (enum_value === 1)
            {
               tiled.log("Applying caves tilemap rules");
               var rules_file = "/Users/markoates/Repos/SomePlatformer/bin/data/maps/fantasy_caves_rules/rules.txt"
               map.autoMap(rules_file);
            }
         }
      }

  } else {
      // Output an error message if no map is open
      tiled.log("Error: No tile map is currently open in Tiled.");
  }
}


var tool = tiled.registerTool("ApplyAutomappingStyle", {
    name: "ApplyAutomappingStyle",

    mousePressed: function(button, x, y, modifiers) {
      myCustomFunction();
    },
})


