#pragma once
struct ConfigLoader {
    const std::string FILE_NAME = "grinder.ini";
    std::vector<std::string>* lines = new std::vector<std::string>;
    long m_lastTimeFileEdited = 0;

    ConfigLoader() {
        reloadFile();
    }
    
    //screen resolution
    int SCREEN_WIDTH = 2560;
    int SCREEN_HEIGHT = 1440;
    int SCREEN_LEFT_WIDTH = 0;

    // Gane mode
    bool IS_GAME_BR = true;

    //features
    bool FEATURE_AIMBOT_ON = true;
    bool FEATURE_SENSE_ON = true;
    bool FEATURE_LOBA_ON = true;
    bool FEATURE_SPECTATOR_ON = true;
    bool FEATURE_QUICKTURN_ON = true;
    bool FEATURE_SKINCHANGER_ON = true;
    bool FEATURE_TRIGGERBOT_ON = true;
    bool FEATURE_NORECOIL_ON = true;
    bool FEATURE_PRINT_LEVELS_ON = true;
    bool FEATURE_SUPER_GLIDE_ON = true;
    bool FEATURE_MAP_RADAR_ON = true;
    bool FEATURE_RADAR_ON = true;

    //norecoil    
    int NORECOIL_PITCH_REDUCTION = 15;
    int NORECOIL_YAW_REDUCTION = 17;

    //aimbot
    bool AIMBOT_ACTIVATED_BY_ATTACK = true;
    bool AIMBOT_ACTIVATED_BY_ADS = false;
    std::string AIMBOT_ACTIVATED_BY_BUTTON = "XK_Shift_L";
    std::string FEATURE_QUICKTURN_BUTTON = "XK_f";
    std::string FEATURE_PRINT_LEVELS_BUTTON = "XK_p";
    std::string FEATURE_MAP_RADAR_BUTTON = "XK_o";
    int AIMBOT_SMOOTH = 20;
    float AIMBOT_SPEED = 40;
    int AIMBOT_SMOOTH_EXTRA_BY_DISTANCE = 1000;
    float AIMBOT_FOV = 5.0000;
    bool AIMBOT_PREDICT_BULLETDROP = true;
    bool AIMBOT_PREDICT_MOVEMENT = true;
    bool AIMBOT_ALLOW_TARGET_SWITCH = true;
    int AIMBOT_MAX_DISTANCE = 100;
    int AIMBOT_MIN_DISTANCE = 1;
    float AIMBOT_DEADZONE = 0.0100;
    
    // radar
    int RADAR_POSITION = 1;
    int RADAR_SIZE = 300;
    int RADAR_ZOOM = 20;
    int RADAR_ENEMY_SCALE_DIVIDER = 35;


    void loadVariables(std::string key, std::string val) {
    	//screen resolution
	    SCREEN_WIDTH = (key.compare("SCREEN_WIDTH") != 0) ? SCREEN_WIDTH : stoi(val);
        SCREEN_HEIGHT = (key.compare("SCREEN_HEIGHT") != 0) ? SCREEN_HEIGHT : stoi(val);
	    SCREEN_LEFT_WIDTH = (key.compare("SCREEN_LEFT_WIDTH") != 0) ? SCREEN_LEFT_WIDTH : stoi(val);

        //gameMode
        IS_GAME_BR = (key.compare("IS_GAME_BR") != 0) ? IS_GAME_BR : toBool(val);
        
        //features
        FEATURE_AIMBOT_ON = (key.compare("FEATURE_AIMBOT_ON") != 0) ? FEATURE_AIMBOT_ON : toBool(val);
        FEATURE_SENSE_ON = (key.compare("FEATURE_SENSE_ON") != 0) ? FEATURE_SENSE_ON : toBool(val);
        FEATURE_LOBA_ON = (key.compare("FEATURE_LOBA_ON") != 0) ? FEATURE_LOBA_ON : toBool(val);
        FEATURE_TRIGGERBOT_ON = (key.compare("FEATURE_TRIGGERBOT_ON") != 0) ? FEATURE_TRIGGERBOT_ON : toBool(val);
        FEATURE_NORECOIL_ON = (key.compare("FEATURE_NORECOIL_ON") != 0) ? FEATURE_NORECOIL_ON : toBool(val);
        FEATURE_RADAR_ON = (key.compare("FEATURE_RADAR_ON") != 0) ? FEATURE_RADAR_ON : toBool(val);

        //norecoil        
        NORECOIL_PITCH_REDUCTION = (key.compare("NORECOIL_PITCH_REDUCTION") != 0) ? NORECOIL_PITCH_REDUCTION : stoi(val);
        NORECOIL_YAW_REDUCTION = (key.compare("NORECOIL_YAW_REDUCTION") != 0) ? NORECOIL_YAW_REDUCTION : stoi(val);

        //aimbot
        AIMBOT_ACTIVATED_BY_ATTACK = (key.compare("AIMBOT_ACTIVATED_BY_ATTACK") != 0) ? AIMBOT_ACTIVATED_BY_ATTACK : toBool(val);
        AIMBOT_ACTIVATED_BY_ADS = (key.compare("AIMBOT_ACTIVATED_BY_ADS") != 0) ? AIMBOT_ACTIVATED_BY_ADS : toBool(val);
        AIMBOT_ACTIVATED_BY_BUTTON = (key.compare("AIMBOT_ACTIVATED_BY_BUTTON") != 0) ? AIMBOT_ACTIVATED_BY_BUTTON : trimConstructive(val);
        AIMBOT_SMOOTH = (key.compare("AIMBOT_SMOOTH") != 0) ? AIMBOT_SMOOTH : stoi(val);
        AIMBOT_SMOOTH_EXTRA_BY_DISTANCE = (key.compare("AIMBOT_SMOOTH_EXTRA_BY_DISTANCE") != 0) ? AIMBOT_SMOOTH_EXTRA_BY_DISTANCE : stoi(val);
        AIMBOT_FOV = (key.compare("AIMBOT_FOV") != 0) ? AIMBOT_FOV : stod(val);
        AIMBOT_MIN_DISTANCE = (key.compare("AIMBOT_MIN_DISTANCE") != 0) ? AIMBOT_MIN_DISTANCE : stoi(val);
        AIMBOT_MAX_DISTANCE = (key.compare("AIMBOT_MAX_DISTANCE") != 0) ? AIMBOT_MAX_DISTANCE : stoi(val);
        
        // Radar
        RADAR_POSITION = (key.compare("RADAR_POSITION") != 0) ? RADAR_POSITION : stoi(val);
        RADAR_SIZE = (key.compare("RADAR_SIZE") != 0) ? RADAR_SIZE : stoi(val);
        RADAR_ZOOM = (key.compare("RADAR_ZOOM") != 0) ? RADAR_ZOOM : stoi(val);
        RADAR_ENEMY_SCALE_DIVIDER = (key.compare("RADAR_ENEMY_SCALE_DIVIDER") != 0) ? RADAR_ENEMY_SCALE_DIVIDER : stoi(val);

        //random
        FEATURE_SPECTATOR_ON = (key.compare("FEATURE_SPECTATOR_ON") != 0) ? FEATURE_SPECTATOR_ON : toBool(val);
        FEATURE_SUPER_GLIDE_ON = (key.compare("FEATURE_SUPER_GLIDE_ON") != 0) ? FEATURE_SUPER_GLIDE_ON : toBool(val);
        FEATURE_SKINCHANGER_ON = (key.compare("FEATURE_SKINCHANGER_ON") != 0) ? FEATURE_SKINCHANGER_ON : toBool(val);
        FEATURE_QUICKTURN_ON = (key.compare("FEATURE_QUICKTURN_ON") != 0) ? FEATURE_QUICKTURN_ON : toBool(val);    
        FEATURE_QUICKTURN_BUTTON = (key.compare("FEATURE_QUICKTURN_BUTTON") != 0) ? FEATURE_QUICKTURN_BUTTON : trimConstructive(val);
        FEATURE_PRINT_LEVELS_ON = (key.compare("FEATURE_PRINT_LEVELS_ON") != 0) ? FEATURE_PRINT_LEVELS_ON : toBool(val); 
        FEATURE_PRINT_LEVELS_BUTTON = (key.compare("FEATURE_PRINT_LEVELS_BUTTON") != 0) ? FEATURE_PRINT_LEVELS_BUTTON : trimConstructive(val);
        FEATURE_MAP_RADAR_ON = (key.compare("FEATURE_MAP_RADAR_ON") != 0) ? FEATURE_MAP_RADAR_ON : toBool(val); 
        FEATURE_MAP_RADAR_BUTTON = (key.compare("FEATURE_MAP_RADAR_BUTTON") != 0) ? FEATURE_MAP_RADAR_BUTTON : trimConstructive(val);
    }

    void print() {
        printf("\n===== GRINDER SETTINGS LOADED - R5Apex v3.0.82.42 (8/10/2024) =======\n");
        
        //screen resolution
        printf("SCREEN_WIDTH\t\t\t\t\t\t%.d\n", SCREEN_WIDTH);
        printf("SCREEN_HEIGHT\t\t\t\t\t\t%.d\n", SCREEN_HEIGHT);
        printf("SCREEN_LEFT_WIDTH\t\t\t\t\t%.d\n", SCREEN_LEFT_WIDTH);
	    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
        //features
        printf("FEATURE_AIMBOT_ON\t\t\t\t\t%s\n", FEATURE_AIMBOT_ON ? "YES" : "NO");
        printf("FEATURE_SENSE_ON\t\t\t\t\t%s\n", FEATURE_SENSE_ON ? "YES" : "NO");
        printf("FEATURE_LOBA_ON\t\t\t\t\t%s\n", FEATURE_LOBA_ON ? "YES" : "NO");
        printf("FEATURE_TRIGGERBOT_ON\t\t\t\t\t%s\n", FEATURE_TRIGGERBOT_ON ? "YES" : "NO");
        printf("FEATURE_NORECOIL_ON\t\t\t\t\t%s\n", FEATURE_NORECOIL_ON ? "YES" : "NO");
        printf("FEATURE_RADAR_ON\t\t\t\t\t%s\n", FEATURE_RADAR_ON ? "YES" : "NO");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        printf("FEATURE_SPECTATOR_ON\t\t\t\t\t%s\n", FEATURE_SPECTATOR_ON ? "YES" : "NO");
        printf("FEATURE_SUPER_GLIDE_ON\t\t\t\t\t%s\n", FEATURE_SUPER_GLIDE_ON ? "YES" : "NO");
        printf("FEATURE_SKINCHANGER_ON\t\t\t\t\t%s\n", FEATURE_SKINCHANGER_ON ? "YES" : "NO");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        printf("FEATURE_QUICKTURN_ON\t\t\t\t\t%s\n", FEATURE_QUICKTURN_ON ? "YES" : "NO");
        printf("FEATURE_QUICKTURN_BUTTON\t\t\t\t%s\n", FEATURE_QUICKTURN_BUTTON.c_str());
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        printf("FEATURE_PRINT_LEVELS_ON\t\t\t\t\t%s\n", FEATURE_PRINT_LEVELS_ON ? "YES" : "NO");
        printf("FEATURE_PRINT_LEVELS_BUTTON\t\t\t\t%s\n", FEATURE_PRINT_LEVELS_BUTTON.c_str());
        
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("FEATURE_MAP_RADAR_ON\t\t\t\t\t%s\n", FEATURE_MAP_RADAR_ON ? "YES" : "NO");
        printf("FEATURE_MAP_RADAR_BUTTON\t\t\t\t%s\n", FEATURE_MAP_RADAR_BUTTON.c_str());
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        //norecoil
        printf("NORECOIL_PITCH_REDUCTION\t\t\t\t%d\n", NORECOIL_PITCH_REDUCTION);
        printf("NORECOIL_YAW_REDUCTION\t\t\t\t\t%d\n", NORECOIL_YAW_REDUCTION);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        //aimbot
        printf("AIMBOT_ACTIVATED_BY_ATTACK\t\t\t\t%s\n", AIMBOT_ACTIVATED_BY_ATTACK ? "YES" : "NO");
        printf("AIMBOT_ACTIVATED_BY_ADS\t\t\t\t\t%s\n", AIMBOT_ACTIVATED_BY_ADS ? "YES" : "NO");
        printf("AIMBOT_ACTIVATED_BY_BUTTON\t\t\t\t%s\n", AIMBOT_ACTIVATED_BY_BUTTON.c_str());
        printf("AIMBOT_SMOOTH\t\t\t\t\t\t%.d\n", AIMBOT_SMOOTH);
        printf("AIMBOT_SMOOTH_EXTRA_BY_DISTANCE\t\t\t\t%.d\n", AIMBOT_SMOOTH_EXTRA_BY_DISTANCE);
        printf("AIMBOT_FOV\t\t\t\t\t\t%.4f\n", AIMBOT_FOV);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        
        printf("RADAR_POSITION\t\t\t\t\t\t%d\n", RADAR_POSITION);
        printf("RADAR_SIZE\t\t\t\t\t\t%.d\n", RADAR_SIZE);
        printf("RADAR_ZOOM\t\t\t\t\t\t%.d\n", RADAR_ZOOM);
        printf("RADAR_ENEMY_SCALE_DIVIDER\t\t\t\t%.d\n", RADAR_ENEMY_SCALE_DIVIDER);

        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        //gameMode
        printf("IS_GAME_BR\t\t\t\t\t\t%s\n", IS_GAME_BR ? "YES" : "NO");

        printf("=====================================================================\n\n");
    }

    void reloadFile() {
        if (loadFileIntoVector()) {
            parseLines();
            print();
        }
    }

    void parseLines() {
        for (int i = 0; i < lines->size(); i++) {
            std::vector<std::string> lineParts = split(lines->at(i));
            // line key
            std::string key(lineParts.at(0));
            trim(key);
            if (key.empty()) throw "Cannot parse the config. Bad key";
            // line value
            std::string value(lineParts.at(1));
            trim(value);
            if (value.empty()) throw "Cannot parse the config. Bad value";
            loadVariables(key, value);
        }
    }

    bool loadFileIntoVector() {
        struct stat result;
        if (stat(FILE_NAME.c_str(), &result) == 0) {
            long modTime = result.st_mtime;
            bool fileNeedsReload = modTime > m_lastTimeFileEdited;
            m_lastTimeFileEdited = modTime;
            if (!fileNeedsReload) return false;
        }
        lines->clear();
        std::string str;
        std::ifstream myFile(FILE_NAME);
        while (getline(myFile, str)) {
            trim(str);
            if (str.empty()) continue;
            if (str.rfind("#", 0) == 0) continue;
            lines->push_back(str);
        }
        myFile.close();
        return true;
    }

    bool toBool(std::string str) {
        if (toLowerCase(str) == "y") return true;
        if (toLowerCase(str) == "n") return false;
        if (toLowerCase(str) == "yes") return true;
        if (toLowerCase(str) == "no") return false;
        if (toLowerCase(str) == "1") return true;
        if (toLowerCase(str) == "0") return false;
        throw  std::invalid_argument("Cannot parse string to boolean: " + str);
    }

    void trim(std::string& s) {
        ltrim(s);
        rtrim(s);
    }

    std::string trimConstructive(std::string& s) {
        ltrim(s);
        rtrim(s);
        return s;
    }

    void ltrim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
            { return !std::isspace(ch); }));
    }

    void rtrim(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
            { return !std::isspace(ch); })
            .base(),
            s.end());
    }

    std::vector<std::string> split(std::string s) {
        std::stringstream ss(s);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> tokens(begin, end);
        return tokens;
    }

    std::string toLowerCase(const std::string& input) {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
};
