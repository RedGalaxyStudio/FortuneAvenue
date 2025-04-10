/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2025 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TGUI_CONTEXT_MENU_HPP
#define TGUI_CONTEXT_MENU_HPP

#include <TGUI/Widgets/MenuWidgetBase.hpp>
#include <TGUI/Renderers/ContextMenuRenderer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TGUI_MODULE_EXPORT namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Context menu widget
    ///
    /// @since TGUI 1.8
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API ContextMenu : public MenuWidgetBase
    {
    public:

        using Ptr = std::shared_ptr<ContextMenu>; //!< Shared widget pointer
        using ConstPtr = std::shared_ptr<const ContextMenu>; //!< Shared constant widget pointer

        static constexpr const char StaticWidgetType[] = "ContextMenu"; //!< Type name of the widget

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Constructor
        /// @param typeName     Type of the widget
        /// @param initRenderer Should the renderer be initialized? Should be true unless a derived class initializes it.
        /// @see create
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ContextMenu(const char* typeName = StaticWidgetType, bool initRenderer = true);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new menu bar widget
        ///
        /// @return The new menu bar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static ContextMenu::Ptr create();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another menu bar
        ///
        /// @param menuBar  The other menu bar
        ///
        /// @return The new menu bar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static ContextMenu::Ptr copy(const ContextMenu::ConstPtr& menuBar);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD ContextMenuRenderer* getSharedRenderer() override;
        TGUI_NODISCARD const ContextMenuRenderer* getSharedRenderer() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD ContextMenuRenderer* getRenderer() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the context menu is open
        ///
        /// The context menu will render nothing until it is opened.
        /// @see openMenu
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool isMenuOpen() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Opens the context menu at the position of this widget
        ///
        /// The context menu will render nothing until this function is called.
        /// Once the user clicked an item in the menu, the menu will be closed and you need to call this function again in order
        /// for the menu to become visible again.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void openMenu();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Opens the context menu at a certain position
        ///
        /// The context menu will render nothing until this function is called.
        /// Once the user clicked an item in the menu, the menu will be closed and you need to call this function again in order
        /// for the menu to become visible again.
        ///
        /// @see openMenuAtCursor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void openMenu(Vector2f position);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Opens the context menu at the last mouse cursor position
        ///
        /// The context menu will render nothing until this function is called.
        /// Once the user clicked an item in the menu, the menu will be closed and you need to call this function again in order
        /// for the menu to become visible again.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void openMenuAtMouseCursor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Closes the context menu if it was open
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void closeMenu() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the height of the items in the context menu
        ///
        /// @param itemHeight  The size of a single item in the context menu
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setItemHeight(float itemHeight);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the height of the items in the context menu
        ///
        /// @return The item height
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getItemHeight() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Connects a signal handler to the "MenuItemClicked" callback that will only be called when a specific
        ///        menu item was clicked.
        ///
        /// @param menuItem Menu item which should trigger the signal (assuming there are no submenus)
        /// @param handler  Callback function to call
        /// @param args     Optional extra arguments to pass to the signal handler when the signal is emitted
        ///
        /// @return Unique id of the connection
        ///
        /// The hierarchy does not need to exist yet and the signal will still exist when removing and readding the menu items.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename Func, typename... Args>
        unsigned int connectMenuItem(const String& menuItem, Func&& handler, const Args&... args)
        {
            return connectMenuItem(std::vector<String>{menuItem}, std::forward<Func>(handler), args...);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Connects a signal handler to the "MenuItemClicked" callback that will only be called when a specific
        ///        menu item was clicked.
        ///
        /// @param hierarchy Hierarchy of the menu items, ending with menu item that should trigger the signal when pressed
        /// @param handler   Callback function to call
        /// @param args      Optional extra arguments to pass to the signal handler when the signal is emitted
        ///
        /// @return Unique id of the connection
        ///
        /// The hierarchy does not need to exist yet and the signal will still exist when removing and readding the menu items.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename Func, typename... Args>
        unsigned int connectMenuItem(const std::vector<String>& hierarchy, Func&& handler, const Args&... args)
        {
#if defined(__cpp_lib_invoke) && (__cpp_lib_invoke >= 201411L)
            return onMenuItemClick.connect(
                [=](const std::vector<String>& clickedMenuItem)
                {
                    if (clickedMenuItem == hierarchy)
                        std::invoke(handler, args...);
                }
            );
#else
            return onMenuItemClick.connect(
                [f=std::function<void(const Args&...)>(handler),args...,hierarchy](const std::vector<String>& clickedMenuItem)
                {
                    if (clickedMenuItem == hierarchy)
                        f(args...);
                }
            );
#endif
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function is overriden to do nothing
        ///
        /// @param size  This parameter is ignored by this overriden function
        ///
        /// @warning The size of the ContextMenu can't be manually set! It depends on the items and the MinimumMenuWidth property.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Enables or disables the widget
        /// @param enabled  Is the widget enabled?
        ///
        /// The disabled widget will no longer receive events and thus no longer send callbacks.
        /// All widgets are enabled by default.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setEnabled(bool enabled) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new menu item to the menu
        ///
        /// @param text  The text written on this menu item
        ///
        /// @code
        /// contextMenu->addMenuItem("Cut");
        /// contextMenu->addMenuItem("Copy");
        /// contextMenu->addMenuItem("Paste");
        /// @endcode
        ///
        /// If the "-" string is given as menu item then a separator will appear instead of an item.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addMenuItem(const String& text);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new sub menu item
        ///
        /// @param hierarchy     Hierarchy of the menu items, ending with menu item to be added
        /// @param createParents Should the hierarchy be created if it did not exist yet?
        ///
        /// @return True when the item was added, false when createParents was false and the parents hierarchy does not exist
        ///         or if hierarchy is empty.
        ///
        /// @code
        /// contextMenu->addMenuItem({"Edit", "Undo"});
        /// contextMenu->addMenuItem({"Edit", "Redo"});
        /// @endcode
        ///
        /// If the "-" string is given as menu item then a separator will appear instead of an item.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool addMenuItem(const std::vector<String>& hierarchy, bool createParents = true);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of an existing menu item
        ///
        /// @param hierarchy Hierarchy of the menu items, ending with the menu item that is to be renamed
        /// @param text      The new text written on this menu item
        ///
        /// @return True when the menu item was renamed, false when the menu item was not found
        ///
        /// @code
        /// contextMenu->addMenuItem({"Edit", "Undo"});
        /// contextMenu->changeMenuItem({"Edit", "Undo"}, "Undo action");
        /// @endcode
        ///
        /// This function can also be used to rename items without submenus, by passing a hierarchy with only one element.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool changeMenuItem(const std::vector<String>& hierarchy, const String& text);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all menu items
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllMenuItems();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a menu item
        ///
        /// @param menuItem  The name of the menu item to remove
        ///
        /// @return True when the item was removed, false when menuItem was not found
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeMenuItem(const String& menuItem);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a sub menu item
        ///
        /// @param hierarchy  Hierarchy of the menu item, ending with menu item to be deleted
        /// @param removeParentsWhenEmpty  Also delete the parent of the deleted menu item if it has no other children
        ///
        /// @return True when the menu item existed and was removed, false when hierarchy was incorrect
        ///
        /// @code
        /// contextMenu->removeMenuItem({"Edit", "Undo"});
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeMenuItem(const std::vector<String>& hierarchy, bool removeParentsWhenEmpty = true);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a all menu items below a (sub) menu
        ///
        /// @param hierarchy Hierarchy of the menu item, ending with the sub menu containing the items
        ///
        /// @return True when the menu item existed and its children were removed, false when hierarchy was incorrect
        ///
        /// @code
        /// contextMenu->removeSubMenuItems({"File", "Recent files"});
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeSubMenuItems(const std::vector<String>& hierarchy);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Enable or disable a menu item
        /// @param menuItem  The name of the menu item to enable or disable
        /// @param enabled   Should the menu item be enabled or disabled?
        /// @return True when the menu item exists, false when menuItem was not found
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setMenuItemEnabled(const String& menuItem, bool enabled);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Enable or disable a menu item
        /// @param hierarchy  Hierarchy of menu items, ending with the menu item to enable/disable
        /// @param enabled    Should the menu item be enabled or disabled?
        /// @return True when the menu item exists, false when hierarchy was incorrect
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setMenuItemEnabled(const std::vector<String>& hierarchy, bool enabled);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Check if a menu item is enabled or disabled
        /// @param menuItem  The name of the menu item to check
        /// @return True if the menu item is enabled, false if it was disabled or when the menuItem did not exist
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool getMenuItemEnabled(const String& menuItem) const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Check if a menu item is enabled or disabled
        /// @param hierarchy  Hierarchy of menu items, ending with the menu item to check
        /// @return True if the menu item is enabled, false if it was disabled or when the hierarchy was incorrect
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool getMenuItemEnabled(const std::vector<String>& hierarchy) const;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the minimum width of the menus
        ///
        /// When a menu is displayed, the width will be either this or the width of the longest text in the menu.
        ///
        /// @param minimumWidth  minimum width of the menus
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMinimumMenuWidth(float minimumWidth);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the minimum width of the menus
        ///
        /// @return minimum width of the menus
        ///
        /// @see setMinimumMenuWidth
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getMinimumMenuWidth() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the menu items, including submenus
        /// @return List of menu items
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::vector<GetMenusElement> getMenuItems() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        ///
        /// @return Is the mouse on top of the widget?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool isMouseOnWidget(Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(BackendRenderTarget& target, RenderStates states) const override;

    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Name of the property that was changed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const String& property) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Called when the text size is changed (either by setTextSize or via the renderer)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateTextSize() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Widget::Ptr clone() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Triggers the onMenuItemClick callback
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void emitMenuItemClick(const std::vector<String>& hierarchy) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Returns the height of a normal menu item (i.e. not a separator). For a context menu this is the ItemHeight.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getDefaultMenuItemHeight() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Left mouse button was released while the menu might be open
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleasedOnMenu() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Is the mouse located on the opened menu?
        /// @param pos  Mouse position
        /// @return True if mouse on menu, false otherwise.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool isMouseOnOpenMenu(Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Mouse moved on top of the menu
        /// @param pos  Mouse position
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMovedOnMenu(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Deselects the selected item of the deepest open submenu
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deselectDeepestItem() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Called from OpenMenuPlaceholder to draw the menu that is currently open
        /// @param target Render target to draw to
        /// @param states Current render states
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void drawOpenMenu(BackendRenderTarget& target, RenderStates states) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        Menu m_menu;
        bool m_menuOpen = false;
        float m_itemHeight = 0;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CONTEXT_MENU_HPP
