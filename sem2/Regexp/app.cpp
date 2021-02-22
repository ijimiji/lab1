#include "app.h"

bool operator==(const shared_ptr<Student> &x, const shared_ptr<Student> &y){
    return x->getFullName() == y->getFullName();
}

struct line
{
    string buf;
    operator std::string() const { return buf; }
};
std::istream& operator>>(std::istream& in, line& line)
{
    return std::getline(in, line.buf);
}

vector<string> readFile(string fileName){
    vector<string> out;
    std::ifstream in(fileName);
    std::copy(std::istream_iterator<line>(in),
        std::istream_iterator<line>(),
        std::back_inserter(out));
    return out;
}

vector<string> parseLine(string line){
    vector<string> out;
    std::stringstream ss(line);
    string word;
    while (ss >> word){
       out.push_back(word);
    }
    return out;
}

vector<vector<string>> parseLines(vector<string> lines){
    vector<vector<string>> out;
    for (auto line : lines){
        out.push_back(parseLine(line));
    }
    return out;
}

shared_ptr<Student> createStudent(vector<string> fields){
    auto student = std::make_shared<Student>();
    student->f_name = fields[0];
    student->surname = fields[1];
    student->s_name = fields[2];
    if (fields.size() == 5){
        student->year = std::stoi(fields[3]);
        student->id = std::stoll(fields[4]);
    }
    return student;
}

void App::Main() {
    auto lines = readFile("L1_NEW_UTF8.txt");
    auto parsed_lines = parseLines(lines);
    vector<shared_ptr<Student>> students;
    for (auto line : parsed_lines){
        students.push_back(createStudent(line));
    }
    cout << "Enter min_year: ";
    int min_year;
    cin >> min_year;
    auto cmp = [](shared_ptr<Student> student_a, shared_ptr<Student> student_b){
        if (student_a->surname > student_b->surname){
            return false;
        }
        else if (student_a->surname == student_b->surname) {

            if (student_a->f_name > student_b->f_name) {
                return false;
            }
            else if (student_a->f_name == student_b->f_name) {
                if (student_a->s_name > student_b->s_name) {
                    return false;
                }
                return true;
            }
            return true;
        }
        return true;
    };
    auto filter = [min_year](shared_ptr<Student> student) {
        return student->year < min_year;
    };
    students.erase(std::remove_if(students.begin(), students.end(), filter), students.end());
    std::sort(std::begin(students), std::end(students), cmp);
    std::ostream_iterator<shared_ptr<Student>> out_it (std::cout, "\n");
    std::copy(students.begin(), students.end(), out_it);

    auto hash = [](const  shared_ptr<Student> &s){ 
        return std::hash<std::string>()(s->getFullName()); 
    };

    std::unordered_set<shared_ptr<Student>, decltype(hash)> set(0, hash);

    for (auto student : students) {
        set.insert(student);
    }

    string arg;
    cout << "Enter student's name" << endl;
    while (arg != "exit"){
        std::cin.ignore ();
        std::getline(cin, arg, '\n');
        auto candidate = createStudent(parseLine(arg));
        auto match = set.find(candidate);
        if (match != set.end()){
            cout <<  (*match)->id << std::endl;
        } else if (arg != "") {
            cout << "Go away!\n";
        }
    }
}