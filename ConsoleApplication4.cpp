//Refresher lab 1 CS216 Fatima Chea 

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

void readData(const string& filename, vector<int>& divBy3, vector<int>& divBy7, vector<int>& others);
void printStats(const vector<int>& arr, const string& label);
double calculateAverage(const vector<int>& arr);
int calculateSum(const vector<int>& arr);
double calculateMedian(vector<int> arr); 
void bubbleSortDescending(vector<int>& arr);
void printSortedArrays(const vector<int>& divBy3, const vector<int>& divBy7, const vector<int>& others);
void writeToFile(const string& filename, const vector<int>& divBy3, const vector<int>& divBy7, const vector<int>& others);
int main() {
    vector<int> divBy3, divBy7, others;
    string inputFile = "numbers.txt";
    string outputFile = "output.txt";
    readData(inputFile, divBy3, divBy7, others);
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Print arrays with sum, average, and median\n";
        cout << "2. Print arrays sorted in descending order\n";
        cout << "3. Quit and write data to output file\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            printStats(divBy3, "Divisible by 3");
            printStats(divBy7, "Divisible by 7");
            printStats(others, "Others");
            break;
        case 2:
            printSortedArrays(divBy3, divBy7, others);
            break;
        case 3:
            writeToFile(outputFile, divBy3, divBy7, others);
            cout << "Data written to " << outputFile << ". Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
    return 0;
}

void readData(const string& filename, vector<int>& divBy3, vector<int>& divBy7, vector<int>& others) {
    ifstream file(filename);
    int num;
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return;
    }
    while (file >> num) {
        if (num % 3 == 0)
            divBy3.push_back(num);
        else if (num % 7 == 0)
            divBy7.push_back(num);
        else
            others.push_back(num);
    }
    file.close();
}

void printStats(const vector<int>& arr, const string& label) {
    cout << "\n--- " << label << " ---\n";
    if (arr.empty()) {
        cout << "No data.\n";
        return;
    }
    for (int num : arr)
        cout << num << " ";
    cout << "\nSum: " << calculateSum(arr);
    cout << "\nAverage: " << fixed << setprecision(2) << calculateAverage(arr);
    cout << "\nMedian: " << fixed << setprecision(2) << calculateMedian(arr) << endl;
}

int calculateSum(const vector<int>& arr) {
    int sum = 0;
    for (int num : arr)
        sum += num;
    return sum;
}

double calculateAverage(const vector<int>& arr) {
    if (arr.empty()) return 0;
    return static_cast<double>(calculateSum(arr)) / arr.size();
}

double calculateMedian(vector<int> arr) {
    if (arr.empty()) return 0;
    sort(arr.begin(), arr.end());
    int n = arr.size();
    if (n % 2 == 0)
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    else
        return arr[n / 2];
}

void bubbleSortDescending(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] < arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void printSortedArrays(const vector<int>& divBy3, const vector<int>& divBy7, const vector<int>& others) {
    vector<int> sorted3 = divBy3, sorted7 = divBy7, sortedOthers = others;
    bubbleSortDescending(sorted3);
    bubbleSortDescending(sorted7);
    bubbleSortDescending(sortedOthers);
    cout << "\n--- Sorted Divisible by 3 ---\n";
    for (int num : sorted3) cout << num << " ";
    cout << "\n--- Sorted Divisible by 7 ---\n";
    for (int num : sorted7) cout << num << " ";
    cout << "\n--- Sorted Others ---\n";
    for (int num : sortedOthers) cout << num << " ";
    cout << endl;
}

void writeToFile(const string& filename, const vector<int>& divBy3, const vector<int>& divBy7, const vector<int>& others) {
    ofstream out(filename);
    if (!out) {
        cerr << "Error: Cannot write to file " << filename << endl;
        return;
    }
    auto writeSection = [&](const vector<int>& arr, const string& label) {
        out << "--- " << label << " ---\n";
        for (int num : arr) out << num << " ";
        out << "\nSum: " << calculateSum(arr);
        out << "\nAverage: " << fixed << setprecision(2) << calculateAverage(arr);
        out << "\nMedian: " << fixed << setprecision(2) << calculateMedian(arr) << "\n\n";
        };
    writeSection(divBy3, "Divisible by 3");
    writeSection(divBy7, "Divisible by 7");
    writeSection(others, "Others");
    out.close();
}

