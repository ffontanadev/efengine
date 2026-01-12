#include "core/Application.h"

int main() {
    efengine::Application app;

    if (!app.Initialize()) {
        return -1;
    }

    app.Run();
    app.Shutdown();

    return 0;
}