#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <iostream>
#include <vector>
#include <QMetaType>
class Preferences
{
private:
    int m_Cycles;
    int m_WrapMode;
    std::vector<char> m_KeyMapping;
public:
    Preferences() = default;
    ~Preferences() = default;
    Preferences(const Preferences &) = default;
    Preferences &operator=(const Preferences &) = default;
    Preferences(int cycles, int wrapMode, std::vector<char> keyMapping)
        : m_Cycles(cycles),
          m_WrapMode(wrapMode),
          m_KeyMapping(keyMapping)
    {};

    const int& cycles() const { return m_Cycles; }
    const int& wrap_mode() const { return m_WrapMode; }
    const std::vector<char>& key_mapping() const { return m_KeyMapping; }
};
Q_DECLARE_METATYPE (Preferences);
#endif // PREFERENCES_H
