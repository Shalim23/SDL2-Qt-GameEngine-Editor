#pragma once

#ifdef EDITOR

#include <QtWidgets/QApplication>
#include "Engine/Engine.h"

class Editor final
{
public:
    Editor(int argc, char* argv[]);
    ~Editor() = default;
    Editor(const Editor&) = delete;
    Editor(Editor&&) = delete;
    Editor& operator=(const Editor&) = delete;
    Editor& operator=(Editor&&) = delete;

    void init();
    int run();

private:
    QApplication app_;
};
#endif