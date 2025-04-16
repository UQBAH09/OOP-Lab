#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

class Logger {
private:
    deque<string> logs;
    const int MAX_LOGS = 1000;

    void storeLog(const string& severity, const string& message, const string& source) {
        string formatted = "[" + severity + "] (" + source + "): " + message;

        if (logs.size() >= MAX_LOGS) {
            logs.pop_front();
        }

        logs.push_back(formatted);
    }

public:
    void logInfo(const string& message, const string& source = "Unknown") {
        storeLog("INFO", message, source);
    }

    void logWarning(const string& message, const string& source = "Unknown") {
        storeLog("WARN", message, source);
    }

    void logError(const string& message, const string& source = "Unknown") {
        storeLog("ERROR", message, source);
    }

    friend class Auditor;
};

class Auditor {
private:
    string auditorPassword = "securepass";

    bool authenticate(const string& password) {
        return password == auditorPassword;
    }

public:
    vector<string> retrieveLogs(const Logger& logger, const string& password) {
        if (authenticate(password)) {
            return vector<string>(logger.logs.begin(), logger.logs.end());
        } else {
            cout << "Access Denied: Invalid credentials.\n";
            return {};
        }
    }
};

int main() {
    Logger logger;

    // Simulate logs from different modules
    logger.logInfo("Network initialized successfully.", "Network Module");
    logger.logWarning("Database connection slow.", "Database Module");
    logger.logError("Disk write failure.", "Storage Module");

    logger.logInfo("Heartbeat signal sent.", "Network Module");
    logger.logError("Authentication failure.", "Auth Module");

    // Try to retrieve logs as an auditor
    Auditor auditor;

    cout << "\nAttempting audit with correct password:\n";
    vector<string> logs = auditor.retrieveLogs(logger, "securepass");

    for (const string& entry : logs) {
        cout << entry << endl;
    }

    cout << "\nAttempting audit with incorrect password:\n";
    auditor.retrieveLogs(logger, "wrongpass");

    return 0;
}