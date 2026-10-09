#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
class Analysis {
    vector<int>* graph;
    vector<string>* names;
    vector<int>* subjectNodes;
public:
    Analysis(vector<int> g[], vector<string>& n, vector<int>& s) {
        graph = g;
        names = &n;
        subjectNodes = &s;
    }
    void showOverall(int totalNodes) {
        cout << "\n OVERALL ANALYSIS      \n";
        vector<bool> visited(totalNodes, false);
        queue<int> q;
        for (int start = 0; start < totalNodes; start++) {
            if (visited[start])
                continue;
            q.push(start);
            visited[start] = true;
            while (!q.empty()) {
                int current = q.front();
                q.pop();
                cout << (*names)[current] << " ";
                for (int next : graph[current]) {
                    if (!visited[next]) {
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }
        }
        cout << endl;
    }
    void showSubjectWise() {
        cout << "\n SUBJECT-WISE ANALYSIS      \n";
        for (int subject : *subjectNodes) {
            vector<bool> visited(names->size(), false);
            vector<int> stack;
            cout << "\nSubject: " << (*names)[subject] << endl;
            stack.push_back(subject);
            visited[subject] = true;
            while (!stack.empty()) {
                int current = stack.back();
                stack.pop_back();
                cout << (*names)[current] << " ";
                for (int i = graph[current].size() - 1; i >= 0; i--) {
                    int next = graph[current][i];
                    if (!visited[next]) {
                        visited[next] = true;
                        stack.push_back(next);
                    }
                }
            }
            cout << endl;
        }
    }
    void subjectWiseGrowth() {
        cout << "\n SUBJECT-WISE STUDENT GROWTH\n";
        int n;
        cout << "Enter number of subjects: ";
        cin >> n;
        if (n <= 0) {
            cout << "Invalid number of subjects.\n";
            return;
        }
        vector<string> subject(n);
        vector<int> total(n), completed(n);
        for (int i = 0; i < n; i++) {
            cout << "\nEnter subject " << i + 1 << ": ";
            cin >> subject[i];
            cout << "Enter total tasks for " << subject[i] << ": ";
            cin >> total[i];
            cout << "Enter completed tasks for " << subject[i] << ": ";
            cin >> completed[i];
            if (total[i] < 0)
                total[i] = 0;
            if (completed[i] < 0)
                completed[i] = 0;
            if (completed[i] > total[i])
                completed[i] = total[i];
        }
        ofstream data("subject_growth.dat");
        cout << "\n SUBJECT PERFORMANCE \n";
        for (int i = 0; i < n; i++) {
            double performance = 0;
            if (total[i] != 0)
                performance = (double)completed[i] / total[i] * 100;
            cout << subject[i] << " : "<< performance << "%\n";
            data << i + 1 << " " << performance << endl;
        }
        data.close();
        ofstream plot("subject_growth.gp");
        plot << "set terminal qt persist\n";
        plot << "set title 'Subject-wise Student Performance'\n";
        plot << "set xlabel 'Subjects'\n";
        plot << "set ylabel 'Performance (%)'\n";
        plot << "set yrange [0:100]\n";
        plot << "set grid\n";
        plot << "set xtics (";
        for (int i = 0; i < n; i++) {
            plot << "'" << subject[i] << "' " << i + 1;
            if (i != n - 1)
                plot << ", ";
        }
        plot << ")\n";
        plot << "plot 'subject_growth.dat' using 1:2 "<< "with linespoints lw 2 pt 7 "<< "title 'Student Performance'\n";
        plot << "set terminal qt persist\n";
        plot.close();
        string command = "start \"\" \"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist \"subject_growth.gp\"";
system(command.c_str());
        cout << "\nSubject-wise growth graph generated.\n";
    }
};