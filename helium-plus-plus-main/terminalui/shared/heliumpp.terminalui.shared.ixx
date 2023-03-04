/*
* Helium++ is a customizable extension system for Minecraft server.
* You can get the latest source code and releases of Helium++ at :
* https://github.com/Helium-DevTeam/helium-plus-plus
* ----------------------------------------------------------------------------------------
* Helium++ Copyright (C) 2021-2023 Helium-DevTeam
*
* This file is a part of Helium++
*
* Helium++ is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium++ is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium++.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

module;

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

export module heliumpp.terminalui.shared;

import heliumpp.shared;

using namespace std;
using namespace ftxui;

export namespace helium {
    class ScrollerBase : public ComponentBase {
    public:
        explicit ScrollerBase(Component child) {
            Add(std::move(child));
        }

    private:
        Element Render() final {
            auto focused = Focused() ? focus : ftxui::select;

            Element background = ComponentBase::Render();
            background->ComputeRequirement();
            size_ = background->requirement().min_y;

            // Values a bit hardcoded for bordered window, should be -0 and -2 if no border is used.
            min_selected_ = int(box_.y_max / 2) - 1;
            max_selected_ = size_ - int(box_.y_max / 2) - 1;
            if (selected_ == 0) {
                selected_ = min_selected_;
            }

            return dbox({
                       std::move(background),
                       vbox({
                           text("") | size(HEIGHT, EQUAL, selected_),
                           text("") | focused,
                       }),
                }) |
                vscroll_indicator | yframe | yflex | reflect(box_);
        }

        bool OnEvent(Event event) final {
            if (event.is_mouse() && box_.Contain(event.mouse().x, event.mouse().y))
                TakeFocus();

            int selected_old = selected_;
            if (event == Event::ArrowUp || event == Event::Character('k') ||
                (event.is_mouse() && event.mouse().button == Mouse::WheelUp)) {
                selected_--;
            }
            if ((event == Event::ArrowDown || event == Event::Character('j') ||
                (event.is_mouse() && event.mouse().button == Mouse::WheelDown))) {
                selected_++;
            }
            if (event == Event::PageDown)
                selected_ += box_.y_max - box_.y_min;
            if (event == Event::PageUp)
                selected_ -= box_.y_max - box_.y_min;
            if (event == Event::Home)
                selected_ = 0;
            if (event == Event::End)
                selected_ = size_;

            if (selected_ < min_selected_) {
                selected_ = min_selected_;
            }
            if (selected_ > max_selected_) {
                selected_ = max_selected_;
            }

            selected_ = std::max(0, std::min(size_ - 1, selected_));
            return selected_old != selected_;
        }

        [[nodiscard]] bool Focusable() const final {
            return true;
        }

        int min_selected_ = 0;
        int max_selected_ = 0;
        int selected_ = 0;
        int size_ = 0;
        Box box_;
    };

    Component Scroller(Component child) {
        return Make<ScrollerBase>(std::move(child));
    }

    Component Window(std::string title, Component component) {
        return Renderer(component, [component, title] {  //
            return window(text(title), component->Render()) | flex;
            });
    }
}