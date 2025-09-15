#include "Helper.hpp"
#include <iomanip>
static const std::string WHITESPACE = " \n\r\t\f\v";

std::string indenter(int n){
    if(n < 0)
        n = 0;
    return std::string (n, '\t');
}

void show_menu(const std::vector<std::string> &options, const std::string &prompt, int tabs){
    std::string indent = indenter(tabs);
    if(!prompt.empty()){
        std::cout << indent << prompt << ":\n";
    }
    indent.push_back('\t');
    for(int i = 0; i < options.size(); ++i){
        std::cout << indent  << std::right << std::setw(2) << i + 1 << ") " << options[i] << "\n";
    }
}

/**
 * @brief (Left Trim - In-place)
 * إزالة المسافات البيضاء البادئة من يسار الـ string (يعدل الأصل)
 */
void ltrim(std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    if (start == std::string::npos) {
        // إذا كان السترينج كله مسافات، قم بإفراغه
        s.clear();
    } else {
        // احذف من البداية (0) حتى أول حرف ليس بمسافة (start)
        s.erase(0, start);
    }
}

/**
 * @brief (Right Trim - In-place)
 * إزالة المسافات البيضاء اللاحقة من يمين الـ string (يعدل الأصل)
 */
void rtrim(std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    if (end == std::string::npos) {
         // إذا كان السترينج كله مسافات، قم بإفراغه
        s.clear();
    } else {
        // احذف كل شيء "بعد" آخر حرف ليس بمسافة (من end + 1)
        s.erase(end + 1);
    }
}

/**
 * @brief (Trim - In-place)
 * هذه هي الدالة التي طلبتها: تزيل المسافات البادئة واللاحقة (تعدل الأصل)
 */
void trim(std::string &s) {
    // الترتيب مهم: أزل من اليمين أولاً ثم اليسار
    // (أو العكس، كلاهما يعمل بشكل سليم)
    rtrim(s);
    ltrim(s);
}
std::basic_istream<char> &read_and_trim(std::istream &is, std::string &str){
    auto &ret = getline(is, str);
    trim(str);
    return ret;
}

