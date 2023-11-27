import bpy

# Discussion from ChatGPT
# https://chat.openai.com/c/011ce426-1a70-4846-bb34-07a7dc1ca5a6

text = "GAME OVER"
font_path = "/Users/markoates/Repos/allegro_flare/bin/data/fonts/PathwayGothicOne-Regular.ttf"
extrude_depth = 0.25

# Clear existing mesh objects
bpy.ops.object.select_all(action='DESELECT')
# bpy.ops.object.select_by_type(type='MESH')
bpy.ops.object.delete()

# Create a new text object
bpy.ops.object.text_add(location=(0, 0, 0))
text_object = bpy.context.object

# Set the text content
text_object.data.body = text

# Set other properties if needed
text_object.location = (0, 0, 0)  # Set the location to the origin

# Load custom font
bpy.ops.font.open(filepath=font_path)

# Set the font for the text object
text_object.data.font = bpy.data.fonts.load(font_path)

# Rotate the text along the X-axis by 90 degrees
text_object.rotation_euler = (1.5708, 0, 0)  # 1.5708 radians is approximately 90 degrees

# Move the text horizontally for center alignment
text_object.location.x -= text_object.dimensions.x / 4

# Update the scene
bpy.context.view_layer.update()

# Convert the text object to a mesh
bpy.ops.object.convert(target='MESH')

# Enter edit mode
bpy.ops.object.mode_set(mode='EDIT')
bpy.ops.mesh.select_all(action='SELECT')

# Extrude the mesh by 0.25 meters
bpy.ops.mesh.extrude_region_move(TRANSFORM_OT_translate={"value":(0, extrude_depth, 0)})

# Exit edit mode
bpy.ops.object.mode_set(mode='OBJECT')

# Print a message to the console
print("Text object created at the origin with custom font.")

