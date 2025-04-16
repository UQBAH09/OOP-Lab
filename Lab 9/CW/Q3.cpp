#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PatientRecord {
private:
    string name;
    string patientID;
    string dateOfBirth;
    vector<string> medicalHistory;
    vector<string> treatments;
    vector<string> billingDetails;

    friend class Doctor;
    friend class Billing;

    void updateMedicalHistory(const string& entry) {
        medicalHistory.push_back(entry);
    }

    void addTreatment(const string& treatment) {
        treatments.push_back(treatment);
    }

    void addBillingDetail(const string& detail) {
        billingDetails.push_back(detail);
    }

public:
    PatientRecord(string n, string id, string dob)
        : name(n), patientID(id), dateOfBirth(dob) {}

    string getPublicData() const {
        return "Name: " + name + ", ID: " + patientID + ", DOB: " + dateOfBirth;
    }

    vector<string> getMedicalData(const string& role) const {
        if (role == "Doctor") {
            return medicalHistory;
        } else {
            cout << "Access Denied: You are not authorized to view medical data.\n";
            return {};
        }
    }

    vector<string> getBillingData(const string& role) const {
        if (role == "Billing") {
            return billingDetails;
        } else {
            cout << "Access Denied: You are not authorized to view billing data.\n";
            return {};
        }
    }
};

class Doctor {
public:
    void addDiagnosis(PatientRecord& patient, const string& diagnosis) {
        patient.updateMedicalHistory(diagnosis);
    }

    void prescribeTreatment(PatientRecord& patient, const string& treatment) {
        patient.addTreatment(treatment);
    }

    void viewMedicalData(const PatientRecord& patient) {
        auto data = patient.getMedicalData("Doctor");
        cout << "Medical History:\n";
        for (const auto& entry : data) {
            cout << "- " << entry << endl;
        }
    }
};

class Billing {
public:
    void addBilling(PatientRecord& patient, const string& bill) {
        patient.addBillingDetail(bill);
    }

    void viewBilling(const PatientRecord& patient) {
        auto bills = patient.getBillingData("Billing");
        cout << "Billing Details:\n";
        for (const auto& b : bills) {
            cout << "- " << b << endl;
        }
    }
};

class Receptionist {
public:
    void tryAccessMedical(const PatientRecord& patient) {
        cout << "Receptionist trying to view medical data...\n";
        patient.getMedicalData("Receptionist");
    }

    void tryAccessBilling(const PatientRecord& patient) {
        cout << "Receptionist trying to view billing data...\n";
        patient.getBillingData("Receptionist");
    }
};

int main() {
    PatientRecord john("John Doe", "P1234", "1990-01-01");

    Doctor doc;
    Billing bill;
    Receptionist rec;

    // Public info access
    cout << "Public Info:\n" << john.getPublicData() << "\n\n";

    // Doctor access
    doc.addDiagnosis(john, "Flu");
    doc.prescribeTreatment(john, "Rest and fluids");
    doc.viewMedicalData(john);

    cout << "\n";

    // Billing access
    bill.addBilling(john, "Consultation - $100");
    bill.viewBilling(john);

    cout << "\n";

    // Receptionist tries to access sensitive data
    rec.tryAccessMedical(john);
    rec.tryAccessBilling(john);

    return 0;
}
