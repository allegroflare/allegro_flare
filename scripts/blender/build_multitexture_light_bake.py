import bpy
import os


# Note this scirpt is a work in progress. For more logged progress, see
# Graphics Pipeline Project: https://docs.google.com/document/d/1K1_udKoOvxrEhKN3KGCpx1voeLBvsIbNK11HH7neNY4/edit#heading=h.uv8wkjkw00ak
# TileFPS document: https://docs.google.com/document/d/1EIp_EFMlWCGFnwEc5-RIP08dAt03p-qePHlrbRf2kGw/edit

# Deselect all objects in the scene

bpy.ops.object.select_all(action='DESELECT')



# Import the obj

bpy.ops.import_scene.obj(filepath="/Users/markoates/Desktop/world-02.obj")
imported_obj = bpy.context.selected_objects[0]

print("--- imported object START ---")
print(imported_obj)
print("--- imported object END ---")

# Select the newly imported object
imported_obj.select_set(True)
bpy.context.view_layer.objects.active = imported_obj


print("AAAAAAAAAAAAAAAA")



# Rename the current UV set

light_uvlayer_name = 'light-uv'
light_uv = bpy.context.active_object.data.uv_layers['UVMap']
light_uv.name = light_uvlayer_name

# Create a new UV set

color_uvlayer_name = 'color-uv'
color_uv = bpy.context.active_object.data.uv_layers.new(name=color_uvlayer_name)
## TODO: Confirm the light uv is selected for the projection below
#bpy.context.object.data.uv_layers[light_uvlayer_name].active = True

print("BBBBBBBBBBBBBBBBB")


# Smart project on the object
# smart_project in docs https://docs.blender.org/api/current/bpy.ops.uv.html#bpy.ops.uv.smart_project
# smart_project(angle_limit=1.15192, margin_method='SCALED', island_margin=0.0, area_weight=0.0, correct_aspect=True, scale_to_bounds=False)
bpy.ops.object.mode_set(mode='EDIT')
bpy.ops.mesh.select_all(action='SELECT')
bpy.ops.uv.smart_project(island_margin=0.001) # 0.001 for 2048, 0.01 for 1024 textures
bpy.ops.object.mode_set(mode='OBJECT')


print("CCCCCCCCCCCCCCCCC")

# Setup the render pipeline
# Cycles render settings: https://docs.blender.org/api/2.80/bpy.types.CyclesRenderSettings.html
bpy.context.scene.render.engine = 'CYCLES'
bpy.context.scene.cycles.device = 'GPU'
bpy.context.scene.cycles.bake_type = 'AO'


print("DDDDDDDDDDDDDDDDD")


# Create the ao bake image
# ao_bake_image = bpy.ops.image.new(name='ao-bake', width=1024, height=1024, color=(0.0, 0.0, 0.0, 1.0), alpha=True, generated_type='BLANK', float=False, use_stereo_3d=False, tiled=False)


# Export the scene

## TODO: Use the "blend_file_path"
# blend_file_path = bpy.data.filepath
# directory = os.path.dirname(blend_file_path)
# target_file = os.path.join(directory, 'myfile.obj')
print("EEEEEEEEEEEEEEEEE")


light_uv.active = True ## Crash occurs here

"""
target_file = os.path.join("/Users/markoates/Desktop/", "myfile-light_uvs.obj")
bpy.ops.export_scene.obj(
 filepath=target_file,
 check_existing=False,
 axis_forward='-Z',
 axis_up='Y',
 filter_glob="*.obj;*.mtl",
 use_selection=False,
 use_animation=False,
 use_mesh_modifiers=True,
 use_edges=True,
 use_smooth_groups=False,
 use_smooth_groups_bitflags=False,
 use_normals=True,
 use_uvs=True,
 use_materials=True,
 use_triangles=False,
 use_nurbs=False,
 use_vertex_groups=False,
 use_blen_objects=True,
 group_by_object=False,
 group_by_material=False,
 keep_vertex_order=True, #Changed from default
 global_scale=1,
 path_mode='AUTO'
)
"""

"""
color_uv.active = True

target_file = os.path.join("/Users/markoates/Desktop/", "myfile-base_texture.obj")
bpy.ops.export_scene.obj(
 filepath=target_file,
 check_existing=False,
 axis_forward='-Z',
 axis_up='Y',
 filter_glob="*.obj;*.mtl",
 use_selection=False,
 use_animation=False,
 use_mesh_modifiers=True,
 use_edges=True,
 use_smooth_groups=False,
 use_smooth_groups_bitflags=False,
 use_normals=True,
 use_uvs=True,
 use_materials=False, #Changed from default
 use_triangles=False,
 use_nurbs=False,
 use_vertex_groups=False,
 use_blen_objects=True,
 group_by_object=False,
 group_by_material=False,
 keep_vertex_order=True, #Changed from default
 global_scale=1,
 path_mode='AUTO'
)
"""



# Bake the texture

# TODO: bpy.ops.object.bake()


