#!/bin/bash

# Define an array of error maps
error_maps=("test_maps/error_maps/invalid_spawn.cub" "test_maps/error_maps/invalid_texture_path.cub" "test_maps/error_maps/map_at_middle.cub" "test_maps/error_maps/map_at_top.cub" "test_maps/error_maps/no_floor_color.cub" "test_maps/error_maps/no_map.cub" "test_maps/error_maps/no_texture.cub" "test_maps/error_maps/no_walls.cub" "test_maps/error_maps/too_many_colors.cub" "test_maps/error_maps/too_many_textures.cub" "test_maps/error_maps/walls_dont_connect.cub" "test_maps/error_maps/wrong_extension.cuub")

overall_result=0

# Loop through the error maps and test each one
clear
for map in "${error_maps[@]}"; do
    # Run the program and capture its output
    output="$(./cub3d "$map" 2>&1)"
    exit_code="$?"

    # Print the map name in light blue and its exit status in light red
	printf "\e[1;34m%-50s \e[91m--- exit status %d\n\e[0m" "$map" "$exit_code"

    # Print the program's output, clear the screen, and wait briefly
    echo -e "\n$output\n"
    sleep 1

    # Check if the exit code is zero (indicating success)
    if [ "$exit_code" -eq 0 ]; then
        overall_result=1
    fi
done

# Print the overall result
if [ "$overall_result" -eq 1 ]; then
    printf "\e[91mAt least one map passed when it should have failed.\e[0m"
else
    printf "\e[32mAll maps failed as expected.\e[0m\n"
fi

# Exit with the overall result
exit "$overall_result"