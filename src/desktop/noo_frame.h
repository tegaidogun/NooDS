/*
    Copyright 2019-2025 Hydr8gon

    This file is part of NooDS.

    NooDS is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    NooDS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with NooDS. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <wx/wx.h>
#include <wx/joystick.h>

#include "../core.h"

class NooApp;
class NooCanvas;

class NooFrame: public wxFrame {
public:
    NooCanvas *canvas;
    NooFrame *partner;
    bool mainFrame;

    Core *core = nullptr;
    bool running = false;

    NooFrame(NooApp *app, int id = 0, std::string path = "", NooFrame *partner = nullptr);
    ~NooFrame();
    void Refresh();

    void startCore(bool full);
    void stopCore(bool full);

    void pressKey(int key);
    void releaseKey(int key);

private:
    NooApp *app;
    wxMenu *fileMenu, *systemMenu;
    wxJoystick *joystick;
    wxTimer *timer;
    int id;

    std::string ndsPath, gbaPath;
    std::thread *coreThread = nullptr, *saveThread = nullptr;
    std::condition_variable cond;
    std::mutex mutex;

    std::vector<int> axisBases;
    uint8_t hotkeyToggles = 0;
    int fpsLimiterBackup = 0;
    bool fullScreen = false;

    void runCore();
    void checkSave();
    void loadRomPath(std::string path);

    void loadRom(wxCommandEvent &event);
    void bootFirmware(wxCommandEvent &event);
    void saveState(wxCommandEvent &event);
    void loadState(wxCommandEvent &event);
    void trimRom(wxCommandEvent &event);
    void changeSave(wxCommandEvent &event);
    void quit(wxCommandEvent &event);
    void pause(wxCommandEvent &event);
    void restart(wxCommandEvent &event);
    void stop(wxCommandEvent &event);
    void actionReplay(wxCommandEvent &event);
    void addSystem(wxCommandEvent &event);
    void directBoot(wxCommandEvent &event);
    void romInRam(wxCommandEvent &event);
    void fpsLimiter(wxCommandEvent &event);
    template <int> void frameskip(wxCommandEvent &event);
    void threaded2D(wxCommandEvent &event);
    template <int> void threaded3D(wxCommandEvent &event);
    void highRes3D(wxCommandEvent &event);
    void screenGhost(wxCommandEvent &event);
    void emulateAudio(wxCommandEvent &event);
    void audio16Bit(wxCommandEvent &event);
    void micEnable(wxCommandEvent &event);
    void arm7Hle(wxCommandEvent &event);
    void dsiMode(wxCommandEvent &event);
    void pathSettings(wxCommandEvent &event);
    void layoutSettings(wxCommandEvent &event);
    void inputSettings(wxCommandEvent &event);
    void updateJoystick(wxTimerEvent &event);
    void dropFiles(wxDropFilesEvent &event);
    void close(wxCloseEvent &event);
    wxDECLARE_EVENT_TABLE();
};
