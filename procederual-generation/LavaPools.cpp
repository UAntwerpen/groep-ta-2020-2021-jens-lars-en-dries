//
// Created by syntaxnoob on 5/7/21.
//

#include <complex>
#include "LavaPools.h"

void LavaPools::Lava(std::vector<std::vector<char>> &map, int lava_pits, int seed) {
    // create random source
    Random random;
    if (seed != -1) random.setSeed(seed);

    // calculate height and width
    int height = map.size();
    int width = map[0].size();

    // loop over lava_pits amount
    for (int i = 0; i < lava_pits; i++) {
        // generate size of pit and coordinates
        int lava_pit_size = random.rand() % 3 + 1;
        int x_coordinate = random.rand() % (width - 2) + 1;
        int y_coordinate = random.rand() % (height - 2) + 1;
        // loop over the size, calculate dx and dy as displacement
        for (int j = 0; j < lava_pit_size; j++) {
            int dx = ((random.rand() % 2) * 2) - 1;
            int dy = ((random.rand() % 2) * 2) - 1;
            if (dy + y_coordinate < height and dx + x_coordinate < width and dy + y_coordinate >= 0 and
                dx + x_coordinate >= 0)
                map[dy + y_coordinate][dx + x_coordinate] = 'L';
            if (dy + y_coordinate < height and dx + x_coordinate + 1 < width and dy + y_coordinate >= 0 and
                dx + x_coordinate + 1 >= 0)
                map[dy + y_coordinate][dx + x_coordinate + 1] = 'L';
            if (dy + y_coordinate < height and dx + x_coordinate - 1 < width and dy + y_coordinate >= 0 and
                dx + x_coordinate - 1 >= 0)
                map[dy + y_coordinate][dx + x_coordinate - 1] = 'L';
            if (dy + y_coordinate + 1 < height and dx + x_coordinate < width and dy + y_coordinate + 1 >= 0 and
                dx + x_coordinate >= 0)
                map[dy + y_coordinate + 1][dx + x_coordinate] = 'L';
            if (dy + y_coordinate - 1 < height and dx + x_coordinate < width and dy + y_coordinate - 1 >= 0 and
                dx + x_coordinate >= 0)
                map[dy + y_coordinate - 1][dx + x_coordinate] = 'L';
        }
    }
}
