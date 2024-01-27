import bpy
import math

# Discussion from ChatGPT
# https://chat.openai.com/c/011ce426-1a70-4846-bb34-07a7dc1ca5a6

# HOW TO USE
# 1) Run like:
#    /Applications/Blender.app/Contents/MacOS/blender -b -P /Users/markoates/Repos/allegro_flare/scripts/blender/generate_3d_text.py
# 2) To view the output
#    /Users/markoates/Repos/allegro_flare/bin/programs/basic_3d_allegro_flare ~/Desktop/text_3d_model.obj /Users/markoates/Repos/allegro_flare/bin/data/bitmaps/test_texture.png
# 3) Convert the generated UV layout SVG to a PNG
#    convert "the_uv_texture.svg" "the_uv_texture.png"


text = "420"
font_path = "/Users/markoates/Repos/allegro_flare/bin/data/fonts/Oswald-Medium.ttf"
#font_path = "/Users/markoates/Repos/allegro_flare/bin/data/fonts/PathwayGothicOne-Regular.ttf"
#font_path = "/Users/markoates/Stuff/September 4 2021/EurostileBQ-BoldExtended.otf"
extrude_depth = 0.1
output_path = "/Users/markoates/Desktop/" + text.lower() + "-text_3d_model.obj"  # Specify the desired output path
output_path_uv_projected = "/Users/markoates/Desktop/" + text.lower() + "-text_3d_model-uv.obj"  # Specify the desired output path
output_path_uv_map = "/Users/markoates/Desktop/" + text.lower() + "-text_uv_layout"  # Specify the desired output path



### Create the projection

# Clear existing mesh objects (the default cube and other objects)
bpy.ops.object.select_all(action='SELECT')
# bpy.ops.object.select_by_type(type='MESH')
bpy.ops.object.delete()

# Deselect everything
bpy.ops.object.select_all(action='DESELECT')

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

# Select the vertices of the object
obj = bpy.context.active_object
bpy.context.view_layer.objects.active = obj
obj.select_set(True)
bpy.ops.object.mode_set(mode='EDIT')
bpy.ops.mesh.select_all(action='SELECT')

# Do a "Smart UV Project" projection
#   https://docs.blender.org/api/current/bpy.ops.uv.html#bpy.ops.uv.smart_project
#   defaults:
#   angle_limit=1.15192, margin_method='SCALED', island_margin=0.0, area_weight=0.0, correct_aspect=True, scale_to_bounds=False
bpy.ops.uv.smart_project(
      angle_limit=math.radians(66),
      #angle_limit=0.523598775598299, # 0.523598775598299 is 1/2 pi / 3, or 66 degrees
      island_margin=0.005,
      area_weight=0.0,
      correct_aspect=True,
      scale_to_bounds=False
   )

# Save the UV layout to a file on the desktop
# Note that PNG is not supported in headless mode, but an SVG can be exported as well
bpy.ops.uv.export_layout(filepath=output_path_uv_map, mode='SVG', size=(1024*2, 1024*2))

# Save the obj model with the new UV layout to a file on the desktop
bpy.ops.export_scene.obj(filepath=output_path_uv_projected, use_selection=True, use_materials=False)



### Tell the user next steps:

print("");
print("To convert the SVG to PNG:");
print("convert \"" + output_path_uv_map + ".svg\" \"" + output_path_uv_map + ".png\"");

print("");
print("To view:");
print("/Users/markoates/Repos/allegro_flare/bin/programs/basic_3d_scene \"" + output_path_uv_projected + "\" /Users/markoates/Repos/allegro_flare/bin/data/bitmaps/test_texture.png");
print("Or, with the generated UV texture:");
print("/Users/markoates/Repos/allegro_flare/bin/programs/basic_3d_scene \"" + output_path_uv_projected + "\" \"" + output_path_uv_map + ".png\"");

