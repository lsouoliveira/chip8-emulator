#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <vector>

namespace Chip8 {

enum WrapMode {
    NONE,
    FULL,
    HALF,
    CIRCULAR
};

class Config {
private:
    int m_Cycles;
    WrapMode m_WrapMode;
    std::vector<std::string> m_KeyMapping;
public:
    Config() {}
    ~Config() {}

    const int& cycles() const { return m_Cycles; };
    void cycles(int cycles) { this->m_Cycles = cycles; };
    const WrapMode& wrap_mode() const { return m_WrapMode; };
    void wrap_mode(WrapMode wrap_mode) { this->m_WrapMode = wrap_mode; };
    const std::vector<std::string>& key_mapping() const { return m_KeyMapping; };
    void key_mapping(std::vector<std::string> key_mapping) { this->m_KeyMapping = key_mapping; };
};

}

#endif /* CONFIG_H */
