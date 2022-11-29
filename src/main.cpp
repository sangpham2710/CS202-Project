<<<<<<< HEAD
#include <iostream>
#include <stdexcept>

#include "Application.h"

int main() {
    try {
        Application app;
        app.run();
    } catch (std::exception& e) {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
    return 0;
}
=======
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2022 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

bool runExample(tgui::BackendGui& gui)
{
    return true;
}

int main()
{
    sf::RenderWindow window{ {800, 600}, "TGUI example - SFML_GRAPHICS backend" };

    tgui::Gui gui{window};
    if (runExample(gui))
        gui.mainLoop();
}// subject to the following restrictions:
>>>>>>> tgui
