#pragma once
struct Player {
    LocalPlayer* myLocalPlayer;
    int index;
    long base;
    std::string name;
    bool dead;
    bool knocked;
    int teamNumber;
    int glowEnable;
    int glowThroughWall;
    int highlightId;
    FloatVector3D localOrigin_prev;
    FloatVector3D localOrigin;
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
    FloatVector2D aimbotDesiredAngles;
    FloatVector2D aimbotDesiredAnglesIncrement;
    FloatVector2D aimbotDesiredAnglesSmoothed;
    FloatVector2D aimbotDesiredAnglesSmoothedNoRecoil;
    float aimbotScore;

    Player(int index, LocalPlayer* in_localPlayer) {
        this->index = index;
        this->myLocalPlayer = in_localPlayer;
    }

    void reset() {
        base = 0;
    }

    void readFromMemory() {
        base = mem::Read<long>(OFF_REGION + OFF_ENTITY_LIST + ((index + 1) << 5));
        if (base == 0) return;
        name = mem::ReadString(base + OFF_NAME, 1024);
        teamNumber = mem::Read<int>(base + OFF_TEAM_NUMBER);
        if (!isPlayer() && !isDummie()) { reset(); return; }
        dead = (isDummie()) ? false : mem::Read<short>(base + OFF_LIFE_STATE) > 0;
        knocked = (isDummie()) ? false : mem::Read<short>(base + OFF_BLEEDOUT_STATE) > 0;

        localOrigin = mem::Read<FloatVector3D>(base + OFF_LOCAL_ORIGIN);
        FloatVector3D localOrigin_diff = localOrigin.subtract(localOrigin_prev).normalize().multiply(30);
        localOrigin_predicted = localOrigin.add(localOrigin_diff);
        localOrigin_prev = FloatVector3D(localOrigin.x, localOrigin.y, localOrigin.z);


        glowEnable = mem::Read<int>(base + OFF_GLOW_ENABLE);
        glowThroughWall = mem::Read<int>(base + OFF_GLOW_THROUGH_WALL);
        highlightId = mem::Read<int>(base + OFF_GLOW_HIGHLIGHT_ID + 1);

        lastTimeAimedAt = mem::Read<int>(base + OFF_LAST_AIMEDAT_TIME);
        aimedAt = lastTimeAimedAtPrev < lastTimeAimedAt;
        lastTimeAimedAtPrev = lastTimeAimedAt;

        lastTimeVisible = mem::Read<int>(base + OFF_LAST_VISIBLE_TIME);
        visible = lastTimeVisiblePrev < lastTimeVisible; //make dummies always visible as the vis check for them is fucked
        lastTimeVisiblePrev = lastTimeVisible;

        if (myLocalPlayer->isValid()) {
            local = myLocalPlayer->base == base;
            friendly = myLocalPlayer->teamNumber == teamNumber;
            enemy = !friendly;
            distanceToLocalPlayer = myLocalPlayer->localOrigin.distance(localOrigin);
            distance2DToLocalPlayer = myLocalPlayer->localOrigin.to2D().distance(localOrigin.to2D());
            if (visible) {
                float aimbotSmmothing = (distance2DToLocalPlayer < util::metersToGameUnits(5)) ? 100 : 20;
                if (aimbotSmmothing < 1)
                    aimbotSmmothing = 1;
                aimbotDesiredAngles = calcDesiredAngles();
                aimbotDesiredAnglesIncrement = calcDesiredAnglesIncrement()
                    .divide({ aimbotSmmothing, aimbotSmmothing });
                aimbotDesiredAnglesSmoothed = myLocalPlayer->viewAngles
                    .add(aimbotDesiredAnglesIncrement);
                aimbotDesiredAnglesSmoothedNoRecoil = aimbotDesiredAnglesSmoothed
                    .subtract(myLocalPlayer->punchAngles.divide({ aimbotSmmothing, aimbotSmmothing }));
                aimbotScore = calcAimbotScore();
            }
        }
    }

    bool isValid() {
        return base != 0 && (!isPlayer() || !isDummie());
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

    void glow() {
        if (glowEnable != 1) mem::Write<int>(base + OFF_GLOW_ENABLE, 1);
        if (glowThroughWall != 2) mem::Write<int>(base + OFF_GLOW_THROUGH_WALL, 2);
        int id = (visible) ? 0 : 1;        
        if (highlightId != id) mem::Write<int>(base + OFF_GLOW_HIGHLIGHT_ID + 1, id);
    }

    FloatVector2D calcDesiredAngles() {
        return FloatVector2D(calcDesiredPitch(), calcDesiredYaw());
    }

    float calcDesiredPitch() {
        if (local) return 0;
        const FloatVector3D shift = FloatVector3D(100000, 100000, 100000);
        const FloatVector3D originA = myLocalPlayer->localOrigin.add(shift);
        const FloatVector3D originB = localOrigin_predicted.add(shift).subtract(FloatVector3D(0, 0, 20));
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

    FloatVector2D calcDesiredAnglesIncrement() {
        return FloatVector2D(calcPitchIncrement(), calcYawIncrement());
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
        return 1000 - (fabs(aimbotDesiredAnglesIncrement.x) + fabs(aimbotDesiredAnglesIncrement.y));
    }
};
