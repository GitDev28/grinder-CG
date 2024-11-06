#pragma once

struct Player {
    int index;
    LocalPlayer* myLocalPlayer;
    uint64_t base;
    std::string name;
    bool dead;
    bool knocked;
    int ducking;
    int teamNumber;
    int currentHealth;
    int currentShields;
    int glowEnable;
    int glowThroughWall;
    int highlightId;
    FloatVector3D localOrigin_prev;
    FloatVector3D localOrigin;
    FloatVector3D AbsoluteVelocity;
    FloatVector3D localOrigin_predicted;
    bool local;
    bool friendly;
    bool enemy;
    int lastTimeAimedAt;
    int lastTimeAimedAtPrev;
    bool aimedAt;
    int lastTimeVisible;
    int lastTimeVisiblePrev;
    bool visible;
    float distanceToLocalPlayer;
    float distance2DToLocalPlayer;
    //values used by aimbot
    bool aimbotLocked;
    bool IsLockedOn;
    bool nonBR;
    FloatVector2D aimbotDesiredAngles;
    FloatVector2D aimbotDesiredAnglesIncrement;
    FloatVector2D aimbotDesiredAnglesSmoothed;
    FloatVector2D aimbotDesiredAnglesSmoothedNoRecoil;
    float aimbotScore;
    float view_yaw;
    uintptr_t nameOffset;
    uintptr_t nameIndex;

    Player(int index, LocalPlayer* in_localPlayer) {
        this->index = index;
        this->myLocalPlayer = in_localPlayer;
    }

    void reset() {
        base = 0;
    }

    std::string getPlayerName(){
        nameIndex = mem::Read<uintptr_t>(base + OFF_NAMEINDEX);                                         //player + 0x38
        nameOffset = mem::Read<uintptr_t>(OFF_REGION + OFF_NAMELIST + ((nameIndex - 1) << 4 ));         //Region + NameList
        std::string playerName = mem::ReadString(nameOffset, 64);
        return playerName;
    }
    
    std::string getPlayerModelName(){
        uintptr_t modelOffset = mem::Read<uintptr_t>(base + OFF_MODELNAME);
        std::string modelName = mem::ReadString(modelOffset, 1024);
        // Check for different player names
        if (modelName.find("dummie") != std::string::npos) modelName = "DUMMIE";
        else if (modelName.find("alter") != std::string::npos) modelName = "ALTER";
        else if (modelName.find("ash") != std::string::npos) modelName = "ASH";
        else if (modelName.find("ballistic") != std::string::npos) modelName = "BALLISTIC";
        else if (modelName.find("bangalore") != std::string::npos) modelName = "BANGALORE";
        else if (modelName.find("bloodhound") != std::string::npos) modelName = "BLOODHOUND";
        else if (modelName.find("catalyst") != std::string::npos) modelName = "CATALYST";
        else if (modelName.find("caustic") != std::string::npos) modelName = "CAUSTIC";
        else if (modelName.find("conduit") != std::string::npos) modelName = "CONDUIT";
        else if (modelName.find("crypto") != std::string::npos) modelName = "CRYPTO";
        else if (modelName.find("fuse") != std::string::npos) modelName = "FUSE";
        else if (modelName.find("gibraltar") != std::string::npos) modelName = "GIBRALTAR";
        else if (modelName.find("horizon") != std::string::npos) modelName = "HORIZON";
        else if (modelName.find("nova") != std::string::npos) modelName = "HORIZON";
        else if (modelName.find("holo") != std::string::npos) modelName = "MIRAGE";
        else if (modelName.find("mirage") != std::string::npos) modelName = "MIRAGE";
        else if (modelName.find("lifeline") != std::string::npos) modelName = "LIFELINE";
        else if (modelName.find("loba") != std::string::npos) modelName = "LOBA";
        else if (modelName.find("madmaggie") != std::string::npos) modelName = "MADMAGGIE";
        else if (modelName.find("newcastle") != std::string::npos) modelName = "NEWCASTLE";
        else if (modelName.find("octane") != std::string::npos) modelName = "OCTANE";
        else if (modelName.find("pathfinder") != std::string::npos) modelName = "PATHFINDER";
        else if (modelName.find("rampart") != std::string::npos) modelName = "RAMPART";
        else if (modelName.find("revenant") != std::string::npos) modelName = "REVENANT";
        else if (modelName.find("seer") != std::string::npos) modelName = "SEER";
        else if (modelName.find("stim") != std::string::npos) modelName = "OCTANE";
        else if (modelName.find("valkyrie") != std::string::npos) modelName = "VALKYRIE";
        else if (modelName.find("vantage") != std::string::npos) modelName = "VANTAGE";
        else if (modelName.find("wattson") != std::string::npos) modelName = "WATTSON";
        else if (modelName.find("wraith") != std::string::npos) modelName = "WRAITH";
        
        return modelName;
    }

    void readFromMemory(ConfigLoader* cl) {
        base = mem::Read<long>(OFF_REGION + OFF_ENTITY_LIST + ((index + 1) << 5), "Player base");
        if (base == 0) return;
        name = mem::ReadString(base + OFF_NAME, 1024, "Player name");
        teamNumber = mem::Read<int>(base + OFF_TEAM_NUMBER, "Player teamNumber");
        currentHealth = mem::Read<int>(base + OFF_CURRENT_HEALTH, "Player currentHealth");
        currentShields = mem::Read<int>(base + OFF_CURRENT_SHIELDS, "Player currentShields");
        if (!isPlayer() && !isDummie()) { reset(); return; }
        dead = (isDummie()) ? false : mem::Read<short>(base + OFF_LIFE_STATE, "Player dead") > 0;
        knocked = (isDummie()) ? false : mem::Read<short>(base + OFF_BLEEDOUT_STATE, "Player knocked") > 0;

        view_yaw = mem::Read<float>(base + OFF_YAW);
        localOrigin = mem::Read<FloatVector3D>(base + OFF_LOCAL_ORIGIN, "Player localOrigin");
        AbsoluteVelocity = mem::Read<FloatVector3D>(base + OFF_ABSVELOCITY, "Player AbsoluteVelocity");
        FloatVector3D localOrigin_diff = localOrigin.subtract(localOrigin_prev).normalize().multiply(20);
        localOrigin_predicted = localOrigin.add(localOrigin_diff);
        localOrigin_prev = FloatVector3D(localOrigin.x, localOrigin.y, localOrigin.z);

        glowEnable = mem::Read<int>(base + OFF_GLOW_ENABLE, "Player glowEnable");
        glowThroughWall = mem::Read<int>(base + OFF_GLOW_THROUGH_WALL, "Player glowThroughWall");
        highlightId = mem::Read<int>(base + OFF_GLOW_HIGHLIGHT_ID + 0, "Player highlightId");

        lastTimeAimedAt = mem::Read<int>(base + OFF_LAST_AIMEDAT_TIME, "Player lastTimeAimedAt");
        aimedAt = lastTimeAimedAtPrev < lastTimeAimedAt;
        lastTimeAimedAtPrev = lastTimeAimedAt;

        lastTimeVisible = mem::Read<int>(base + OFF_LAST_VISIBLE_TIME, "Player lastTimeVisible");
        visible = isDummie() || aimedAt || lastTimeVisiblePrev < lastTimeVisible; //aimedAt is only true when looking at unobscured target. Helps the shit in-game vis check a bit.
        lastTimeVisiblePrev = lastTimeVisible;

        if (myLocalPlayer->isValid()) {
            local = myLocalPlayer->base == base;
            nonBR = !cl->IS_GAME_BR;
            friendly = (nonBR)
                ? (myLocalPlayer->teamNumber % 2 == 0 && teamNumber % 2 == 0) || (myLocalPlayer->teamNumber % 2 != 0 && teamNumber % 2 != 0)
                : myLocalPlayer->teamNumber == teamNumber;
            enemy = !friendly;
            distanceToLocalPlayer = myLocalPlayer->localOrigin.distance(localOrigin);
            distance2DToLocalPlayer = myLocalPlayer->localOrigin.to2D().distance(localOrigin.to2D());
            if (visible) {
                aimbotDesiredAngles = calcDesiredAngles();
                aimbotDesiredAnglesIncrement = calcDesiredAnglesIncrement();
                aimbotScore = calcAimbotScore();
            }
        }

    }

    bool isValid() {
        return base != 0 && (isPlayer() || isDummie());
    }

    void MapRadar(ConfigLoader* cl, XDisplay* m_disp) {
        if (m_disp->keyDown(cl->FEATURE_MAP_RADAR_BUTTON) && cl->FEATURE_MAP_RADAR_ON) {
            uintptr_t pLocal = mem::Read<uintptr_t>(OFF_REGION + OFF_LOCAL_PLAYER);

            int currentTEAM = mem::Read<int>(pLocal + OFF_TEAM_NUMBER);

            for (uintptr_t i = 0; i <= 80000; i++)
            {
            mem::Write<int>(pLocal + OFF_TEAM_NUMBER, 1);
            }
            for (uintptr_t i = 0; i <= 80000; i++)
            {
            mem::Write<int>(pLocal + OFF_TEAM_NUMBER, currentTEAM);
            } 
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    bool isCombatReady() {
        if (!isValid())return false;
        if (isDummie()) return true;
        if (dead) return false;
        if (knocked) return false;
        return true;
    }

    bool isPlayer() {
        return name == "player";
    }

    bool isDummie() {
        return teamNumber == 97;
    }

    void setGlowEnable(int glowEnable)
    {
        long ptrLong = base + OFF_GLOW_ENABLE;
        mem::Write<int>(ptrLong, glowEnable);
    }
    void setGlowThroughWall(int glowThroughWall)
    {  
        long ptrLong = base + OFF_GLOW_THROUGH_WALL;
        mem::Write<int>(ptrLong, glowThroughWall);
    }
    int getGlowThroughWall()
    {
        int ptrInt = mem::Read<int>(base + OFF_GLOW_THROUGH_WALL);
        if (!mem::IsValidPointer(ptrInt))
            return -1;
        return ptrInt;
    }
    int getGlowEnable()
    {
        int ptrInt = mem::Read<int>(base + OFF_GLOW_ENABLE);
        if (!mem::IsValidPointer(ptrInt))
            return -1;
        return ptrInt;
    }
    int GetPlayerLevel()
    {
        int m_xp = mem::Read<int>(base + 0x3634); //m_xp
        if (m_xp < 0) return 0;
        if (m_xp < 100) return 1;
     
        int levels[] = { 2750, 6650, 11400, 17000, 23350, 30450, 38300, 46450, 55050,
        64100, 73600, 83550, 93950, 104800, 116100, 127850, 140050, 152400, 164900, 
        177550, 190350, 203300, 216400, 229650, 243050, 256600, 270300, 284150, 298150, 
        312300, 326600, 341050, 355650, 370400, 385300, 400350, 415550, 430900, 446400, 
        462050, 477850, 493800, 509900, 526150, 542550, 559100, 575800, 592650, 609650, 626800, 
        644100, 661550, 679150, 696900, 714800 };
     
        int level = 56;
        int arraySize = sizeof(levels) / sizeof(levels[0]);
     
        for (int i = 0; i < arraySize; i++)
        {
            if (m_xp < levels[i])
            {
                return i + 1;
            }
        }   
        return level + ((m_xp - levels[arraySize - 1] + 1) / 18000);
    }

    void setCustomGlow(ConfigLoader* cl, int health, bool isVisible, bool isSameTeam)
    {
        static const int contextId = 0; // Same as glow enable
        long basePointer = base;
        int settingIndex = 65;
        std::array<unsigned char, 4> highlightFunctionBits = {
            2,   // InsideFunction
            125, // OutlineFunction: HIGHLIGHT_OUTLINE_OBJECTIVE
            64,  // OutlineRadius: size * 255 / 8
            64   // (EntityVisible << 6) | State & 0x3F | (AfterPostProcess << 7)
        };
        std::array<float, 3> glowColorRGB = { 0, 0, 0 };
        if (isSameTeam) {
            settingIndex = 20;
        } else if (!isVisible) {
            settingIndex = 65;
            glowColorRGB = { 0.5, 0.5, 0.5 }; // knocked enemies // gray
        } else if (health >= 205) {
            settingIndex = 66;
            glowColorRGB = { 1, 0, 0 }; // red shield
        } else if (health >= 190) {
            settingIndex = 67;
            glowColorRGB = { 0.5, 0, 0.5 }; // purple shield
        } else if (health >= 170) {
            settingIndex = 68;
            glowColorRGB = { 0, 0.5, 1 }; // blue shield
        } else if (health >= 95) {
            settingIndex = 69;
            glowColorRGB = { 0, 1, 0.5 }; // gray shield // cyan 
        } else {
            settingIndex = 70;
            glowColorRGB = { 0, 0.5, 0 }; // low health enemies // greeen
        }
        mem::Write<unsigned char>(basePointer + OFF_GLOW_HIGHLIGHT_ID + contextId, settingIndex);
        
        long highlightSettingsPtr = mem::Read<long>( OFF_REGION + OFF_GLOW_HIGHLIGHTS);
        if (!isSameTeam) {
            mem::Write<typeof(highlightFunctionBits)>(
                highlightSettingsPtr + HIGHLIGHT_TYPE_SIZE * settingIndex + 0, highlightFunctionBits);
            mem::Write<typeof(glowColorRGB)>(
                highlightSettingsPtr + HIGHLIGHT_TYPE_SIZE * settingIndex + 4, glowColorRGB);
            mem::Write<int>(basePointer + OFF_GLOW_FIX, 0);
        }
        
        //item Glow UPDATE!
        const std::vector<uint8_t> ItemHighlightID = { 15, 42, 47, 54, 65, 9, 58 }; // Gold, Red, Purple, Blue, Grey, Weapons, Ammo

        if (cl->FEATURE_LOBA_ON) {
            for (int highlightId : ItemHighlightID) {
                const GlowMode newGlowMode = { 137,0,0,127 }; // Or whatever glow settings you want
                const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (HIGHLIGHT_TYPE_SIZE * highlightId) + 0);
                
                if (newGlowMode != oldGlowMode) {
                    mem::Write<GlowMode>(highlightSettingsPtr + (HIGHLIGHT_TYPE_SIZE * highlightId) + 0, newGlowMode);
                }
            }
        }
    }

    float calcDesiredPitch() {
        if (local) return 0;
        const FloatVector3D shift = FloatVector3D(100000, 100000, 100000);
        const FloatVector3D originA = myLocalPlayer->localOrigin.add(shift);
        const float extraZ = (ducking != -1) ? 10 : 0;
        const FloatVector3D originB = localOrigin_predicted.add(shift).subtract(FloatVector3D(0, 0, extraZ));
        const float deltaZ = originB.z - originA.z;
        const float pitchInRadians = std::atan2(-deltaZ, distance2DToLocalPlayer);
        const float degrees = pitchInRadians * (180.0f / M_PI);
        return degrees;
    }

    float calcDesiredYaw() {
        if (local) return 0;
        const FloatVector2D shift = FloatVector2D(100000, 100000);
        const FloatVector2D originA = myLocalPlayer->localOrigin.to2D().add(shift);
        const FloatVector2D originB = localOrigin_predicted.to2D().add(shift);
        const FloatVector2D diff = originB.subtract(originA);
        const double yawInRadians = std::atan2(diff.y, diff.x);
        const float degrees = yawInRadians * (180.0f / M_PI);
        return degrees;
    }

    FloatVector2D calcDesiredAngles() {
        return FloatVector2D(calcDesiredPitch(), calcDesiredYaw());
    }

    FloatVector2D calcDesiredAnglesIncrement() {
        return FloatVector2D(calcPitchIncrement(), calcYawIncrement());
    }

    int GetBoneFromHitbox(HitboxType HitBox) const {
        long ModelPointer = mem::Read<long>(base + OFF_STUDIOHDR);
        if (!mem::IsValidPointer(ModelPointer))
            return -1;

        long StudioHDR = mem::Read<long>(ModelPointer + 0x8);
        if (!mem::IsValidPointer(StudioHDR + 0x34))
            return -1;

        auto HitboxCache = mem::Read<uint16_t>(StudioHDR + 0x34);
        auto HitboxArray = StudioHDR + ((uint16_t)(HitboxCache & 0xFFFE) << (4 * (HitboxCache & 1))); 
        if (!mem::IsValidPointer(HitboxArray + 0x4))
            return -1;

        auto IndexCache = mem::Read<uint16_t>(HitboxArray + 0x4);
        auto HitboxIndex = ((uint16_t)(IndexCache & 0xFFFE) << (4 * (IndexCache & 1)));
        auto BonePointer = HitboxIndex + HitboxArray + (static_cast<int>(HitBox) * 0x20);
        if (!mem::IsValidPointer(BonePointer))
            return -1;
        return mem::Read<uint16_t>(BonePointer);
    }

    FloatVector3D GetBonePosition(HitboxType HitBox) const {
        FloatVector3D Offset = FloatVector3D(0.0f, 0.0f, 0.0f);

        int Bone = GetBoneFromHitbox(HitBox);
        if (Bone < 0 || Bone > 255)
            return localOrigin.add(Offset);

        long BonePtr = mem::Read<long>(base + OFF_BONES);
        BonePtr += (Bone * sizeof(Matrix3x4));
        if (!mem::IsValidPointer(BonePtr))
            return localOrigin.add(Offset);

        Matrix3x4 BoneMatrix = mem::Read<Matrix3x4>(BonePtr);
        FloatVector3D BonePosition = BoneMatrix.GetPosition();

        if (!BonePosition.IsValid())
            return localOrigin.add(FloatVector3D(0, 0, 0));

        BonePosition += localOrigin;
        return BonePosition;
    }

    float calcPitchIncrement() {
        float wayA = aimbotDesiredAngles.x - myLocalPlayer->viewAngles.x;
        float wayB = 180 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (fabs(wayA) < fabs(wayB))
            return wayA;
        return wayB;
    }

    float calcYawIncrement() {
        float wayA = aimbotDesiredAngles.y - myLocalPlayer->viewAngles.y;
        float wayB = 360 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        if (fabs(wayA) < fabs(wayB))
            return wayA;
        return wayB;
    }

    float calcAimbotScore() {
        return (1000 - (fabs(aimbotDesiredAnglesIncrement.x) + fabs(aimbotDesiredAnglesIncrement.y)));
    }
};
