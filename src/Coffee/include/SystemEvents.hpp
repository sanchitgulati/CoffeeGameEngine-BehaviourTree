#pragma once


namespace Coffee {
    enum class SystemEvents : int
    {
        WIN_EXIT = 1024,
        ON_MOUSE_DOWN,
        ON_MOUSE_UP,
        ON_MOUSE_MOVE,
        ON_MOUSE_SWIPE_UP,
        ON_MOUSE_SWIPE_DOWN,
        ON_MOUSE_SWIPE_RIGHT,
        ON_MOUSE_SWIPE_LEFT,
        CHANGE_SCENE,
        GENUS_REPLICATION,
        GENUS_DIE,
    };
}
