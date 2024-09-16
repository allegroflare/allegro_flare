/* 	Reverse Vertex Order by eishiya, last updated 15 Sep 2024

	Adds an action to the Object right-click menu that reverses the order
	of vertices in a Polygon. Does nothing for non-Polygon Objects.
	
	TODO: Disable the action when no Polygons are currently selected.
		This requires also watching for active asset changes, bleh.
*/

var reverseVertexOrder = tiled.registerAction("ReverseVertexOrder", function(action) {	
	let map = tiled.activeAsset;
	if(!map || !map.isTileMap)
		return;
	
	let objects = map.selectedObjects;
	if(!objects || objects.length < 1)
		return;
	
	map.macro("Reverse Vertex Order", function() {
		for(let obj of objects) {
			if(obj.shape == MapObject.Polygon && obj.polygon) {
				let oldPolygon = obj.polygon;
				let newPolygon = [oldPolygon[0]];
				for(let i = oldPolygon.length-1; i > 0; i--) {
					newPolygon.push(oldPolygon[i]);
				}
				obj.polygon = newPolygon;
			}
		}
	});

});
reverseVertexOrder.text = "Reverse Vertex Order";

//Add to the Objects right-click menu:
tiled.extendMenu("MapView.Objects", [
	{ action: "ReverseVertexOrder"}
]);
