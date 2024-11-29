#include "Functions.h"
extern _POINT _A[BOARD_SIZE][BOARD_SIZE];
extern bool _TURN;
extern int _COMMAND;
extern int _X, _Y;



void About(){
    printf("Contact: Email:...............\n");//đứa nào điền email dô
    printf("Fb: .................\n");//đứa nào điền fb dô
    printf("Name:...............MSSV\n");//điền tên, mssv dô nào mấy fen hehe..
}



void Guide() {
    printf("\n======================== GUIDE ========================\n");
    printf("Controls:\n");
    printf("  W : Move up\n");
    printf("  A : Move left\n");
    printf("  D : Move right\n");
    printf("  S : Move down\n\n");
    printf("Game Rules:\n");
    printf("  The goal of the game is to align 5 cells consecutively in\n");
    printf("  a straight line, diagonal, or horizontal line faster than\n");
    printf("  your opponent. Achieving 4 unblocked moves also wins.\n\n");
    printf("Tips:\n");
    printf("  - Plan ahead and block your opponent's moves.\n");
    printf("  - Use strategies from online resources to improve.\n");
    printf("=======================================================\n\n");
}


void MenuHandler() {
    const int NUM_MENU_ITEMS = 5;
    const char* menuItems[NUM_MENU_ITEMS] = {
        "New Game",
        "Load Game", 
        "Guide",
        "About",
        "Exit"
    };
    
    int selectedItem = 0;
    
    while (true) {
        system("cls");
        cout << "====================== DIT ME CONG SAN ======================\n\n";
        
        // display menu ưith highlights
            for (int i = 0; i < NUM_MENU_ITEMS; i++) {
            if (i == selectedItem) {
                cout << ">> " << menuItems[i] << " <<" << endl;
            } else {
                cout << "   " << menuItems[i] << endl;
            }
        }
        
        // inpit
        int ch = getch();
        switch (ch) {
            case 'W':
            case 'w':
            case 72: // up
                selectedItem = (selectedItem - 1 + NUM_MENU_ITEMS) % NUM_MENU_ITEMS;
                break;
            
            case 'S':
            case 's':
            case 80: // down
                selectedItem = (selectedItem + 1) % NUM_MENU_ITEMS;
                break;
            
            case 13: // enter
                switch (selectedItem) {
                    case 0: // New Game
                        system("cls");
                        StartGame();
                        moveWASD();
                        return;
                    
                    case 1: // Load Game
                        system("cls");
                        loadGame();
                        moveWASD();
                        return;
                    
                    case 2: // Guide
                        system("cls");
                        Guide();
                        cout << "Press any key to return to menu...";
                        getch();
                        break;
                    
                    case 3: // About
                        system("cls");
                        About();
                        cout << "Press any key to return to menu...";
                        getch();
                        break;
                    
                    case 4: // Exit
                        ExitGame();
                        exit(0);
                }
                break;
            
            case 27: // Escape key
                ExitGame();
                exit(0);
        }
    }
}


void InGameMenu() {
    const int NUM_MENU_ITEMS = 4;
    const char* menuItems[NUM_MENU_ITEMS] = {
        "Continue",
        "Save Game", 
        "Load Game",
        "Exit Game"
    };
    
    int selectedItem = 0;
    
    while (true) {
        system("cls");
        cout << "====================== MENU CAI LOL TAO ======================" << endl << endl;
        
        // display menu with highlights
        for (int i = 0; i < NUM_MENU_ITEMS; i++) {
            if (i == selectedItem) {
                cout << ">> " << menuItems[i] << " <<" << endl;
            } else {
                cout << "   " << menuItems[i] << endl;
            }
        }
        
        // input
        int ch = getch();
        switch (ch) {
            case 'W':
            case 'w':
            case 72: // up
                selectedItem = (selectedItem - 1 + NUM_MENU_ITEMS) % NUM_MENU_ITEMS;
                break;
            
            case 'S':
            case 's':
            case 80: // down
                selectedItem = (selectedItem + 1) % NUM_MENU_ITEMS;
                break;
            
            case 13: // enter
                switch (selectedItem) {
                    case 0: // Continue
                        system("cls");
                        DrawBoard();
                        // redraw existing X and O 
                        for (int i = 0; i < BOARD_SIZE; i++) {
                            for (int j = 0; j < BOARD_SIZE; j++) {
                                GotoXY(_A[i][j].x, _A[i][j].y);
                                if (_A[i][j].c == -1) {
                                    cout << "X";
                                } else if (_A[i][j].c == 1) {
                                    cout << "O";
                                }
                            }
                        }
                        GotoXY(_X, _Y);
                        return;
                    
                    case 1: // Save Game
                        saveGame();
                        getch();
                        break;
                    
                    case 2: // Load Game
                        loadGame();
                        moveWASD();
                        return;
                    
                    case 3: // Exit Game
                        ExitGame();
                        MenuHandler();
                        return;
                }
                break;
            
            case 27: // esc key
                // redraw board and return to game
                system("cls");
                DrawBoard();
                // redraw existing X and O 
                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        GotoXY(_A[i][j].x, _A[i][j].y);
                        if (_A[i][j].c == -1) {
                            cout << "X";
                        } else if (_A[i][j].c == 1) {
                            cout << "O";
                        }
                    }
                }
                GotoXY(_X, _Y);
                return;
        }
    }
}



vector<string> GetSaveFiles() {
    vector<string> saveFiles;
    string savePath = "."; // current directory

    for (const auto& entry : filesystem::directory_iterator(savePath)) {
        if (entry.is_regular_file()) {
            string filename = entry.path().filename().string();
            
            if (filename.length() > 4 && filename.substr(filename.length() - 4) == ".txt") {
                saveFiles.push_back(filename);
            }
        }
    }

    return saveFiles;
}

string SelectSaveFile(bool isSaving) {
    vector<string> saveFiles = GetSaveFiles();
    int selectedFile = 0;

    while (true) {
        system("cls");
        cout << (isSaving ? "Select Save File:" : "Select Load File:") << endl;
        
        // add new save
        if (isSaving) {
            if (selectedFile == 0) {
                cout << ">> New Save <<" << endl;
            } else {
                cout << "   New Save" << endl;
            }
        }

        // display existing save files
        for (int i = 0; i < saveFiles.size(); i++) {
            if (i + (isSaving ? 1 : 0) == selectedFile) {
                cout << ">> " << saveFiles[i] << " <<" << endl;
            } else {
                cout << "   " << saveFiles[i] << endl;
            }
        }
        
        int ch = getch();
        switch (ch) {
            case 'W':
            case 'w':
            case 72: // up
                selectedFile = (selectedFile - 1 + saveFiles.size() + (isSaving ? 1 : 0)) 
                               % (saveFiles.size() + (isSaving ? 1 : 0));
                break;
            
            case 'S':
            case 's':
            case 80: // down
                selectedFile = (selectedFile + 1) 
                               % (saveFiles.size() + (isSaving ? 1 : 0));
                break;
            
            case 13: // enter
                if (isSaving && selectedFile == 0) {
                    // new save
                    system("cls");
                    cout << "Enter save name: ";
                    string filename;
                    getline(cin, filename);
                    
                    // them .txt
                    if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".txt") {
                        filename += ".txt";
                    }
                    
                    // check file co san chua
                    bool fileExists = false;
                    for (const string& existingFile : saveFiles) {
                        if (existingFile == filename) {
                            fileExists = true;
                            break;
                        }
                    }
                    
                    if (fileExists) {
                        cout << "File already exists! Press any key to try again...";
                        getch();
                        continue;
                    }
                    
                    return filename;
                } else {
                    // return selected existing save file
                    return saveFiles[selectedFile - (isSaving ? 1 : 0)];
                }
                break;
            
            case 27: // escape
                return "";  // nha ra empty de biet la cancel duoc
        }
    }
}


void saveGame() {
    // prevent saving during initial menu
    if (_X == 0 && _Y == 0) {
        printf("Cannot save game before starting!\n");
        cout << "Press any key to continue...";
        getch();
        return;
    }

    const char* saveOptions[] = {
        "Save to New File",
        "Overwrite Existing Save"
    };
    int selectedOption = 0;

    while (true) {
        system("cls");
        cout << "Save Game Options:\n\n";

        // display menu with highlights
        for (int i = 0; i < 2; i++) {
            if (i == selectedOption) {
                cout << ">> " << saveOptions[i] << " <<\n";
            } else {
                cout << "   " << saveOptions[i] << "\n";
            }
        }

        int ch = getch();
        switch (ch) {
            case 'W':
            case 'w':
            case 72: // up arrow
                selectedOption = (selectedOption - 1 + 2) % 2;
                break;
            
            case 'S':
            case 's':
            case 80: // down arrow
                selectedOption = (selectedOption + 1) % 2;
                break;
            
            case 13: // enter
                if (selectedOption == 0) {
                    // save to new
                    string filename = SelectSaveFile(true);
                    if (filename.empty()) return; // user canceled

                    FILE *outFile = fopen(filename.c_str(), "w");
                    if (outFile) {
                        // lưu trạng thái của bảng!!!
                        for (int i = 0; i < BOARD_SIZE; i++) {
                            for (int j = 0; j < BOARD_SIZE; j++) {
                                fprintf(outFile, "%d ", _A[i][j].c);
                            }
                            fprintf(outFile, "\n");
                        }
                        // save lượt chơi
                        fprintf(outFile, "%d\n", _TURN);
                        // save tọa độ
                        fprintf(outFile, "%d %d\n", _X, _Y);
                        
                        printf("Game state saved to: %s\n", filename.c_str());
                        fclose(outFile);
                        
                        cout << "Press any key to continue...";
                        getch();
                        return;
                    } else {
                        printf("Error: Unable to save the file.\n");
                        cout << "Press any key to continue...";
                        getch();
                        return;
                    }
                } else {
                    // overwrite existing save
                    string filename = SelectSaveFile(false);
                    if (filename.empty()) return; // user canceled

                    FILE *outFile = fopen(filename.c_str(), "w");
                    if (outFile) {
                        // lưu trạng thái của bảng!!!
                        for (int i = 0; i < BOARD_SIZE; i++) {
                            for (int j = 0; j < BOARD_SIZE; j++) {
                                fprintf(outFile, "%d ", _A[i][j].c);
                            }
                            fprintf(outFile, "\n");
                        }
                        // save lượt chơi
                        fprintf(outFile, "%d\n", _TURN);
                        // save tọa độ
                        fprintf(outFile, "%d %d\n", _X, _Y);
                        
                        printf("Game state saved to: %s\n", filename.c_str());
                        fclose(outFile);
                        
                        cout << "Press any key to continue...";
                        getch();
                        return;
                    } else {
                        printf("Error: Unable to save the file.\n");
                        cout << "Press any key to continue...";
                        getch();
                        return;
                    }
                }
                break;
            
            case 27: // escape
                return;
        }
    }
}




void loadGame() {
    string filename = SelectSaveFile(false);
    if (filename.empty()) return; // user canceled

    FILE *inFile = fopen(filename.c_str(), "r");
    if (inFile) {
        // reset neu dang choi
        system("cls");
        ResetData();

        //đọc trạng thái bảng
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                fscanf(inFile, "%d", &_A[i][j].c);
                // Ensure x and y coordinates are correct
                _A[i][j].x = 4 * j + LEFT + 2; 
                _A[i][j].y = 2 * i + TOP + 1; 
            }
        }
        
        //đọc lượt chơi
        int turn;
        fscanf(inFile, "%d", &turn);
        _TURN = turn;
        
        // đọc tọa độ 
        fscanf(inFile, "%d %d", &_X, &_Y);

        printf("Game state loaded from: %s\n", filename.c_str());
        fclose(inFile);

        // draw board
        DrawBoard();
        
        // draw X and O 
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                GotoXY(_A[i][j].x, _A[i][j].y);
                if (_A[i][j].c == -1) {
                    cout << "X";
                } else if (_A[i][j].c == 1) {
                    cout << "O";
                }
            }
        }
        
        // position cursor
        GotoXY(_X, _Y);
        moveWASD();
    } else {
        printf("Error: Unable to open the file.\n");
        cout << "Press any key to continue...";
        getch();
        MenuHandler();
    }
}