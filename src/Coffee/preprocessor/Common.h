#pragma once

#define COFFEE_MAKE_SINGLETON(class)                                   \
public:                                                             \
    static auto& getInstance()                                      \
    {                                                               \
        static class instance;                                      \
        return instance;                                            \
    }                                                               \
                                                                    \
    class(const class&) = delete;                                   \
    const class& operator =(const class&) = delete;                 \
                                                                    \
private:                                                            \
    class() = default