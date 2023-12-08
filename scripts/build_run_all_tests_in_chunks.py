import subprocess # for executingshell commands
import itertools # for creating batches
from pprint import pprint
import re # for splitargstring
import shlex

p = subprocess.Popen("make list_test_objects", stdout=subprocess.PIPE, shell=True)

output = p.communicate()
stdout_data = output[0].decode("utf-8")
stderr_data = output[1] #.decode("utf-8")

tokens = stdout_data.split()

n = 50
batches = {}
for i, x in enumerate(tokens):
    batches.setdefault(i//n, []).append(x)

pprint(batches)




## build composite build commands

build_composite_obj_command_template = "ld -relocatable {objs_in_this_batch} -o {composite_obj_name_for_this_batch}"

individual_batch_commands = []
composite_obj_names = []
for i, batch in enumerate(batches):

    ## assemble the command for this batch

    print("================={i}=================".format(i=i))
    batch_name = "composite-{}.o".format(i)
    objs_in_this_batch = batches[i]
    build_composite_obj_command=build_composite_obj_command_template.format(
            objs_in_this_batch=' '.join(objs_in_this_batch), # objs_in_this_batch=' '.join(batch),
            composite_obj_name_for_this_batch=batch_name
            )
    #print(build_composite_obj_command)
    individual_batch_commands.append(build_composite_obj_command)
    composite_obj_names.append(batch_name)



## run the composite build commands

skip_obj_build = False;

for i, command in enumerate(individual_batch_commands):
    ## run the command
    print("=xxx============{i}=================".format(i=i))

    if skip_obj_build: continue;

    p = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output = p.communicate()
    stdout_data = output[0].decode("utf-8")
    stderr_data = output[1] #.decode("utf-8")
    print("=yyy============={i}=================".format(i=i))
    print(stdout_data)
    print(stderr_data)



## assemble the "run_all_tests" build command

composite_objs=' '.join(composite_obj_names)

build_run_all_tests_command_template="""g++ -g -std=c++17 -Wall -Wuninitialized -Weffc++ {COMPOSITE_OBJS} obj/tests/TestRunner.o -o bin/run_all_tests -I./include -lgmock -lgtest -I/home/Mark/Repos/googletest/googletest/include -I/home/Mark/Repos/googletest/googlemock/include -L/home/Mark/Repos/googletest/build/googlemock/gtest -I/home/Mark/Repos/asio/asio/include -L/home/Mark/Repos/allegro5/build/lib -I/usr/include -L. -lncurses -I/home/Mark/Repos/yaml-cpp/include -L/home/Mark/Repos/yaml-cpp/build -lyaml-cpp -lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro -lallegro_main -D_XOPEN_SOURCE_EXTENDED -lopengl32 -lwsock32 -lws2_32 -I/home/Mark/Repos/allegro_flare/include -L/home/Mark/Repos/allegro_flare/lib -lallegro_flare-0.8.11wip"""
build_run_all_tests_command=build_run_all_tests_command_template.format(COMPOSITE_OBJS=composite_objs)


## run the build "run_all_tests" command

print("building bin/run_all_tests...".format(i=i))
p = subprocess.Popen(build_run_all_tests_command, stdout=subprocess.PIPE, shell=True)
output = p.communicate()
stdout_data = output[0].decode("utf-8")
stderr_data = output[1] #.decode("utf-8")
print(stdout_data)
print(stderr_data)
print("...done".format(i=i))


