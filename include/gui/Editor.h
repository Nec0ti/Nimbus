#pragma once

#include <memory>
#include <vector>
#include <string>
#include <functional>

#include "gui/Panel.h"
#include "gui/HierarchyPanel.h"
#include "gui/InspectorPanel.h"
#include "gui/SceneView.h"
#include "gui/GameView.h"
#include "gui/ProjectPanel.h"
#include "gui/ConsolePanel.h"
#include "gui/MenuBar.h"
#include "gui/Toolbar.h"
#include "gui/StatusBar.h"
#include "core/Scene.h"
#include "core/GameObject.h"

namespace Nimbus {

    class Panel;
    class HierarchyPanel;
    class InspectorPanel;
    class SceneView;
    class GameView;
    class ProjectPanel;
    class ConsolePanel;
    class MenuBar;
    class Toolbar;
    class StatusBar;
    class Scene;
    class GameObject;

    /**
     * @brief Main editor interface for the Nimbus Engine
     * 
     * The Editor class manages the Unity-style GUI interface, including
     * all panels, menus, toolbars, and user interactions. It provides
     * a comprehensive development environment for creating and editing
     * 3D scenes and game content.
     */
    class Editor {
    public:
        /**
         * @brief Editor configuration
         */
        struct Config {
            int width = 1920;
            int height = 1080;
            std::string title = "Nimbus Engine";
            bool enableDocking = true;
            bool enableImGuiDemo = false;
            std::string theme = "Dark"; // "Dark", "Light", "Classic"
            float fontSize = 16.0f;
            std::string fontPath = "assets/fonts/Roboto-Regular.ttf";
            bool enableAutoSave = true;
            int autoSaveInterval = 300; // seconds
        };

        /**
         * @brief Editor layout preset
         */
        enum class LayoutPreset {
            Default,
            Tall,
            Wide,
            GameDev,
            Cinematic,
            Custom
        };

        /**
         * @brief Constructor
         */
        Editor();

        /**
         * @brief Destructor
         */
        ~Editor();

        /**
         * @brief Initialize the editor
         * @param config Editor configuration
         * @return True if initialization was successful
         */
        bool Initialize(const Config& config = Config{});

        /**
         * @brief Shutdown the editor
         */
        void Shutdown();

        /**
         * @brief Update the editor for one frame
         * @param deltaTime Time since last frame
         */
        void Update(float deltaTime);

        /**
         * @brief Render the editor interface
         */
        void Render();

        /**
         * @brief Get the current configuration
         * @return Reference to the current configuration
         */
        const Config& GetConfig() const { return m_config; }

        /**
         * @brief Resize the editor window
         * @param width New width
         * @param height New height
         */
        void Resize(int width, int height);

        /**
         * @brief Set the active scene
         * @param scene Scene to set as active
         */
        void SetActiveScene(Scene* scene);

        /**
         * @brief Get the active scene
         * @return Pointer to the active scene
         */
        Scene* GetActiveScene() const { return m_activeScene; }

        /**
         * @brief Set the selected GameObject
         * @param gameObject GameObject to select
         */
        void SetSelectedGameObject(GameObject* gameObject);

        /**
         * @brief Get the selected GameObject
         * @return Pointer to the selected GameObject
         */
        GameObject* GetSelectedGameObject() const { return m_selectedGameObject; }

        /**
         * @brief Get the hierarchy panel
         * @return Pointer to the hierarchy panel
         */
        HierarchyPanel* GetHierarchyPanel() const { return m_hierarchyPanel.get(); }

        /**
         * @brief Get the inspector panel
         * @return Pointer to the inspector panel
         */
        InspectorPanel* GetInspectorPanel() const { return m_inspectorPanel.get(); }

        /**
         * @brief Get the scene view
         * @return Pointer to the scene view
         */
        SceneView* GetSceneView() const { return m_sceneView.get(); }

        /**
         * @brief Get the game view
         * @return Pointer to the game view
         */
        GameView* GetGameView() const { return m_gameView.get(); }

        /**
         * @brief Get the project panel
         * @return Pointer to the project panel
         */
        ProjectPanel* GetProjectPanel() const { return m_projectPanel.get(); }

        /**
         * @brief Get the console panel
         * @return Pointer to the console panel
         */
        ConsolePanel* GetConsolePanel() const { return m_consolePanel.get(); }

        /**
         * @brief Get the menu bar
         * @return Pointer to the menu bar
         */
        MenuBar* GetMenuBar() const { return m_menuBar.get(); }

        /**
         * @brief Get the toolbar
         * @return Pointer to the toolbar
         */
        Toolbar* GetToolbar() const { return m_toolbar.get(); }

        /**
         * @brief Get the status bar
         * @return Pointer to the status bar
         */
        StatusBar* GetStatusBar() const { return m_statusBar.get(); }

        /**
         * @brief Add a custom panel
         * @param panel Panel to add
         */
        void AddPanel(std::shared_ptr<Panel> panel);

        /**
         * @brief Remove a custom panel
         * @param panel Panel to remove
         */
        void RemovePanel(std::shared_ptr<Panel> panel);

        /**
         * @brief Get all custom panels
         * @return Vector of custom panels
         */
        const std::vector<std::shared_ptr<Panel>>& GetCustomPanels() const { return m_customPanels; }

        /**
         * @brief Set the layout preset
         * @param preset Layout preset to apply
         */
        void SetLayoutPreset(LayoutPreset preset);

        /**
         * @brief Save the current layout
         * @param filepath Path to save the layout to
         * @return True if save was successful
         */
        bool SaveLayout(const std::string& filepath);

        /**
         * @brief Load a layout from file
         * @param filepath Path to load the layout from
         * @return True if load was successful
         */
        bool LoadLayout(const std::string& filepath);

        /**
         * @brief Reset the layout to default
         */
        void ResetLayout();

        /**
         * @brief Show or hide a panel
         * @param panelName Name of the panel
         * @param visible True to show the panel
         */
        void SetPanelVisible(const std::string& panelName, bool visible);

        /**
         * @brief Check if a panel is visible
         * @param panelName Name of the panel
         * @return True if the panel is visible
         */
        bool IsPanelVisible(const std::string& panelName) const;

        /**
         * @brief Focus a panel
         * @param panelName Name of the panel to focus
         */
        void FocusPanel(const std::string& panelName);

        /**
         * @brief Get the focused panel
         * @return Name of the focused panel
         */
        std::string GetFocusedPanel() const { return m_focusedPanel; }

        /**
         * @brief Set the editor theme
         * @param theme Theme name
         */
        void SetTheme(const std::string& theme);

        /**
         * @brief Get the current theme
         * @return Current theme name
         */
        const std::string& GetTheme() const { return m_config.theme; }

        /**
         * @brief Set the font size
         * @param size Font size
         */
        void SetFontSize(float size);

        /**
         * @brief Get the font size
         * @return Font size
         */
        float GetFontSize() const { return m_config.fontSize; }

        /**
         * @brief Enable or disable auto-save
         * @param enabled True to enable auto-save
         */
        void SetAutoSave(bool enabled) { m_config.enableAutoSave = enabled; }

        /**
         * @brief Check if auto-save is enabled
         * @return True if auto-save is enabled
         */
        bool IsAutoSaveEnabled() const { return m_config.enableAutoSave; }

        /**
         * @brief Set the auto-save interval
         * @param interval Auto-save interval in seconds
         */
        void SetAutoSaveInterval(int interval) { m_config.autoSaveInterval = interval; }

        /**
         * @brief Get the auto-save interval
         * @return Auto-save interval in seconds
         */
        int GetAutoSaveInterval() const { return m_config.autoSaveInterval; }

        /**
         * @brief Perform auto-save
         */
        void AutoSave();

        /**
         * @brief Show a modal dialog
         * @param title Dialog title
         * @param message Dialog message
         * @param type Dialog type
         * @return User response
         */
        enum class DialogType {
            Info,
            Warning,
            Error,
            Question,
            YesNo,
            YesNoCancel
        };

        enum class DialogResult {
            OK,
            Cancel,
            Yes,
            No
        };

        DialogResult ShowDialog(const std::string& title, const std::string& message, DialogType type = DialogType::Info);

        /**
         * @brief Show a file dialog
         * @param title Dialog title
         * @param filters File filters
         * @param defaultPath Default path
         * @return Selected file path
         */
        std::string ShowFileDialog(const std::string& title, const std::vector<std::string>& filters, const std::string& defaultPath = "");

        /**
         * @brief Show a folder dialog
         * @param title Dialog title
         * @param defaultPath Default path
         * @return Selected folder path
         */
        std::string ShowFolderDialog(const std::string& title, const std::string& defaultPath = "");

        /**
         * @brief Show a color picker
         * @param title Dialog title
         * @param initialColor Initial color
         * @return Selected color
         */
        glm::vec4 ShowColorPicker(const std::string& title, const glm::vec4& initialColor = glm::vec4(1.0f));

        /**
         * @brief Register a menu item
         * @param menu Menu name
         * @param item Item name
         * @param callback Callback function
         */
        void RegisterMenuItem(const std::string& menu, const std::string& item, std::function<void()> callback);

        /**
         * @brief Unregister a menu item
         * @param menu Menu name
         * @param item Item name
         */
        void UnregisterMenuItem(const std::string& menu, const std::string& item);

        /**
         * @brief Register a toolbar button
         * @param name Button name
         * @param icon Icon path
         * @param tooltip Tooltip text
         * @param callback Callback function
         */
        void RegisterToolbarButton(const std::string& name, const std::string& icon, const std::string& tooltip, std::function<void()> callback);

        /**
         * @brief Unregister a toolbar button
         * @param name Button name
         */
        void UnregisterToolbarButton(const std::string& name);

        /**
         * @brief Register a keyboard shortcut
         * @param name Shortcut name
         * @param key Key code
         * @param modifiers Key modifiers
         * @param callback Callback function
         */
        void RegisterShortcut(const std::string& name, int key, int modifiers, std::function<void()> callback);

        /**
         * @brief Unregister a keyboard shortcut
         * @param name Shortcut name
         */
        void UnregisterShortcut(const std::string& name);

        /**
         * @brief Get editor statistics
         * @return Editor statistics
         */
        struct EditorStats {
            int frameCount = 0;
            float frameTime = 0.0f;
            float renderTime = 0.0f;
            float guiTime = 0.0f;
            int drawCalls = 0;
            int vertices = 0;
            int triangles = 0;
        };

        /**
         * @brief Get the current editor statistics
         * @return Current editor statistics
         */
        const EditorStats& GetEditorStats() const { return m_editorStats; }

        /**
         * @brief Reset editor statistics
         */
        void ResetEditorStats();

    private:
        // Configuration
        Config m_config;

        // Core panels
        std::unique_ptr<HierarchyPanel> m_hierarchyPanel;
        std::unique_ptr<InspectorPanel> m_inspectorPanel;
        std::unique_ptr<SceneView> m_sceneView;
        std::unique_ptr<GameView> m_gameView;
        std::unique_ptr<ProjectPanel> m_projectPanel;
        std::unique_ptr<ConsolePanel> m_consolePanel;

        // UI elements
        std::unique_ptr<MenuBar> m_menuBar;
        std::unique_ptr<Toolbar> m_toolbar;
        std::unique_ptr<StatusBar> m_statusBar;

        // Custom panels
        std::vector<std::shared_ptr<Panel>> m_customPanels;

        // Scene data
        Scene* m_activeScene = nullptr;
        GameObject* m_selectedGameObject = nullptr;

        // UI state
        std::string m_focusedPanel;
        bool m_layoutDirty = true;
        float m_autoSaveTimer = 0.0f;

        // Statistics
        EditorStats m_editorStats;

        // Callbacks
        std::unordered_map<std::string, std::unordered_map<std::string, std::function<void()>>> m_menuCallbacks;
        std::unordered_map<std::string, std::function<void()>> m_toolbarCallbacks;
        std::unordered_map<std::string, std::function<void()>> m_shortcutCallbacks;

        /**
         * @brief Initialize ImGui
         * @return True if initialization was successful
         */
        bool InitializeImGui();

        /**
         * @brief Shutdown ImGui
         */
        void ShutdownImGui();

        /**
         * @brief Setup ImGui style
         */
        void SetupImGuiStyle();

        /**
         * @brief Load ImGui font
         * @return True if font was loaded successfully
         */
        bool LoadImGuiFont();

        /**
         * @brief Setup ImGui docking
         */
        void SetupImGuiDocking();

        /**
         * @brief Create default layout
         */
        void CreateDefaultLayout();

        /**
         * @brief Update auto-save timer
         * @param deltaTime Time since last frame
         */
        void UpdateAutoSave(float deltaTime);

        /**
         * @brief Process input events
         */
        void ProcessInput();

        /**
         * @brief Process keyboard shortcuts
         */
        void ProcessShortcuts();

        /**
         * @brief Render the main menu bar
         */
        void RenderMenuBar();

        /**
         * @brief Render the toolbar
         */
        void RenderToolbar();

        /**
         * @brief Render the status bar
         */
        void RenderStatusBar();

        /**
         * @brief Render all panels
         */
        void RenderPanels();

        /**
         * @brief Render custom panels
         */
        void RenderCustomPanels();

        /**
         * @brief Render dialogs
         */
        void RenderDialogs();
    };

} // namespace Nimbus