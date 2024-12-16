#ifdef EDITOR
#include "Editor/Editor.h"
#include <QtWidgets/QPushButton>

Editor::Editor(int argc, char* argv[])
    : app_{argc, argv}
{

}

void Editor::init()
{

}

int Editor::run()
{
    QPushButton button("Hello, World!");
    button.resize(200, 60);
    button.show();

    return app_.exec();
}

#endif
