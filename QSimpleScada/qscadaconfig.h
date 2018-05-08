#ifndef CONFIG_H
#define CONFIG_H

#define MIN_PAUSE_TIME 5

enum VStatus {
    VStatusDefault,
    VStatusGray,
    VStatusGreen,
    VStatusYellow,
    VStatusRed
};

enum VIDAUnitStatus{
    VIDAUnitStatusNotConfigured = -1,
    VIDAUnitStatusConfigured,
    VIDAUnitStatusNotConnected
} ;

typedef enum {
    VMachineryClass1 = 1,
    VMachineryClass2,
    VMachineryClass3,
    VMachineryClass4
} VMachineryClass;

enum VUpdateMode {
    VUpdateModeFromTo,
    VUpdateMode24Hours,
    VUpdateModeDaysCount
};

enum VTrendPaintMode {
    VTrendPaintModeDefault,
    VTrendPaintModeHours,
    VTrendPaintModeDays
};

inline double GetRealRecordingPeriod(QList<int>& recordingDurations, double&& pauseTime = 0, int&& totalRecordingTime = 0)
{
    totalRecordingTime = 0;
    pauseTime = 0;

    for(const int& value : recordingDurations) {
        totalRecordingTime += value;
    }

    pauseTime = totalRecordingTime * 0.5;

    if(pauseTime < (double)MIN_PAUSE_TIME) {
        pauseTime = (double)MIN_PAUSE_TIME;
    }

    double rRecordingPeriod = (double)totalRecordingTime + pauseTime;

    return rRecordingPeriod;
}

#endif // CONFIG_H
