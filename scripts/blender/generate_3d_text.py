import bpy

# Discussion from ChatGPT
# https://chat.openai.com/c/011ce426-1a70-4846-bb34-07a7dc1ca5a6

# HOW TO USE
# 1) With blender running, run like:
#    /Applications/Blender.app/Contents/MacOS/blender -b -P /Users/markoates/Repos/allegro_flare/scripts/blender/generate_3d_text.py
# 2) To view the output
#    /Users/markoates/Repos/allegro_flare/bin/programs/basic_3d_allegro_flare ~/Desktop/text_3d_model.obj /Users/markoates/Repos/allegro_flare/bin/data/bitmaps/test_texture.png


text = "CAT TREAT CATCH"
font_path = "/Users/markoates/Repos/allegro_flare/bin/data/fonts/PathwayGothicOne-Regular.ttf"
#font_path = "/Users/markoates/Stuff/September 4 2021/EurostileBQ-BoldExtended.otf"
extrude_depth = 0.1
output_path = "/Users/markoates/Desktop/" + text.lower() + "-text_3d_model.obj"  # Specify the desired output path
output_path_uv_projected = "/Users/markoates/Desktop/" + text.lower() + "-text_3d_model-uv.obj"  # Specify the desired output path
output_path_uv_map = "/Users/markoates/Desktop/" + text.lower() + "-text_uv_layout.png"  # Specify the desired output path

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

bpy.ops.export_scene.obj(filepath=output_path, use_selection=True, use_materials=False)

# Print a message to the console
print("Text object created at the origin with custom font.")



### Improve the UV mapping and generate a UV texture

# bpy.ops.object.select_all(action='SELECT')
bpy.ops.object.editmode_toggle()

# # Do the projection
# TODO: This needs to be changed to smart project with the correct settings
# bpy.ops.uv.smart_project()

# # Save the UV layout to a file on the desktop
# bpy.ops.uv.export_layout(filepath=output_path_uv_map, size=(1024, 1024))

# # Save the UV layout to a file on the desktop
# bpy.ops.export_scene.obj(filepath=output_path_uv_projected, use_selection=True, use_materials=False)

