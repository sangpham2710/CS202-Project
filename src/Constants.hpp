#pragma once

#include <vector>

class Constants {
   public:
    static constexpr int SCREEN_WIDTH = 1024;
    static constexpr int SCREEN_HEIGHT = 768;
    static constexpr int BLOCK_SIZE = 64;
    static constexpr int LANE_HEIGHT = 64;
    static constexpr int LANE_WIDTH = SCREEN_WIDTH;
    static constexpr int NUM_LANES = 12;
    static constexpr float MOVE_ANIMATION_DURATION = 0.2f;
    static constexpr int CHARACTER_HITBOX_WIDTH = 32;
    static constexpr int CHARACTER_HITBOX_HEIGHT = 40;
    static constexpr int OBSTACLE_HITBOX_WIDTH_OFFSET = 24;
    static constexpr int OBSTACLE_HITBOX_HEIGHT_OFFSET = 24;
    static constexpr float RED_LIGHT_DURATION = 3;
    static constexpr float YELLOW_LIGHT_DURATION = 3;
    static constexpr float GREEN_LIGHT_DURATION = 7;
    static constexpr float OBSTACLE_GAP = 32;
};